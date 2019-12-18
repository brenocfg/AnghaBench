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
struct cpuidle_driver {int state_count; } ;
struct cpuidle_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpuidle_free_state_kobj (struct cpuidle_device*,int) ; 
 struct cpuidle_driver* cpuidle_get_cpu_driver (struct cpuidle_device*) ; 

__attribute__((used)) static void cpuidle_remove_state_sysfs(struct cpuidle_device *device)
{
	struct cpuidle_driver *drv = cpuidle_get_cpu_driver(device);
	int i;

	for (i = 0; i < drv->state_count; i++)
		cpuidle_free_state_kobj(device, i);
}