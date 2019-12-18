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
 int /*<<< orphan*/  _machine_restart (char*) ; 
 int /*<<< orphan*/  do_kernel_restart (char*) ; 
 int /*<<< orphan*/  machine_hang () ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  smp_send_stop () ; 

void machine_restart(char *command)
{
	if (_machine_restart)
		_machine_restart(command);

#ifdef CONFIG_SMP
	preempt_disable();
	smp_send_stop();
#endif
	do_kernel_restart(command);
	mdelay(1000);
	pr_emerg("Reboot failed -- System halted\n");
	machine_hang();
}