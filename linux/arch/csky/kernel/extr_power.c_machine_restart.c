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
 int /*<<< orphan*/  do_kernel_restart (char*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 

void machine_restart(char *cmd)
{
	local_irq_disable();
	do_kernel_restart(cmd);
	asm volatile ("bkpt");
}