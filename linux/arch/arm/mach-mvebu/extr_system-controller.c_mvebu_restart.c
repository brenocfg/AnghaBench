#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum reboot_mode { ____Placeholder_reboot_mode } reboot_mode ;
struct TYPE_2__ {scalar_t__ system_soft_reset_offset; int /*<<< orphan*/  system_soft_reset; scalar_t__ rstoutn_mask_offset; int /*<<< orphan*/  rstoutn_mask_reset_out_en; } ;

/* Variables and functions */
 TYPE_1__* mvebu_sc ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ system_controller_base ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void mvebu_restart(enum reboot_mode mode, const char *cmd)
{
	if (!system_controller_base) {
		pr_err("Cannot restart, system-controller not available: check the device tree\n");
	} else {
		/*
		 * Enable soft reset to assert RSTOUTn.
		 */
		writel(mvebu_sc->rstoutn_mask_reset_out_en,
			system_controller_base +
			mvebu_sc->rstoutn_mask_offset);
		/*
		 * Assert soft reset.
		 */
		writel(mvebu_sc->system_soft_reset,
			system_controller_base +
			mvebu_sc->system_soft_reset_offset);
	}

	while (1)
		;
}