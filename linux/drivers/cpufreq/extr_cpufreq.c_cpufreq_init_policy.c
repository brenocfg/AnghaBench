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
struct cpufreq_policy {scalar_t__ last_policy; scalar_t__ policy; struct cpufreq_governor* governor; int /*<<< orphan*/  cpu; int /*<<< orphan*/  last_governor; } ;
struct cpufreq_governor {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODATA ; 
 struct cpufreq_governor* cpufreq_default_governor () ; 
 int /*<<< orphan*/  cpufreq_parse_policy (int /*<<< orphan*/ ,struct cpufreq_policy*) ; 
 int cpufreq_set_policy (struct cpufreq_policy*,struct cpufreq_policy*) ; 
 struct cpufreq_governor* find_governor (int /*<<< orphan*/ ) ; 
 scalar_t__ has_target () ; 
 int /*<<< orphan*/  memcpy (struct cpufreq_policy*,struct cpufreq_policy*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpufreq_init_policy(struct cpufreq_policy *policy)
{
	struct cpufreq_governor *gov = NULL, *def_gov = NULL;
	struct cpufreq_policy new_policy;

	memcpy(&new_policy, policy, sizeof(*policy));

	def_gov = cpufreq_default_governor();

	if (has_target()) {
		/*
		 * Update governor of new_policy to the governor used before
		 * hotplug
		 */
		gov = find_governor(policy->last_governor);
		if (gov) {
			pr_debug("Restoring governor %s for cpu %d\n",
				policy->governor->name, policy->cpu);
		} else {
			if (!def_gov)
				return -ENODATA;
			gov = def_gov;
		}
		new_policy.governor = gov;
	} else {
		/* Use the default policy if there is no last_policy. */
		if (policy->last_policy) {
			new_policy.policy = policy->last_policy;
		} else {
			if (!def_gov)
				return -ENODATA;
			cpufreq_parse_policy(def_gov->name, &new_policy);
		}
	}

	return cpufreq_set_policy(policy, &new_policy);
}