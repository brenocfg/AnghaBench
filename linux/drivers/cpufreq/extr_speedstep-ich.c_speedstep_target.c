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
 int /*<<< orphan*/  _speedstep_set_state ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 unsigned int cpumask_any_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_call_function_single (unsigned int,int /*<<< orphan*/ ,unsigned int*,int) ; 

__attribute__((used)) static int speedstep_target(struct cpufreq_policy *policy, unsigned int index)
{
	unsigned int policy_cpu;

	policy_cpu = cpumask_any_and(policy->cpus, cpu_online_mask);

	smp_call_function_single(policy_cpu, _speedstep_set_state, &index,
				 true);

	return 0;
}