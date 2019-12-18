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
struct cpuidle_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cpuidle_unregister_driver (struct cpuidle_driver*) ; 
 int /*<<< orphan*/  cpuidle_driver_lock ; 
 struct cpuidle_driver* cpuidle_get_driver () ; 
 int /*<<< orphan*/  cpuidle_lock ; 
 int /*<<< orphan*/ * cpuidle_prev_governor ; 
 int /*<<< orphan*/  cpuidle_switch_governor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void cpuidle_unregister_driver(struct cpuidle_driver *drv)
{
	bool enabled = (cpuidle_get_driver() == drv);

	spin_lock(&cpuidle_driver_lock);
	__cpuidle_unregister_driver(drv);
	spin_unlock(&cpuidle_driver_lock);

	if (!enabled)
		return;

	mutex_lock(&cpuidle_lock);
	if (cpuidle_prev_governor) {
		if (!cpuidle_switch_governor(cpuidle_prev_governor))
			cpuidle_prev_governor = NULL;
	}
	mutex_unlock(&cpuidle_lock);
}