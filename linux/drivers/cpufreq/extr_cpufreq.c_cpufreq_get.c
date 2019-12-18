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
struct cpufreq_policy {int /*<<< orphan*/  rwsem; } ;
struct TYPE_2__ {scalar_t__ get; } ;

/* Variables and functions */
 unsigned int __cpufreq_get (struct cpufreq_policy*) ; 
 struct cpufreq_policy* cpufreq_cpu_get (unsigned int) ; 
 int /*<<< orphan*/  cpufreq_cpu_put (struct cpufreq_policy*) ; 
 TYPE_1__* cpufreq_driver ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

unsigned int cpufreq_get(unsigned int cpu)
{
	struct cpufreq_policy *policy = cpufreq_cpu_get(cpu);
	unsigned int ret_freq = 0;

	if (policy) {
		down_read(&policy->rwsem);
		if (cpufreq_driver->get)
			ret_freq = __cpufreq_get(policy);
		up_read(&policy->rwsem);

		cpufreq_cpu_put(policy);
	}

	return ret_freq;
}