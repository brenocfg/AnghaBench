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

/* Variables and functions */
 scalar_t__ OMAP343X_CONTROL_MEM_WKUP ; 
 int /*<<< orphan*/  OMAP343X_PADCONF_ETK_D14 ; 
 int /*<<< orphan*/  omap3_control_save_context () ; 
 int /*<<< orphan*/  omap3_ctrl_save_padconf () ; 
 int /*<<< orphan*/  omap3_gpmc_save_context () ; 
 int /*<<< orphan*/  omap_ctrl_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_ctrl_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  omap_dma_global_context_save () ; 
 int /*<<< orphan*/  omap_intc_save_context () ; 

__attribute__((used)) static void omap3_core_save_context(void)
{
	omap3_ctrl_save_padconf();

	/*
	 * Force write last pad into memory, as this can fail in some
	 * cases according to errata 1.157, 1.185
	 */
	omap_ctrl_writel(omap_ctrl_readl(OMAP343X_PADCONF_ETK_D14),
		OMAP343X_CONTROL_MEM_WKUP + 0x2a0);

	/* Save the Interrupt controller context */
	omap_intc_save_context();
	/* Save the GPMC context */
	omap3_gpmc_save_context();
	/* Save the system control module context, padconf already save above*/
	omap3_control_save_context();
	omap_dma_global_context_save();
}