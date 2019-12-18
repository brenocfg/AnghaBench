#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct omap_hwmod {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ptr; } ;
struct clockdomain {scalar_t__ usecount; int /*<<< orphan*/  name; TYPE_1__ pwrdm; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* clkdm_clk_disable ) (struct clockdomain*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_2__* arch_clkdm ; 
 scalar_t__ cpu_is_omap24xx () ; 
 scalar_t__ cpu_is_omap34xx () ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_state_switch_nolock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct clockdomain*) ; 

int clkdm_hwmod_disable(struct clockdomain *clkdm, struct omap_hwmod *oh)
{
	/* The clkdm attribute does not exist yet prior OMAP4 */
	if (cpu_is_omap24xx() || cpu_is_omap34xx())
		return 0;

	/*
	 * XXX Rewrite this code to maintain a list of enabled
	 * downstream hwmods for debugging purposes?
	 */

	if (!clkdm || !oh || !arch_clkdm || !arch_clkdm->clkdm_clk_disable)
		return -EINVAL;

	pwrdm_lock(clkdm->pwrdm.ptr);

	if (clkdm->usecount == 0) {
		pwrdm_unlock(clkdm->pwrdm.ptr);
		WARN_ON(1); /* underflow */
		return -ERANGE;
	}

	clkdm->usecount--;
	if (clkdm->usecount > 0) {
		pwrdm_unlock(clkdm->pwrdm.ptr);
		return 0;
	}

	arch_clkdm->clkdm_clk_disable(clkdm);
	pwrdm_state_switch_nolock(clkdm->pwrdm.ptr);
	pwrdm_unlock(clkdm->pwrdm.ptr);

	pr_debug("clockdomain: %s: disabled\n", clkdm->name);

	return 0;
}