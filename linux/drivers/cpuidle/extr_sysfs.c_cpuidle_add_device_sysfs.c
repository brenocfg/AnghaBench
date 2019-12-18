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
struct cpuidle_device {int dummy; } ;

/* Variables and functions */
 int cpuidle_add_driver_sysfs (struct cpuidle_device*) ; 
 int cpuidle_add_state_sysfs (struct cpuidle_device*) ; 
 int /*<<< orphan*/  cpuidle_remove_state_sysfs (struct cpuidle_device*) ; 

int cpuidle_add_device_sysfs(struct cpuidle_device *device)
{
	int ret;

	ret = cpuidle_add_state_sysfs(device);
	if (ret)
		return ret;

	ret = cpuidle_add_driver_sysfs(device);
	if (ret)
		cpuidle_remove_state_sysfs(device);
	return ret;
}