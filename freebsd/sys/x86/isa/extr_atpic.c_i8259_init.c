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
struct atpic {int at_ioaddr; int at_intbase; int at_imen; } ;

/* Variables and functions */
 int ICU_IMR_OFFSET ; 
 int ICU_SLAVEID ; 
 int ICW1_IC4 ; 
 int ICW1_RESET ; 
 int IRQ_MASK (int) ; 
 int MASTER_MODE ; 
 int OCW2_L1 ; 
 int OCW2_R ; 
 int OCW2_SL ; 
 int OCW3_RR ; 
 int OCW3_SEL ; 
 int SLAVE_MODE ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  spinlock_enter () ; 
 int /*<<< orphan*/  spinlock_exit () ; 

__attribute__((used)) static void
i8259_init(struct atpic *pic, int slave)
{
	int imr_addr;

	/* Reset the PIC and program with next four bytes. */
	spinlock_enter();
	outb(pic->at_ioaddr, ICW1_RESET | ICW1_IC4);
	imr_addr = pic->at_ioaddr + ICU_IMR_OFFSET;

	/* Start vector. */
	outb(imr_addr, pic->at_intbase);

	/*
	 * Setup slave links.  For the master pic, indicate what line
	 * the slave is configured on.  For the slave indicate
	 * which line on the master we are connected to.
	 */
	if (slave)
		outb(imr_addr, ICU_SLAVEID);
	else
		outb(imr_addr, IRQ_MASK(ICU_SLAVEID));

	/* Set mode. */
	if (slave)
		outb(imr_addr, SLAVE_MODE);
	else
		outb(imr_addr, MASTER_MODE);

	/* Set interrupt enable mask. */
	outb(imr_addr, pic->at_imen);

	/* Reset is finished, default to IRR on read. */
	outb(pic->at_ioaddr, OCW3_SEL | OCW3_RR);

	/* OCW2_L1 sets priority order to 3-7, 0-2 (com2 first). */
	if (!slave)
		outb(pic->at_ioaddr, OCW2_R | OCW2_SL | OCW2_L1);

	spinlock_exit();
}