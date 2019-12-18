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
struct cpufreq_policy {int /*<<< orphan*/  policy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_NAME_LEN ; 
 int /*<<< orphan*/  CPUFREQ_POLICY_PERFORMANCE ; 
 int /*<<< orphan*/  CPUFREQ_POLICY_POWERSAVE ; 
 int EINVAL ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpufreq_parse_policy(char *str_governor,
				struct cpufreq_policy *policy)
{
	if (!strncasecmp(str_governor, "performance", CPUFREQ_NAME_LEN)) {
		policy->policy = CPUFREQ_POLICY_PERFORMANCE;
		return 0;
	}
	if (!strncasecmp(str_governor, "powersave", CPUFREQ_NAME_LEN)) {
		policy->policy = CPUFREQ_POLICY_POWERSAVE;
		return 0;
	}
	return -EINVAL;
}