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
struct od_policy_dbs_info {scalar_t__ freq_lo; } ;
struct cpufreq_policy {int /*<<< orphan*/  governor_data; } ;

/* Variables and functions */
 struct od_policy_dbs_info* to_dbs_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ondemand_powersave_bias_init(struct cpufreq_policy *policy)
{
	struct od_policy_dbs_info *dbs_info = to_dbs_info(policy->governor_data);

	dbs_info->freq_lo = 0;
}