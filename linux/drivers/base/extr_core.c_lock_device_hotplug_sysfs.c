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

/* Variables and functions */
 int /*<<< orphan*/  device_hotplug_lock ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ mutex_trylock (int /*<<< orphan*/ *) ; 
 int restart_syscall () ; 

int lock_device_hotplug_sysfs(void)
{
	if (mutex_trylock(&device_hotplug_lock))
		return 0;

	/* Avoid busy looping (5 ms of sleep should do). */
	msleep(5);
	return restart_syscall();
}