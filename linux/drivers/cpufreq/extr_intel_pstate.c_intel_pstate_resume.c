#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cpufreq_policy {size_t cpu; } ;
struct TYPE_3__ {scalar_t__ epp_policy; } ;

/* Variables and functions */
 TYPE_1__** all_cpu_data ; 
 int /*<<< orphan*/  hwp_active ; 
 int /*<<< orphan*/  intel_pstate_hwp_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  intel_pstate_hwp_set (size_t) ; 
 int /*<<< orphan*/  intel_pstate_limits_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_pstate_resume(struct cpufreq_policy *policy)
{
	if (!hwp_active)
		return 0;

	mutex_lock(&intel_pstate_limits_lock);

	if (policy->cpu == 0)
		intel_pstate_hwp_enable(all_cpu_data[policy->cpu]);

	all_cpu_data[policy->cpu]->epp_policy = 0;
	intel_pstate_hwp_set(policy->cpu);

	mutex_unlock(&intel_pstate_limits_lock);

	return 0;
}