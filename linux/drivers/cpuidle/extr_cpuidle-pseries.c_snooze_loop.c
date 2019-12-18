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
typedef  scalar_t__ u64 ;
struct cpuidle_driver {int dummy; } ;
struct cpuidle_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HMT_low () ; 
 int /*<<< orphan*/  HMT_medium () ; 
 int /*<<< orphan*/  HMT_very_low () ; 
 int /*<<< orphan*/  TIF_POLLING_NRFLAG ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 scalar_t__ get_tb () ; 
 int /*<<< orphan*/  idle_loop_epilog (unsigned long) ; 
 int /*<<< orphan*/  idle_loop_prolog (unsigned long*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  need_resched () ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ snooze_timeout ; 
 int /*<<< orphan*/  snooze_timeout_en ; 

__attribute__((used)) static int snooze_loop(struct cpuidle_device *dev,
			struct cpuidle_driver *drv,
			int index)
{
	unsigned long in_purr;
	u64 snooze_exit_time;

	set_thread_flag(TIF_POLLING_NRFLAG);

	idle_loop_prolog(&in_purr);
	local_irq_enable();
	snooze_exit_time = get_tb() + snooze_timeout;

	while (!need_resched()) {
		HMT_low();
		HMT_very_low();
		if (likely(snooze_timeout_en) && get_tb() > snooze_exit_time) {
			/*
			 * Task has not woken up but we are exiting the polling
			 * loop anyway. Require a barrier after polling is
			 * cleared to order subsequent test of need_resched().
			 */
			clear_thread_flag(TIF_POLLING_NRFLAG);
			smp_mb();
			break;
		}
	}

	HMT_medium();
	clear_thread_flag(TIF_POLLING_NRFLAG);

	local_irq_disable();

	idle_loop_epilog(in_purr);

	return index;
}