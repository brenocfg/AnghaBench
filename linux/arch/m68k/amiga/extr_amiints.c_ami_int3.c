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
 unsigned short IF_BLIT ; 
 unsigned short IF_COPER ; 
 unsigned short IF_VERTB ; 
 int /*<<< orphan*/  IRQ_AMIGA_BLIT ; 
 int /*<<< orphan*/  IRQ_AMIGA_COPPER ; 
 int /*<<< orphan*/  IRQ_AMIGA_VERTB ; 
 TYPE_1__ amiga_custom ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ami_int3(struct irq_desc *desc)
{
	unsigned short ints = amiga_custom.intreqr & amiga_custom.intenar;

	/* if a blitter interrupt */
	if (ints & IF_BLIT) {
		amiga_custom.intreq = IF_BLIT;
		generic_handle_irq(IRQ_AMIGA_BLIT);
	}

	/* if a copper interrupt */
	if (ints & IF_COPER) {
		amiga_custom.intreq = IF_COPER;
		generic_handle_irq(IRQ_AMIGA_COPPER);
	}

	/* if a vertical blank interrupt */
	if (ints & IF_VERTB) {
		amiga_custom.intreq = IF_VERTB;
		generic_handle_irq(IRQ_AMIGA_VERTB);
	}
}