#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int min_freq; int max_freq; } ;
struct cpufreq_policy {size_t cpu; int min; int max; int fast_switch_possible; TYPE_2__ cpuinfo; } ;
struct TYPE_4__ {int min_pstate; int scaling; int turbo_pstate; int max_pstate; unsigned int max_freq; unsigned int turbo_freq; } ;
struct cpudata {int max_perf_ratio; TYPE_1__ pstate; scalar_t__ min_perf_ratio; } ;
struct TYPE_6__ {scalar_t__ turbo_disabled; scalar_t__ turbo_disabled_mf; } ;

/* Variables and functions */
 struct cpudata** all_cpu_data ; 
 TYPE_3__ global ; 
 scalar_t__ hwp_active ; 
 int /*<<< orphan*/  intel_pstate_init_acpi_perf_limits (struct cpufreq_policy*) ; 
 int intel_pstate_init_cpu (size_t) ; 
 int /*<<< orphan*/  update_turbo_state () ; 

__attribute__((used)) static int __intel_pstate_cpu_init(struct cpufreq_policy *policy)
{
	struct cpudata *cpu;
	int rc;

	rc = intel_pstate_init_cpu(policy->cpu);
	if (rc)
		return rc;

	cpu = all_cpu_data[policy->cpu];

	cpu->max_perf_ratio = 0xFF;
	cpu->min_perf_ratio = 0;

	policy->min = cpu->pstate.min_pstate * cpu->pstate.scaling;
	policy->max = cpu->pstate.turbo_pstate * cpu->pstate.scaling;

	/* cpuinfo and default policy values */
	policy->cpuinfo.min_freq = cpu->pstate.min_pstate * cpu->pstate.scaling;
	update_turbo_state();
	global.turbo_disabled_mf = global.turbo_disabled;
	policy->cpuinfo.max_freq = global.turbo_disabled ?
			cpu->pstate.max_pstate : cpu->pstate.turbo_pstate;
	policy->cpuinfo.max_freq *= cpu->pstate.scaling;

	if (hwp_active) {
		unsigned int max_freq;

		max_freq = global.turbo_disabled ?
			cpu->pstate.max_freq : cpu->pstate.turbo_freq;
		if (max_freq < policy->cpuinfo.max_freq)
			policy->cpuinfo.max_freq = max_freq;
	}

	intel_pstate_init_acpi_perf_limits(policy);

	policy->fast_switch_possible = true;

	return 0;
}