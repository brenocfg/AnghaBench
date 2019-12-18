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
typedef  int u8 ;
struct TYPE_2__ {int istat1; int imask1; int vmeistat; int cmeimask1; } ;

/* Variables and functions */
 int SGINT_ISTAT1_LIO3 ; 
 int /*<<< orphan*/  do_IRQ (int) ; 
 int* lc1msk_to_irqnr ; 
 int* lc3msk_to_irqnr ; 
 TYPE_1__* sgint ; 

__attribute__((used)) static void indy_local1_irqdispatch(void)
{
	u8 mask = sgint->istat1 & sgint->imask1;
	u8 mask2;
	int irq;

	if (mask & SGINT_ISTAT1_LIO3) {
		mask2 = sgint->vmeistat & sgint->cmeimask1;
		irq = lc3msk_to_irqnr[mask2];
	} else
		irq = lc1msk_to_irqnr[mask];

	/* if irq == 0, then the interrupt has already been cleared */
	if (irq)
		do_IRQ(irq);
}