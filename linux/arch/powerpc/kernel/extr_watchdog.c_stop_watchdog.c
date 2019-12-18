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
struct hrtimer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_tb () ; 
 int /*<<< orphan*/  hrtimer_cancel (struct hrtimer*) ; 
 int smp_processor_id () ; 
 struct hrtimer* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wd_cpus_enabled ; 
 int /*<<< orphan*/  wd_hrtimer ; 
 int /*<<< orphan*/  wd_smp_clear_cpu_pending (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wd_smp_lock (unsigned long*) ; 
 int /*<<< orphan*/  wd_smp_unlock (unsigned long*) ; 

__attribute__((used)) static void stop_watchdog(void *arg)
{
	struct hrtimer *hrtimer = this_cpu_ptr(&wd_hrtimer);
	int cpu = smp_processor_id();
	unsigned long flags;

	if (!cpumask_test_cpu(cpu, &wd_cpus_enabled))
		return; /* Can happen in CPU unplug case */

	hrtimer_cancel(hrtimer);

	wd_smp_lock(&flags);
	cpumask_clear_cpu(cpu, &wd_cpus_enabled);
	wd_smp_unlock(&flags);

	wd_smp_clear_cpu_pending(cpu, get_tb());
}