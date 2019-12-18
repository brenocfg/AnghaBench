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
 unsigned long EIEM_MASK (unsigned int) ; 
 unsigned long cpu_eiem ; 
 int /*<<< orphan*/  smp_send_all_nop () ; 

__attribute__((used)) static void __cpu_unmask_irq(unsigned int irq)
{
	unsigned long eirr_bit = EIEM_MASK(irq);

	cpu_eiem |= eirr_bit;

	/* This is just a simple NOP IPI.  But what it does is cause
	 * all the other CPUs to do a set_eiem(cpu_eiem) at the end
	 * of the interrupt handler */
	smp_send_all_nop();
}