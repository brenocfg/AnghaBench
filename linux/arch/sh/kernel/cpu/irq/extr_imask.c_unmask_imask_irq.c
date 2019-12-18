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
 scalar_t__ IMASK_PRIORITY ; 
 scalar_t__ find_first_zero_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  imask_mask ; 
 scalar_t__ interrupt_priority ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_interrupt_registers (scalar_t__) ; 

__attribute__((used)) static void unmask_imask_irq(struct irq_data *data)
{
	unsigned int irq = data->irq;

	set_bit(irq, imask_mask);
	interrupt_priority = IMASK_PRIORITY -
		find_first_zero_bit(imask_mask, IMASK_PRIORITY);
	set_interrupt_registers(interrupt_priority);
}