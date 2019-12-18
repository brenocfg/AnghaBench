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
typedef  int suspend_state_t ;

/* Variables and functions */
 int EINVAL ; 
#define  PM_SUSPEND_MEM 128 
 int /*<<< orphan*/  cpu_suspend (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outer_disable () ; 
 int /*<<< orphan*/  outer_resume () ; 
 int /*<<< orphan*/  sirfsoc_finish_suspend ; 
 int /*<<< orphan*/  sirfsoc_pre_suspend_power_off () ; 

__attribute__((used)) static int sirfsoc_pm_enter(suspend_state_t state)
{
	switch (state) {
	case PM_SUSPEND_MEM:
		sirfsoc_pre_suspend_power_off();

		outer_disable();
		/* go zzz */
		cpu_suspend(0, sirfsoc_finish_suspend);
		outer_resume();
		break;
	default:
		return -EINVAL;
	}
	return 0;
}