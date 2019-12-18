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
typedef  enum reboot_mode { ____Placeholder_reboot_mode } reboot_mode ;

/* Variables and functions */
 int /*<<< orphan*/  N2100_HARDWARE_RESET ; 
 int gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 

__attribute__((used)) static void n2100_restart(enum reboot_mode mode, const char *cmd)
{
	int ret;

	ret = gpio_direction_output(N2100_HARDWARE_RESET, 0);
	if (ret) {
		pr_crit("could not drive reset GPIO low\n");
		return;
	}
	/* Wait for reset to happen */
	while (1)
		;
}