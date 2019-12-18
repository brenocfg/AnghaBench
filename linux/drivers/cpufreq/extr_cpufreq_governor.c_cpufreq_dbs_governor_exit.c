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
struct policy_dbs_info {int /*<<< orphan*/  list; struct dbs_data* dbs_data; } ;
struct dbs_governor {int /*<<< orphan*/  (* exit ) (struct dbs_data*) ;int /*<<< orphan*/ * gdbs_data; } ;
struct dbs_data {int /*<<< orphan*/  attr_set; } ;
struct cpufreq_policy {struct policy_dbs_info* governor_data; } ;

/* Variables and functions */
 struct dbs_governor* dbs_governor_of (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  free_policy_dbs_info (struct policy_dbs_info*,struct dbs_governor*) ; 
 unsigned int gov_attr_set_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gov_dbs_data_mutex ; 
 int /*<<< orphan*/  have_governor_per_policy () ; 
 int /*<<< orphan*/  kfree (struct dbs_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dbs_data*) ; 

void cpufreq_dbs_governor_exit(struct cpufreq_policy *policy)
{
	struct dbs_governor *gov = dbs_governor_of(policy);
	struct policy_dbs_info *policy_dbs = policy->governor_data;
	struct dbs_data *dbs_data = policy_dbs->dbs_data;
	unsigned int count;

	/* Protect gov->gdbs_data against concurrent updates. */
	mutex_lock(&gov_dbs_data_mutex);

	count = gov_attr_set_put(&dbs_data->attr_set, &policy_dbs->list);

	policy->governor_data = NULL;

	if (!count) {
		if (!have_governor_per_policy())
			gov->gdbs_data = NULL;

		gov->exit(dbs_data);
		kfree(dbs_data);
	}

	free_policy_dbs_info(policy_dbs, gov);

	mutex_unlock(&gov_dbs_data_mutex);
}