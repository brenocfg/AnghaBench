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
typedef  int /*<<< orphan*/  u64 ;
struct cpufreq_policy {size_t cpu; } ;
struct TYPE_2__ {int scaling; } ;
struct cpudata {TYPE_1__ pstate; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int HWP_GUARANTEED_PERF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSR_HWP_CAPABILITIES ; 
 struct cpudata** all_cpu_data ; 
 int intel_pstate_get_cppc_guranteed (size_t) ; 
 int /*<<< orphan*/  rdmsrl_on_cpu (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_base_frequency(struct cpufreq_policy *policy, char *buf)
{
	struct cpudata *cpu;
	u64 cap;
	int ratio;

	ratio = intel_pstate_get_cppc_guranteed(policy->cpu);
	if (ratio <= 0) {
		rdmsrl_on_cpu(policy->cpu, MSR_HWP_CAPABILITIES, &cap);
		ratio = HWP_GUARANTEED_PERF(cap);
	}

	cpu = all_cpu_data[policy->cpu];

	return sprintf(buf, "%d\n", ratio * cpu->pstate.scaling);
}