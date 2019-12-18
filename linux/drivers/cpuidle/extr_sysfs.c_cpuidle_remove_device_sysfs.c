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
 int /*<<< orphan*/  cpuidle_remove_driver_sysfs (struct cpuidle_device*) ; 
 int /*<<< orphan*/  cpuidle_remove_state_sysfs (struct cpuidle_device*) ; 

void cpuidle_remove_device_sysfs(struct cpuidle_device *device)
{
	cpuidle_remove_driver_sysfs(device);
	cpuidle_remove_state_sysfs(device);
}