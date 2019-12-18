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
struct irq_data {int irq; } ;

/* Variables and functions */
 int ADM5120_INTC_IRQ_BASE ; 
 int /*<<< orphan*/  INTC_REG_IRQ_DISABLE ; 
 int /*<<< orphan*/  intc_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void adm5120_intc_irq_mask(struct irq_data *d)
{
	intc_write_reg(INTC_REG_IRQ_DISABLE, 1 << (d->irq - ADM5120_INTC_IRQ_BASE));
}