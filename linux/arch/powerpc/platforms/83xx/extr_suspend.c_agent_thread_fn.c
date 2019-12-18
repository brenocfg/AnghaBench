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
 int /*<<< orphan*/  PM_SUSPEND_MEM ; 
 int /*<<< orphan*/  PM_SUSPEND_STANDBY ; 
 int /*<<< orphan*/  agent_wq ; 
 int /*<<< orphan*/  current ; 
 int pci_pm_state ; 
 int /*<<< orphan*/  pm_suspend (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_to_freeze () ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int wake_from_pci ; 

__attribute__((used)) static int agent_thread_fn(void *data)
{
	while (1) {
		wait_event_interruptible(agent_wq, pci_pm_state >= 2);
		try_to_freeze();

		if (signal_pending(current) || pci_pm_state < 2)
			continue;

		/* With a preemptible kernel (or SMP), this could race with
		 * a userspace-driven suspend request.  It's probably best
		 * to avoid mixing the two with such a configuration (or
		 * else fix it by adding a mutex to state_store that we can
		 * synchronize with).
		 */

		wake_from_pci = 1;

		pm_suspend(pci_pm_state == 3 ? PM_SUSPEND_MEM :
		                               PM_SUSPEND_STANDBY);

		wake_from_pci = 0;
	}

	return 0;
}