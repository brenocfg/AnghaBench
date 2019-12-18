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
 scalar_t__ ICU_IMR_OFFSET ; 
 int ICU_SLAVEID ; 
 int ICW1_IC4 ; 
 int ICW1_RESET ; 
 int IDT_IO_INTS ; 
 scalar_t__ IO_ICU1 ; 
 scalar_t__ IO_ICU2 ; 
 int IRQ_MASK (int) ; 
 int MASTER_MODE ; 
 int OCW3_RR ; 
 int OCW3_SEL ; 
 int SLAVE_MODE ; 
 int /*<<< orphan*/  outb (scalar_t__,int) ; 

void
atpic_reset(void)
{

	outb(IO_ICU1, ICW1_RESET | ICW1_IC4);
	outb(IO_ICU1 + ICU_IMR_OFFSET, IDT_IO_INTS);
	outb(IO_ICU1 + ICU_IMR_OFFSET, IRQ_MASK(ICU_SLAVEID));
	outb(IO_ICU1 + ICU_IMR_OFFSET, MASTER_MODE);
	outb(IO_ICU1 + ICU_IMR_OFFSET, 0xff);
	outb(IO_ICU1, OCW3_SEL | OCW3_RR);

	outb(IO_ICU2, ICW1_RESET | ICW1_IC4);
	outb(IO_ICU2 + ICU_IMR_OFFSET, IDT_IO_INTS + 8);
	outb(IO_ICU2 + ICU_IMR_OFFSET, ICU_SLAVEID);
	outb(IO_ICU2 + ICU_IMR_OFFSET, SLAVE_MODE);
	outb(IO_ICU2 + ICU_IMR_OFFSET, 0xff);
	outb(IO_ICU2, OCW3_SEL | OCW3_RR);
}