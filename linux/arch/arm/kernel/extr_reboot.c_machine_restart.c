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
 int /*<<< orphan*/  arm_pm_restart (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  do_kernel_restart (char*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  reboot_mode ; 
 int /*<<< orphan*/  smp_send_stop () ; 

void machine_restart(char *cmd)
{
	local_irq_disable();
	smp_send_stop();

	if (arm_pm_restart)
		arm_pm_restart(reboot_mode, cmd);
	else
		do_kernel_restart(cmd);

	/* Give a grace period for failure to restart of 1s */
	mdelay(1000);

	/* Whoops - the platform was unable to reboot. Tell the user! */
	printk("Reboot failed -- System halted\n");
	while (1);
}