#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct trapframe {int dummy; } ;
struct intsrc {scalar_t__ is_pic; int /*<<< orphan*/ * is_event; } ;
struct atpic {int at_ioaddr; } ;
struct TYPE_2__ {struct intsrc at_intsrc; } ;

/* Variables and functions */
 int IRQ_MASK (int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 size_t NUM_ISA_IRQS ; 
 int OCW3_RIS ; 
 int OCW3_RR ; 
 int OCW3_SEL ; 
 TYPE_1__* atintrs ; 
 int inb (int) ; 
 int /*<<< orphan*/  intr_execute_handlers (struct intsrc*,struct trapframe*) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  spinlock_enter () ; 
 int /*<<< orphan*/  spinlock_exit () ; 

void
atpic_handle_intr(u_int vector, struct trapframe *frame)
{
	struct intsrc *isrc;

	KASSERT(vector < NUM_ISA_IRQS, ("unknown int %u\n", vector));
	isrc = &atintrs[vector].at_intsrc;

	/*
	 * If we don't have an event, see if this is a spurious
	 * interrupt.
	 */
	if (isrc->is_event == NULL && (vector == 7 || vector == 15)) {
		int port, isr;

		/*
		 * Read the ISR register to see if IRQ 7/15 is really
		 * pending.  Reset read register back to IRR when done.
		 */
		port = ((struct atpic *)isrc->is_pic)->at_ioaddr;
		spinlock_enter();
		outb(port, OCW3_SEL | OCW3_RR | OCW3_RIS);
		isr = inb(port);
		outb(port, OCW3_SEL | OCW3_RR);
		spinlock_exit();
		if ((isr & IRQ_MASK(7)) == 0)
			return;
	}
	intr_execute_handlers(isrc, frame);
}