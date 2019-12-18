#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;

/* Variables and functions */
 int MEM_SYS_CFG_EBI_FIX_PRI_CFCON ; 
 int MEM_SYS_CFG_INDEP_CF ; 
 int /*<<< orphan*/  S3C64XX_GPB (int) ; 
 int /*<<< orphan*/  S3C64XX_GPK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S3C64XX_GPL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S3C64XX_GPM (int) ; 
 int /*<<< orphan*/  S3C_GPIO_SFN (int) ; 
 int /*<<< orphan*/  S3C_MEM_SYS_CFG ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_gpio_cfgpin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_gpio_cfgpin_range (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

void s3c64xx_ide_setup_gpio(void)
{
	u32 reg;

	reg = readl(S3C_MEM_SYS_CFG) & (~0x3f);

	/* Independent CF interface, CF chip select configuration */
	writel(reg | MEM_SYS_CFG_INDEP_CF |
		MEM_SYS_CFG_EBI_FIX_PRI_CFCON, S3C_MEM_SYS_CFG);

	s3c_gpio_cfgpin(S3C64XX_GPB(4), S3C_GPIO_SFN(4));

	/* Set XhiDATA[15:0] pins as CF Data[15:0] */
	s3c_gpio_cfgpin_range(S3C64XX_GPK(0), 16, S3C_GPIO_SFN(5));

	/* Set XhiADDR[2:0] pins as CF ADDR[2:0] */
	s3c_gpio_cfgpin_range(S3C64XX_GPL(0), 3, S3C_GPIO_SFN(6));

	/* Set Xhi ctrl pins as CF ctrl pins(IORDY, IOWR, IORD, CE[0:1]) */
	s3c_gpio_cfgpin(S3C64XX_GPM(5), S3C_GPIO_SFN(1));
	s3c_gpio_cfgpin_range(S3C64XX_GPM(0), 5, S3C_GPIO_SFN(6));
}