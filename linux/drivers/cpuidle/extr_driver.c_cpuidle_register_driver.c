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
struct cpuidle_governor {int dummy; } ;
struct cpuidle_driver {scalar_t__ governor; } ;

/* Variables and functions */
 int __cpuidle_register_driver (struct cpuidle_driver*) ; 
 int /*<<< orphan*/ * cpuidle_curr_governor ; 
 int /*<<< orphan*/  cpuidle_driver_lock ; 
 struct cpuidle_governor* cpuidle_find_governor (scalar_t__) ; 
 struct cpuidle_driver* cpuidle_get_driver () ; 
 int /*<<< orphan*/  cpuidle_lock ; 
 int /*<<< orphan*/ * cpuidle_prev_governor ; 
 scalar_t__ cpuidle_switch_governor (struct cpuidle_governor*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  param_governor ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

int cpuidle_register_driver(struct cpuidle_driver *drv)
{
	struct cpuidle_governor *gov;
	int ret;

	spin_lock(&cpuidle_driver_lock);
	ret = __cpuidle_register_driver(drv);
	spin_unlock(&cpuidle_driver_lock);

	if (!ret && !strlen(param_governor) && drv->governor &&
	    (cpuidle_get_driver() == drv)) {
		mutex_lock(&cpuidle_lock);
		gov = cpuidle_find_governor(drv->governor);
		if (gov) {
			cpuidle_prev_governor = cpuidle_curr_governor;
			if (cpuidle_switch_governor(gov) < 0)
				cpuidle_prev_governor = NULL;
		}
		mutex_unlock(&cpuidle_lock);
	}

	return ret;
}