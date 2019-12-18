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
struct cs_policy_dbs_info {int /*<<< orphan*/  requested_freq; scalar_t__ down_skip; } ;
struct cpufreq_policy {int /*<<< orphan*/  cur; int /*<<< orphan*/  governor_data; } ;

/* Variables and functions */
 struct cs_policy_dbs_info* to_dbs_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs_start(struct cpufreq_policy *policy)
{
	struct cs_policy_dbs_info *dbs_info = to_dbs_info(policy->governor_data);

	dbs_info->down_skip = 0;
	dbs_info->requested_freq = policy->cur;
}