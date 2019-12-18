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
struct cpufreq_policy {struct cpufreq_governor* governor; } ;
struct cpufreq_governor {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cpufreq_governor_mutex ; 
 struct cpufreq_governor* find_governor (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int request_module (char*,char*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpufreq_parse_governor(char *str_governor,
				  struct cpufreq_policy *policy)
{
	struct cpufreq_governor *t;

	mutex_lock(&cpufreq_governor_mutex);

	t = find_governor(str_governor);
	if (!t) {
		int ret;

		mutex_unlock(&cpufreq_governor_mutex);

		ret = request_module("cpufreq_%s", str_governor);
		if (ret)
			return -EINVAL;

		mutex_lock(&cpufreq_governor_mutex);

		t = find_governor(str_governor);
	}
	if (t && !try_module_get(t->owner))
		t = NULL;

	mutex_unlock(&cpufreq_governor_mutex);

	if (t) {
		policy->governor = t;
		return 0;
	}

	return -EINVAL;
}