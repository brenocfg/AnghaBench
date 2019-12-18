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
 int /*<<< orphan*/  cpufreq_set_policy (struct cpufreq_policy*,struct cpufreq_policy*) ; 
 int /*<<< orphan*/  policy_is_inactive (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

void refresh_frequency_limits(struct cpufreq_policy *policy)
{
	struct cpufreq_policy new_policy;

	if (!policy_is_inactive(policy)) {
		new_policy = *policy;
		pr_debug("updating policy for CPU %u\n", policy->cpu);

		cpufreq_set_policy(policy, &new_policy);
	}
}