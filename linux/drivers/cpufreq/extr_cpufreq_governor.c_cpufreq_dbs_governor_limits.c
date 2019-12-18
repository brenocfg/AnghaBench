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
struct policy_dbs_info {int /*<<< orphan*/  update_mutex; } ;
struct cpufreq_policy {struct policy_dbs_info* governor_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpufreq_policy_apply_limits (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  gov_dbs_data_mutex ; 
 int /*<<< orphan*/  gov_update_sample_delay (struct policy_dbs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void cpufreq_dbs_governor_limits(struct cpufreq_policy *policy)
{
	struct policy_dbs_info *policy_dbs;

	/* Protect gov->gdbs_data against cpufreq_dbs_governor_exit() */
	mutex_lock(&gov_dbs_data_mutex);
	policy_dbs = policy->governor_data;
	if (!policy_dbs)
		goto out;

	mutex_lock(&policy_dbs->update_mutex);
	cpufreq_policy_apply_limits(policy);
	gov_update_sample_delay(policy_dbs, 0);
	mutex_unlock(&policy_dbs->update_mutex);

out:
	mutex_unlock(&gov_dbs_data_mutex);
}