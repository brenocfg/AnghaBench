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
 int /*<<< orphan*/  EM7210_HARDWARE_POWER ; 
 int gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 

void em7210_power_off(void)
{
	int ret;

	ret = gpio_direction_output(EM7210_HARDWARE_POWER, 1);
	if (ret)
		pr_crit("could not drive power off GPIO high\n");
}