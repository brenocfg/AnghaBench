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
struct TYPE_2__ {int /*<<< orphan*/  min_freq; } ;
struct cpufreq_policy {size_t cpu; scalar_t__ policy; TYPE_1__ cpuinfo; } ;
struct cpudata {int dummy; } ;

/* Variables and functions */
 scalar_t__ CPUFREQ_POLICY_PERFORMANCE ; 
 scalar_t__ CPUFREQ_POLICY_POWERSAVE ; 
 int EINVAL ; 
 struct cpudata** all_cpu_data ; 
 int /*<<< orphan*/  cpufreq_verify_within_limits (struct cpufreq_policy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pstate_adjust_policy_max (struct cpufreq_policy*,struct cpudata*) ; 
 int /*<<< orphan*/  intel_pstate_get_max_freq (struct cpudata*) ; 
 int /*<<< orphan*/  update_turbo_state () ; 

__attribute__((used)) static int intel_pstate_verify_policy(struct cpufreq_policy *policy)
{
	struct cpudata *cpu = all_cpu_data[policy->cpu];

	update_turbo_state();
	cpufreq_verify_within_limits(policy, policy->cpuinfo.min_freq,
				     intel_pstate_get_max_freq(cpu));

	if (policy->policy != CPUFREQ_POLICY_POWERSAVE &&
	    policy->policy != CPUFREQ_POLICY_PERFORMANCE)
		return -EINVAL;

	intel_pstate_adjust_policy_max(policy, cpu);

	return 0;
}