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
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  do_IRQ (int) ; 
 int sni_rm200_i8259_irq () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t sni_rm200_i8259A_irq_handler(int dummy, void *p)
{
	int irq;

	irq = sni_rm200_i8259_irq();
	if (unlikely(irq < 0))
		return IRQ_NONE;

	do_IRQ(irq);
	return IRQ_HANDLED;
}