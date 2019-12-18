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
 int /*<<< orphan*/  active_events ; 
 scalar_t__ atomic_dec_and_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nmi_active ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pmc_grab_mutex ; 
 int /*<<< orphan*/  start_nmi_watchdog ; 

__attribute__((used)) static void perf_event_release_pmc(void)
{
	if (atomic_dec_and_mutex_lock(&active_events, &pmc_grab_mutex)) {
		if (atomic_read(&nmi_active) == 0)
			on_each_cpu(start_nmi_watchdog, NULL, 1);
		mutex_unlock(&pmc_grab_mutex);
	}
}