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
struct TYPE_3__ {int /*<<< orphan*/  ptr; } ;
struct clockdomain {scalar_t__ usecount; TYPE_1__ pwrdm; int /*<<< orphan*/  name; } ;
struct clk {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* clkdm_clk_disable ) (struct clockdomain*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ __clk_get_enable_count (struct clk*) ; 
 TYPE_2__* arch_clkdm ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_state_switch_nolock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct clockdomain*) ; 

int clkdm_clk_disable(struct clockdomain *clkdm, struct clk *clk)
{
	if (!clkdm || !clk || !arch_clkdm || !arch_clkdm->clkdm_clk_disable)
		return -EINVAL;

	pwrdm_lock(clkdm->pwrdm.ptr);

	/* corner case: disabling unused clocks */
	if ((__clk_get_enable_count(clk) == 0) && clkdm->usecount == 0)
		goto ccd_exit;

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

	pr_debug("clockdomain: %s: disabled\n", clkdm->name);

ccd_exit:
	pwrdm_unlock(clkdm->pwrdm.ptr);

	return 0;
}