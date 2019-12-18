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
 size_t MPC512x_CLK_PCI ; 
 size_t MPC512x_CLK_PSC3_MCLK ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * clks ; 
 scalar_t__ of_find_compatible_node (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static void mpc5121_clk_provide_migration_support(void)
{

	/*
	 * pre-enable those clock items which are not yet appropriately
	 * acquired by their peripheral driver
	 *
	 * the PCI clock cannot get acquired by its peripheral driver,
	 * because for this platform the driver won't probe(), instead
	 * initialization is done from within the .setup_arch() routine
	 * at a point in time where the clock provider has not been
	 * setup yet and thus isn't available yet
	 *
	 * so we "pre-enable" the clock here, to not have the clock
	 * subsystem automatically disable this item in a late init call
	 *
	 * this PCI clock pre-enable workaround only applies when there
	 * are device tree nodes for PCI and thus the peripheral driver
	 * has attached to bridges, otherwise the PCI clock remains
	 * unused and so it gets disabled
	 */
	clk_prepare_enable(clks[MPC512x_CLK_PSC3_MCLK]);/* serial console */
	if (of_find_compatible_node(NULL, "pci", "fsl,mpc5121-pci"))
		clk_prepare_enable(clks[MPC512x_CLK_PCI]);
}