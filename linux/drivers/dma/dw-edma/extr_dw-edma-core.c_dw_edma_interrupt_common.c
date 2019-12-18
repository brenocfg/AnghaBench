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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dw_edma_interrupt (int,void*,int) ; 

__attribute__((used)) static irqreturn_t dw_edma_interrupt_common(int irq, void *data)
{
	dw_edma_interrupt(irq, data, true);
	dw_edma_interrupt(irq, data, false);

	return IRQ_HANDLED;
}