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
 int /*<<< orphan*/  DNS323_GPIO_POWER_OFF ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void dns323b_power_off(void)
{
	pr_info("DNS-323: Triggering power-off...\n");
	/* Pin has to be changed to 1 and back to 0 to do actual power off. */
	gpio_set_value(DNS323_GPIO_POWER_OFF, 1);
	mdelay(100);
	gpio_set_value(DNS323_GPIO_POWER_OFF, 0);
}