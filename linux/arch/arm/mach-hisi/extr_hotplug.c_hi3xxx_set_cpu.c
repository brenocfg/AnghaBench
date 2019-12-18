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
 scalar_t__ HI3620_CTRL ; 
 int /*<<< orphan*/  ctrl_base ; 
 scalar_t__ hi3xxx_hotplug_init () ; 
 scalar_t__ id ; 
 int /*<<< orphan*/  set_cpu_hi3620 (int,int) ; 

void hi3xxx_set_cpu(int cpu, bool enable)
{
	if (!ctrl_base) {
		if (hi3xxx_hotplug_init() < 0)
			return;
	}

	if (id == HI3620_CTRL)
		set_cpu_hi3620(cpu, enable);
}