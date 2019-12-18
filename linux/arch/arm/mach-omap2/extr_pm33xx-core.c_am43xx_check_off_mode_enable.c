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
 int enable_off_mode ; 
 scalar_t__ of_machine_is_compatible (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int am43xx_check_off_mode_enable(void)
{
	/*
	 * Check for am437x-gp-evm which has the right Hardware design to
	 * support this mode reliably.
	 */
	if (of_machine_is_compatible("ti,am437x-gp-evm") && enable_off_mode)
		return enable_off_mode;
	else if (enable_off_mode)
		pr_warn("WARNING: This platform does not support off-mode, entering DeepSleep suspend.\n");

	return 0;
}