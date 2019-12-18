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
struct menu_device {int needs_update; int /*<<< orphan*/  tick_wakeup; } ;
struct cpuidle_device {int last_state_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  menu_devices ; 
 struct menu_device* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tick_nohz_idle_got_tick () ; 

__attribute__((used)) static void menu_reflect(struct cpuidle_device *dev, int index)
{
	struct menu_device *data = this_cpu_ptr(&menu_devices);

	dev->last_state_idx = index;
	data->needs_update = 1;
	data->tick_wakeup = tick_nohz_idle_got_tick();
}