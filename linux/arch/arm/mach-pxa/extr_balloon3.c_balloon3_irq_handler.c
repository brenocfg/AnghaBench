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
struct irq_desc {int dummy; } ;
struct irq_data {int dummy; } ;
struct irq_chip {int /*<<< orphan*/  (* irq_ack ) (struct irq_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BALLOON3_INT_CONTROL_REG ; 
 unsigned int BALLOON3_IRQ (int /*<<< orphan*/ ) ; 
 unsigned int __ffs (unsigned long) ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 unsigned long balloon3_irq_enabled ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct irq_data* irq_desc_get_irq_data (struct irq_desc*) ; 
 int /*<<< orphan*/  stub1 (struct irq_data*) ; 

__attribute__((used)) static void balloon3_irq_handler(struct irq_desc *desc)
{
	unsigned long pending = __raw_readl(BALLOON3_INT_CONTROL_REG) &
					balloon3_irq_enabled;
	do {
		struct irq_data *d = irq_desc_get_irq_data(desc);
		struct irq_chip *chip = irq_desc_get_chip(desc);
		unsigned int irq;

		/* clear useless edge notification */
		if (chip->irq_ack)
			chip->irq_ack(d);

		while (pending) {
			irq = BALLOON3_IRQ(0) + __ffs(pending);
			generic_handle_irq(irq);
			pending &= pending - 1;
		}
		pending = __raw_readl(BALLOON3_INT_CONTROL_REG) &
				balloon3_irq_enabled;
	} while (pending);
}