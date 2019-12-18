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
 int /*<<< orphan*/  cpu_emergency_vmxoff () ; 
 int /*<<< orphan*/  ipi_entering_ack_irq () ; 
 int /*<<< orphan*/  irq_exit () ; 
 int /*<<< orphan*/  stop_this_cpu (int /*<<< orphan*/ *) ; 

void smp_reboot_interrupt(void)
{
	ipi_entering_ack_irq();
	cpu_emergency_vmxoff();
	stop_this_cpu(NULL);
	irq_exit();
}