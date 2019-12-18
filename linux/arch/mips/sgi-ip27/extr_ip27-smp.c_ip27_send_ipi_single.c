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
 int /*<<< orphan*/  COMPACT_TO_NASID_NODEID (int /*<<< orphan*/ ) ; 
 int CPU_CALL_A_IRQ ; 
 int CPU_RESCHED_A_IRQ ; 
 int /*<<< orphan*/  REMOTE_HUB_SEND_INTR (int /*<<< orphan*/ ,int) ; 
#define  SMP_CALL_FUNCTION 129 
#define  SMP_RESCHEDULE_YOURSELF 128 
 int /*<<< orphan*/  cpu_to_node (int) ; 
 scalar_t__ cputoslice (int) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void ip27_send_ipi_single(int destid, unsigned int action)
{
	int irq;

	switch (action) {
	case SMP_RESCHEDULE_YOURSELF:
		irq = CPU_RESCHED_A_IRQ;
		break;
	case SMP_CALL_FUNCTION:
		irq = CPU_CALL_A_IRQ;
		break;
	default:
		panic("sendintr");
	}

	irq += cputoslice(destid);

	/*
	 * Convert the compact hub number to the NASID to get the correct
	 * part of the address space.  Then set the interrupt bit associated
	 * with the CPU we want to send the interrupt to.
	 */
	REMOTE_HUB_SEND_INTR(COMPACT_TO_NASID_NODEID(cpu_to_node(destid)), irq);
}