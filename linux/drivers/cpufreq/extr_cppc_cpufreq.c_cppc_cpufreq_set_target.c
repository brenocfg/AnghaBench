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
typedef  scalar_t__ u32 ;
struct cpufreq_policy {size_t cpu; int /*<<< orphan*/  cur; } ;
struct cpufreq_freqs {unsigned int new; int /*<<< orphan*/  old; } ;
struct TYPE_2__ {scalar_t__ desired_perf; } ;
struct cppc_cpudata {int /*<<< orphan*/  cpu; TYPE_1__ perf_ctrls; } ;

/* Variables and functions */
 struct cppc_cpudata** all_cpu_data ; 
 scalar_t__ cppc_cpufreq_khz_to_perf (struct cppc_cpudata*,unsigned int) ; 
 int cppc_set_perf (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  cpufreq_freq_transition_begin (struct cpufreq_policy*,struct cpufreq_freqs*) ; 
 int /*<<< orphan*/  cpufreq_freq_transition_end (struct cpufreq_policy*,struct cpufreq_freqs*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cppc_cpufreq_set_target(struct cpufreq_policy *policy,
		unsigned int target_freq,
		unsigned int relation)
{
	struct cppc_cpudata *cpu;
	struct cpufreq_freqs freqs;
	u32 desired_perf;
	int ret = 0;

	cpu = all_cpu_data[policy->cpu];

	desired_perf = cppc_cpufreq_khz_to_perf(cpu, target_freq);
	/* Return if it is exactly the same perf */
	if (desired_perf == cpu->perf_ctrls.desired_perf)
		return ret;

	cpu->perf_ctrls.desired_perf = desired_perf;
	freqs.old = policy->cur;
	freqs.new = target_freq;

	cpufreq_freq_transition_begin(policy, &freqs);
	ret = cppc_set_perf(cpu->cpu, &cpu->perf_ctrls);
	cpufreq_freq_transition_end(policy, &freqs, ret != 0);

	if (ret)
		pr_debug("Failed to set target on CPU:%d. ret:%d\n",
				cpu->cpu, ret);

	return ret;
}