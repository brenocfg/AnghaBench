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
struct cpuidle_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_do_idle () ; 

__attribute__((used)) static int zynq_enter_idle(struct cpuidle_device *dev,
			   struct cpuidle_driver *drv, int index)
{
	/* Add code for DDR self refresh start */
	cpu_do_idle();

	return index;
}