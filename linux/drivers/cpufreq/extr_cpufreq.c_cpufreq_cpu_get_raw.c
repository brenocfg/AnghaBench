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
struct cpufreq_policy {int /*<<< orphan*/  cpus; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpufreq_cpu_data ; 
 scalar_t__ cpumask_test_cpu (unsigned int,int /*<<< orphan*/ ) ; 
 struct cpufreq_policy* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 

struct cpufreq_policy *cpufreq_cpu_get_raw(unsigned int cpu)
{
	struct cpufreq_policy *policy = per_cpu(cpufreq_cpu_data, cpu);

	return policy && cpumask_test_cpu(cpu, policy->cpus) ? policy : NULL;
}