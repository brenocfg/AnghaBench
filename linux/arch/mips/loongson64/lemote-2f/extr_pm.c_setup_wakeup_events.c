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
 int I8042_KBD_IRQ ; 
#define  MACH_LEMOTE_ML2F7 129 
#define  MACH_LEMOTE_YL2F89 128 
 int PIC_CASCADE_IR ; 
 int /*<<< orphan*/  PIC_MASTER_IMR ; 
 int /*<<< orphan*/  PIC_SLAVE_IMR ; 
 int /*<<< orphan*/  SCI_IRQ_NUM ; 
 int /*<<< orphan*/  i8042_enable_kbd_port () ; 
 int inb (int /*<<< orphan*/ ) ; 
 int mips_machtype ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

void setup_wakeup_events(void)
{
	int irq_mask;

	switch (mips_machtype) {
	case MACH_LEMOTE_ML2F7:
	case MACH_LEMOTE_YL2F89:
		/* open the keyboard irq in i8259A */
		outb((0xff & ~(1 << I8042_KBD_IRQ)), PIC_MASTER_IMR);
		irq_mask = inb(PIC_MASTER_IMR);

		/* enable keyboard port */
		i8042_enable_kbd_port();

		/* Wakeup CPU via SCI lid open event */
		outb(irq_mask & ~(1 << PIC_CASCADE_IR), PIC_MASTER_IMR);
		inb(PIC_MASTER_IMR);
		outb(0xff & ~(1 << (SCI_IRQ_NUM - 8)), PIC_SLAVE_IMR);
		inb(PIC_SLAVE_IMR);

		break;

	default:
		break;
	}
}