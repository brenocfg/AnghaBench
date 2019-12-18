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
 int /*<<< orphan*/  amx3_post_suspend_common () ; 
 int /*<<< orphan*/  amx3_pre_suspend_common () ; 
 int /*<<< orphan*/  clkdm_sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkdm_wakeup (int /*<<< orphan*/ ) ; 
 int cpu_suspend (unsigned long,int (*) (unsigned long)) ; 
 int /*<<< orphan*/  gfx_l4ls_clkdm ; 

__attribute__((used)) static int am33xx_suspend(unsigned int state, int (*fn)(unsigned long),
			  unsigned long args)
{
	int ret = 0;

	amx3_pre_suspend_common();
	ret = cpu_suspend(args, fn);
	amx3_post_suspend_common();

	/*
	 * BUG: GFX_L4LS clock domain needs to be woken up to
	 * ensure thet L4LS clock domain does not get stuck in
	 * transition. If that happens L3 module does not get
	 * disabled, thereby leading to PER power domain
	 * transition failing
	 */

	clkdm_wakeup(gfx_l4ls_clkdm);
	clkdm_sleep(gfx_l4ls_clkdm);

	return ret;
}