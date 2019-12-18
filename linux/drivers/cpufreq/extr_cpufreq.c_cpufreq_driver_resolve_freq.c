#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cpufreq_policy {unsigned int cached_target_freq; int cached_resolved_idx; TYPE_1__* freq_table; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_4__ {unsigned int (* resolve_freq ) (struct cpufreq_policy*,unsigned int) ;scalar_t__ target_index; } ;
struct TYPE_3__ {unsigned int frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_RELATION_L ; 
 unsigned int clamp_val (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* cpufreq_driver ; 
 int cpufreq_frequency_table_target (struct cpufreq_policy*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int stub1 (struct cpufreq_policy*,unsigned int) ; 

unsigned int cpufreq_driver_resolve_freq(struct cpufreq_policy *policy,
					 unsigned int target_freq)
{
	target_freq = clamp_val(target_freq, policy->min, policy->max);
	policy->cached_target_freq = target_freq;

	if (cpufreq_driver->target_index) {
		int idx;

		idx = cpufreq_frequency_table_target(policy, target_freq,
						     CPUFREQ_RELATION_L);
		policy->cached_resolved_idx = idx;
		return policy->freq_table[idx].frequency;
	}

	if (cpufreq_driver->resolve_freq)
		return cpufreq_driver->resolve_freq(policy, target_freq);

	return target_freq;
}