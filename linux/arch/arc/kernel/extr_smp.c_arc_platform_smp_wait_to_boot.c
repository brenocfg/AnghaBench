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
 int /*<<< orphan*/  CONFIG_ARC_SMP_HALT_ON_RESET ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int __boot_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __boot_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_flag ; 

void arc_platform_smp_wait_to_boot(int cpu)
{
	/* for halt-on-reset, we've waited already */
	if (IS_ENABLED(CONFIG_ARC_SMP_HALT_ON_RESET))
		return;

	while (__boot_read(wake_flag) != cpu)
		;

	__boot_write(wake_flag, 0);
}