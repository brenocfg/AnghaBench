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
 unsigned short IF_DSKSYN ; 
 unsigned short IF_RBF ; 
 int /*<<< orphan*/  IRQ_AMIGA_DSKSYN ; 
 int /*<<< orphan*/  IRQ_AMIGA_RBF ; 
 TYPE_1__ amiga_custom ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ami_int5(struct irq_desc *desc)
{
	unsigned short ints = amiga_custom.intreqr & amiga_custom.intenar;

	/* if serial receive buffer full interrupt */
	if (ints & IF_RBF) {
		/* acknowledge of IF_RBF must be done by the serial interrupt */
		generic_handle_irq(IRQ_AMIGA_RBF);
	}

	/* if a disk sync interrupt */
	if (ints & IF_DSKSYN) {
		amiga_custom.intreq = IF_DSKSYN;
		generic_handle_irq(IRQ_AMIGA_DSKSYN);
	}
}