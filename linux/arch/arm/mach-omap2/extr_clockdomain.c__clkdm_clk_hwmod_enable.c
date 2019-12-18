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
struct clockdomain {int usecount; int /*<<< orphan*/  name; TYPE_1__ pwrdm; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* clkdm_clk_enable ) (struct clockdomain*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_2__* arch_clkdm ; 
 scalar_t__ autodeps ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_state_switch_nolock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct clockdomain*) ; 

__attribute__((used)) static int _clkdm_clk_hwmod_enable(struct clockdomain *clkdm)
{
	if (!clkdm || !arch_clkdm || !arch_clkdm->clkdm_clk_enable)
		return -EINVAL;

	pwrdm_lock(clkdm->pwrdm.ptr);

	/*
	 * For arch's with no autodeps, clkcm_clk_enable
	 * should be called for every clock instance or hwmod that is
	 * enabled, so the clkdm can be force woken up.
	 */
	clkdm->usecount++;
	if (clkdm->usecount > 1 && autodeps) {
		pwrdm_unlock(clkdm->pwrdm.ptr);
		return 0;
	}

	arch_clkdm->clkdm_clk_enable(clkdm);
	pwrdm_state_switch_nolock(clkdm->pwrdm.ptr);
	pwrdm_unlock(clkdm->pwrdm.ptr);

	pr_debug("clockdomain: %s: enabled\n", clkdm->name);

	return 0;
}