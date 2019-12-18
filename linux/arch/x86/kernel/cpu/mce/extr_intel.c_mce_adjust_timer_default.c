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
 unsigned long CMCI_POLL_INTERVAL ; 
#define  CMCI_STORM_ACTIVE 129 
 unsigned long CMCI_STORM_INTERVAL ; 
 int CMCI_STORM_NONE ; 
#define  CMCI_STORM_SUBSIDED 128 
 int __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmci_backoff_cnt ; 
 int /*<<< orphan*/  cmci_recheck () ; 
 int /*<<< orphan*/  cmci_storm_on_cpus ; 
 int /*<<< orphan*/  cmci_storm_state ; 
 int /*<<< orphan*/  cmci_toggle_interrupt_mode (int) ; 
 int /*<<< orphan*/  mce_notify_irq () ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 scalar_t__ this_cpu_read (int /*<<< orphan*/ ) ; 

unsigned long cmci_intel_adjust_timer(unsigned long interval)
{
	if ((this_cpu_read(cmci_backoff_cnt) > 0) &&
	    (__this_cpu_read(cmci_storm_state) == CMCI_STORM_ACTIVE)) {
		mce_notify_irq();
		return CMCI_STORM_INTERVAL;
	}

	switch (__this_cpu_read(cmci_storm_state)) {
	case CMCI_STORM_ACTIVE:

		/*
		 * We switch back to interrupt mode once the poll timer has
		 * silenced itself. That means no events recorded and the timer
		 * interval is back to our poll interval.
		 */
		__this_cpu_write(cmci_storm_state, CMCI_STORM_SUBSIDED);
		if (!atomic_sub_return(1, &cmci_storm_on_cpus))
			pr_notice("CMCI storm subsided: switching to interrupt mode\n");

		/* FALLTHROUGH */

	case CMCI_STORM_SUBSIDED:
		/*
		 * We wait for all CPUs to go back to SUBSIDED state. When that
		 * happens we switch back to interrupt mode.
		 */
		if (!atomic_read(&cmci_storm_on_cpus)) {
			__this_cpu_write(cmci_storm_state, CMCI_STORM_NONE);
			cmci_toggle_interrupt_mode(true);
			cmci_recheck();
		}
		return CMCI_POLL_INTERVAL;
	default:

		/* We have shiny weather. Let the poll do whatever it thinks. */
		return interval;
	}
}