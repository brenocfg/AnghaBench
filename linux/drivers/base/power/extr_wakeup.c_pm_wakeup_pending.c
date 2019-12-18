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
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int events_check_enabled ; 
 int /*<<< orphan*/  events_lock ; 
 int /*<<< orphan*/  pm_abort_suspend ; 
 int /*<<< orphan*/  pm_pr_dbg (char*) ; 
 int /*<<< orphan*/  pm_print_active_wakeup_sources () ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int saved_count ; 
 int /*<<< orphan*/  split_counters (unsigned int*,unsigned int*) ; 

bool pm_wakeup_pending(void)
{
	unsigned long flags;
	bool ret = false;

	raw_spin_lock_irqsave(&events_lock, flags);
	if (events_check_enabled) {
		unsigned int cnt, inpr;

		split_counters(&cnt, &inpr);
		ret = (cnt != saved_count || inpr > 0);
		events_check_enabled = !ret;
	}
	raw_spin_unlock_irqrestore(&events_lock, flags);

	if (ret) {
		pm_pr_dbg("Wakeup pending, aborting suspend\n");
		pm_print_active_wakeup_sources();
	}

	return ret || atomic_read(&pm_abort_suspend) > 0;
}