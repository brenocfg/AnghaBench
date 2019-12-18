#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpuidle_governor {scalar_t__ rating; int /*<<< orphan*/  name; int /*<<< orphan*/  governor_list; int /*<<< orphan*/  select; } ;
struct TYPE_2__ {scalar_t__ rating; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUIDLE_NAME_LEN ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENODEV ; 
 TYPE_1__* cpuidle_curr_governor ; 
 scalar_t__ cpuidle_disabled () ; 
 int /*<<< orphan*/ * cpuidle_find_governor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuidle_governors ; 
 int /*<<< orphan*/  cpuidle_lock ; 
 int /*<<< orphan*/  cpuidle_switch_governor (struct cpuidle_governor*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  param_governor ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cpuidle_register_governor(struct cpuidle_governor *gov)
{
	int ret = -EEXIST;

	if (!gov || !gov->select)
		return -EINVAL;

	if (cpuidle_disabled())
		return -ENODEV;

	mutex_lock(&cpuidle_lock);
	if (cpuidle_find_governor(gov->name) == NULL) {
		ret = 0;
		list_add_tail(&gov->governor_list, &cpuidle_governors);
		if (!cpuidle_curr_governor ||
		    !strncasecmp(param_governor, gov->name, CPUIDLE_NAME_LEN) ||
		    (cpuidle_curr_governor->rating < gov->rating &&
		     strncasecmp(param_governor, cpuidle_curr_governor->name,
				 CPUIDLE_NAME_LEN)))
			cpuidle_switch_governor(gov);
	}
	mutex_unlock(&cpuidle_lock);

	return ret;
}