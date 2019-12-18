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
struct cpufreq_policy {unsigned int cur; } ;
struct TYPE_2__ {unsigned int (* get ) (unsigned int) ;scalar_t__ setpolicy; } ;

/* Variables and functions */
 struct cpufreq_policy* cpufreq_cpu_get (unsigned int) ; 
 int /*<<< orphan*/  cpufreq_cpu_put (struct cpufreq_policy*) ; 
 TYPE_1__* cpufreq_driver ; 
 int /*<<< orphan*/  cpufreq_driver_lock ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int stub1 (unsigned int) ; 

unsigned int cpufreq_quick_get(unsigned int cpu)
{
	struct cpufreq_policy *policy;
	unsigned int ret_freq = 0;
	unsigned long flags;

	read_lock_irqsave(&cpufreq_driver_lock, flags);

	if (cpufreq_driver && cpufreq_driver->setpolicy && cpufreq_driver->get) {
		ret_freq = cpufreq_driver->get(cpu);
		read_unlock_irqrestore(&cpufreq_driver_lock, flags);
		return ret_freq;
	}

	read_unlock_irqrestore(&cpufreq_driver_lock, flags);

	policy = cpufreq_cpu_get(cpu);
	if (policy) {
		ret_freq = policy->cur;
		cpufreq_cpu_put(policy);
	}

	return ret_freq;
}