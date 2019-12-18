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
struct irq_data {int dummy; } ;
struct core_chip_data {unsigned int bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_c0_cause (int) ; 
 int /*<<< orphan*/  clear_c0_status (int) ; 
 struct core_chip_data* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static void irq_core_ack(struct irq_data *data)
{
	struct core_chip_data *cd = irq_data_get_irq_chip_data(data);
	unsigned int bit = cd->bit;

	/*
	 * We don't need to disable IRQs to make these atomic since
	 * they are already disabled earlier in the low level
	 * interrupt code.
	 */
	clear_c0_status(0x100 << bit);
	/* The two user interrupts must be cleared manually. */
	if (bit < 2)
		clear_c0_cause(0x100 << bit);
}