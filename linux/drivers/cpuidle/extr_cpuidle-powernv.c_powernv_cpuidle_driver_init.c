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
struct cpumask {int dummy; } ;
struct cpuidle_driver {size_t state_count; struct cpumask* cpumask; TYPE_1__* states; } ;
struct TYPE_2__ {int /*<<< orphan*/ * enter; } ;

/* Variables and functions */
 scalar_t__ cpu_present_mask ; 
 TYPE_1__* cpuidle_state_table ; 
 int max_idle_state ; 
 struct cpuidle_driver powernv_idle_driver ; 

__attribute__((used)) static int powernv_cpuidle_driver_init(void)
{
	int idle_state;
	struct cpuidle_driver *drv = &powernv_idle_driver;

	drv->state_count = 0;

	for (idle_state = 0; idle_state < max_idle_state; ++idle_state) {
		/* Is the state not enabled? */
		if (cpuidle_state_table[idle_state].enter == NULL)
			continue;

		drv->states[drv->state_count] =	/* structure copy */
			cpuidle_state_table[idle_state];

		drv->state_count += 1;
	}

	/*
	 * On the PowerNV platform cpu_present may be less than cpu_possible in
	 * cases when firmware detects the CPU, but it is not available to the
	 * OS.  If CONFIG_HOTPLUG_CPU=n, then such CPUs are not hotplugable at
	 * run time and hence cpu_devices are not created for those CPUs by the
	 * generic topology_init().
	 *
	 * drv->cpumask defaults to cpu_possible_mask in
	 * __cpuidle_driver_init().  This breaks cpuidle on PowerNV where
	 * cpu_devices are not created for CPUs in cpu_possible_mask that
	 * cannot be hot-added later at run time.
	 *
	 * Trying cpuidle_register_device() on a CPU without a cpu_device is
	 * incorrect, so pass a correct CPU mask to the generic cpuidle driver.
	 */

	drv->cpumask = (struct cpumask *)cpu_present_mask;

	return 0;
}