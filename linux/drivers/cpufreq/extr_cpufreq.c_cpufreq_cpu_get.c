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
struct cpufreq_policy {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct cpufreq_policy* cpufreq_cpu_get_raw (unsigned int) ; 
 scalar_t__ cpufreq_driver ; 
 int /*<<< orphan*/  cpufreq_driver_lock ; 
 int /*<<< orphan*/  kobject_get (int /*<<< orphan*/ *) ; 
 unsigned int nr_cpu_ids ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct cpufreq_policy *cpufreq_cpu_get(unsigned int cpu)
{
	struct cpufreq_policy *policy = NULL;
	unsigned long flags;

	if (WARN_ON(cpu >= nr_cpu_ids))
		return NULL;

	/* get the cpufreq driver */
	read_lock_irqsave(&cpufreq_driver_lock, flags);

	if (cpufreq_driver) {
		/* get the CPU */
		policy = cpufreq_cpu_get_raw(cpu);
		if (policy)
			kobject_get(&policy->kobj);
	}

	read_unlock_irqrestore(&cpufreq_driver_lock, flags);

	return policy;
}