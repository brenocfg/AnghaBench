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
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
 unsigned long INTC_INTDSB_0 ; 
 unsigned long INTC_INTDSB_1 ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,unsigned long) ; 

__attribute__((used)) static void disable_intc_irq(struct irq_data *data)
{
	unsigned int irq = data->irq;
	unsigned long reg;
	unsigned long bitmask;

	if (irq < 32) {
		reg = INTC_INTDSB_0;
		bitmask = 1 << irq;
	} else {
		reg = INTC_INTDSB_1;
		bitmask = 1 << (irq - 32);
	}

	__raw_writel(bitmask, reg);
}