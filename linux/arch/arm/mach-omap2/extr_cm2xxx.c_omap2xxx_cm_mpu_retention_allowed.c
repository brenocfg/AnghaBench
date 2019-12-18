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
 int /*<<< orphan*/  CM_FCLKEN1 ; 
 int /*<<< orphan*/  CORE_MOD ; 
 int OMAP2420_EN_MMC_MASK ; 
 int /*<<< orphan*/  OMAP24XX_CM_FCLKEN2 ; 
 int OMAP24XX_EN_DSS1_MASK ; 
 int OMAP24XX_EN_MCSPI1_MASK ; 
 int OMAP24XX_EN_MCSPI2_MASK ; 
 int OMAP24XX_EN_UART1_MASK ; 
 int OMAP24XX_EN_UART2_MASK ; 
 int OMAP24XX_EN_UART3_MASK ; 
 int omap2_cm_read_mod_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int omap2xxx_cm_mpu_retention_allowed(void)
{
	u32 l;

	/* Check for MMC, UART2, UART1, McSPI2, McSPI1 and DSS1. */
	l = omap2_cm_read_mod_reg(CORE_MOD, CM_FCLKEN1);
	if (l & (OMAP2420_EN_MMC_MASK | OMAP24XX_EN_UART2_MASK |
		 OMAP24XX_EN_UART1_MASK | OMAP24XX_EN_MCSPI2_MASK |
		 OMAP24XX_EN_MCSPI1_MASK | OMAP24XX_EN_DSS1_MASK))
		return 0;
	/* Check for UART3. */
	l = omap2_cm_read_mod_reg(CORE_MOD, OMAP24XX_CM_FCLKEN2);
	if (l & OMAP24XX_EN_UART3_MASK)
		return 0;

	return 1;
}