static volatile unsigned int *CCM_CCGR1 							 ;static volatile unsigned int *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER1;static volatile unsigned int *GPIO5_GDIR							 ;static volatile unsigned int *GPIO5_DR								 ;static volatile unsigned int *CCM_CCGR3 							 ;static volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_NAND_CE1_B       ;static volatile unsigned int *GPIO4_GDIR							 ;static volatile unsigned int *GPIO4_DR								 ;/********************************************************************** * 函数名称： buttons_init * 功能描述： 初始化按键引脚，就是把它设置为输入引脚 * 输入参数： 无 * 输出参数： 无 * 返 回 值： 无 * 修改日期        版本号     修改人	      修改内容 * ----------------------------------------------- * 2020/03/10	     V1.0	  来木	      创建 ***********************************************************************/void buttons_init(void){	unsigned int val;	CCM_CCGR1                               = (volatile unsigned int *)(0x20C406C);	IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER1 = (volatile unsigned int *)(0x229000C);	GPIO5_GDIR                              = (volatile unsigned int *)(0x20AC000 + 0x4);	GPIO5_DR                                = (volatile unsigned int *)(0x20AC000);		CCM_CCGR3                               = (volatile unsigned int *)(0x20C4074);	IOMUXC_SW_MUX_CTL_PAD_NAND_CE1_B 		= (volatile unsigned int *)(0x20E01B0);	GPIO4_GDIR                              = (volatile unsigned int *)(0x20A8000 + 0x4);	GPIO4_DR                                = (volatile unsigned int *)(0x20A8000);	/* buttons1  GPIO5_IO01 */	/* a. 	 * 使能GPIO5	 * set CCM to enable GPIO5	 * CCM_CCGR1[CG15] 0x20C406C	 * bit[31:30] = 0b11	 *	 * 使能GPIO4	 * set CCM to enable GPIO4	 * CCM_CCGR3[CG6] 0x20C4074	 * bit[13:12] = 0b11	 */	*CCM_CCGR1 |= (3<<30);	*CCM_CCGR3 |= (3<<12);	/* b. 	 * 设置GPIO5_IO01用于GPIO	 * set IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER1	 *      to configure GPIO5_IO01 as GPIO	 * IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER1  0x229000C	 * bit[3:0] = 0b0101 alt5	 *	 * 设置GPIO4_IO14用于GPIO	 * set IOMUXC_SW_MUX_CTL_PAD_NAND_CE1_B	 *      to configure GPIO4_IO14 as GPIO	 * IOMUXC_SW_MUX_CTL_PAD_NAND_CE1_B  0x20E01B0	 * bit[3:0] = 0b1101 alt5	 */	val = *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER1;	val &= ~(0xf);	val |= (5);	*IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER1 = val;		val = *IOMUXC_SW_MUX_CTL_PAD_NAND_CE1_B;	val &= ~(0xf);	val |= (5);	*IOMUXC_SW_MUX_CTL_PAD_NAND_CE1_B = val;		  			 		  						  					  				 	   		  	  	 	  	/* c. 	 * 设置GPIO5_IO01作为input引脚	 * set GPIO5_GDIR to configure GPIO5_IO01 as input	 * GPIO5_GDIR  0x020AC000 + 0x4	 * bit[1] = 0b0	 *	 * 设置GPIO4_IO14作为input引脚	 * set GPIO5_GDIR to configure GPIO4_IO14 as input	 * GPIO4_GDIR  0x020A8000 + 0x4	 * bit[14] = 0b0	 */	*GPIO5_GDIR &= ~(1<<1);	*GPIO4_GDIR &= ~(1<<14);}