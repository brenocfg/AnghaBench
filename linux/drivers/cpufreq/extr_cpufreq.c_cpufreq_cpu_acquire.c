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
struct cpufreq_policy {int /*<<< orphan*/  rwsem; } ;

/* Variables and functions */
 struct cpufreq_policy* cpufreq_cpu_get (unsigned int) ; 
 int /*<<< orphan*/  cpufreq_cpu_release (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ policy_is_inactive (struct cpufreq_policy*) ; 

struct cpufreq_policy *cpufreq_cpu_acquire(unsigned int cpu)
{
	struct cpufreq_policy *policy = cpufreq_cpu_get(cpu);

	if (!policy)
		return NULL;

	down_write(&policy->rwsem);

	if (policy_is_inactive(policy)) {
		cpufreq_cpu_release(policy);
		return NULL;
	}

	return policy;
}