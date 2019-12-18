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
struct irq_desc {int dummy; } ;
struct TYPE_2__ {unsigned short intreqr; unsigned short intenar; unsigned short intreq; } ;

/* Variables and functions */
 unsigned short IF_DSKBLK ; 
 unsigned short IF_SOFT ; 
 unsigned short IF_TBE ; 
 int /*<<< orphan*/  IRQ_AMIGA_DSKBLK ; 
 int /*<<< orphan*/  IRQ_AMIGA_SOFT ; 
 int /*<<< orphan*/  IRQ_AMIGA_TBE ; 
 TYPE_1__ amiga_custom ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ami_int1(struct irq_desc *desc)
{
	unsigned short ints = amiga_custom.intreqr & amiga_custom.intenar;

	/* if serial transmit buffer empty, interrupt */
	if (ints & IF_TBE) {
		amiga_custom.intreq = IF_TBE;
		generic_handle_irq(IRQ_AMIGA_TBE);
	}

	/* if floppy disk transfer complete, interrupt */
	if (ints & IF_DSKBLK) {
		amiga_custom.intreq = IF_DSKBLK;
		generic_handle_irq(IRQ_AMIGA_DSKBLK);
	}

	/* if software interrupt set, interrupt */
	if (ints & IF_SOFT) {
		amiga_custom.intreq = IF_SOFT;
		generic_handle_irq(IRQ_AMIGA_SOFT);
	}
}