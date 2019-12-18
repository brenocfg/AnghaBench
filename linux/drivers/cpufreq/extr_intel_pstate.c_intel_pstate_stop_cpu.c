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
struct cpufreq_policy {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 scalar_t__ hwp_active ; 
 int /*<<< orphan*/  intel_cpufreq_stop_cpu (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  intel_pstate_clear_update_util_hook (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pstate_hwp_force_min_perf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pstate_hwp_save_state (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_pstate_stop_cpu(struct cpufreq_policy *policy)
{
	pr_debug("CPU %d exiting\n", policy->cpu);

	intel_pstate_clear_update_util_hook(policy->cpu);
	if (hwp_active) {
		intel_pstate_hwp_save_state(policy);
		intel_pstate_hwp_force_min_perf(policy->cpu);
	} else {
		intel_cpufreq_stop_cpu(policy);
	}
}