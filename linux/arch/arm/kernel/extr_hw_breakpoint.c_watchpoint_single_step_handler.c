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
struct perf_event {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  enabled; } ;
struct arch_hw_breakpoint {unsigned long trigger; TYPE_1__ step_ctrl; } ;

/* Variables and functions */
 int core_num_wrps ; 
 struct arch_hw_breakpoint* counter_arch_bp (struct perf_event*) ; 
 int /*<<< orphan*/  disable_single_step (struct perf_event*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct perf_event** this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wp_on_reg ; 

__attribute__((used)) static void watchpoint_single_step_handler(unsigned long pc)
{
	int i;
	struct perf_event *wp, **slots;
	struct arch_hw_breakpoint *info;

	slots = this_cpu_ptr(wp_on_reg);

	for (i = 0; i < core_num_wrps; ++i) {
		rcu_read_lock();

		wp = slots[i];

		if (wp == NULL)
			goto unlock;

		info = counter_arch_bp(wp);
		if (!info->step_ctrl.enabled)
			goto unlock;

		/*
		 * Restore the original watchpoint if we've completed the
		 * single-step.
		 */
		if (info->trigger != pc)
			disable_single_step(wp);

unlock:
		rcu_read_unlock();
	}
}