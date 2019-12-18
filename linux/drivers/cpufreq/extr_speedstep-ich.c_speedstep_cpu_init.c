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
struct get_freqs {int ret; struct cpufreq_policy* policy; } ;
struct cpufreq_policy {int /*<<< orphan*/  freq_table; int /*<<< orphan*/  cpus; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_online_mask ; 
 unsigned int cpumask_any_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_freqs_on_cpu ; 
 int /*<<< orphan*/  smp_call_function_single (unsigned int,int /*<<< orphan*/ ,struct get_freqs*,int) ; 
 int /*<<< orphan*/  speedstep_freqs ; 
 int /*<<< orphan*/  topology_sibling_cpumask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int speedstep_cpu_init(struct cpufreq_policy *policy)
{
	unsigned int policy_cpu;
	struct get_freqs gf;

	/* only run on CPU to be set, or on its sibling */
#ifdef CONFIG_SMP
	cpumask_copy(policy->cpus, topology_sibling_cpumask(policy->cpu));
#endif
	policy_cpu = cpumask_any_and(policy->cpus, cpu_online_mask);

	/* detect low and high frequency and transition latency */
	gf.policy = policy;
	smp_call_function_single(policy_cpu, get_freqs_on_cpu, &gf, 1);
	if (gf.ret)
		return gf.ret;

	policy->freq_table = speedstep_freqs;

	return 0;
}