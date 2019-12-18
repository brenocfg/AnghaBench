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
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  machine_crash_nonpanic_core ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ num_online_cpus () ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  smp_call_function (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  waiting_for_crash_ipi ; 

void crash_smp_send_stop(void)
{
	static int cpus_stopped;
	unsigned long msecs;

	if (cpus_stopped)
		return;

	atomic_set(&waiting_for_crash_ipi, num_online_cpus() - 1);
	smp_call_function(machine_crash_nonpanic_core, NULL, false);
	msecs = 1000; /* Wait at most a second for the other cpus to stop */
	while ((atomic_read(&waiting_for_crash_ipi) > 0) && msecs) {
		mdelay(1);
		msecs--;
	}
	if (atomic_read(&waiting_for_crash_ipi) > 0)
		pr_warn("Non-crashing CPUs did not react to IPI\n");

	cpus_stopped = 1;
}