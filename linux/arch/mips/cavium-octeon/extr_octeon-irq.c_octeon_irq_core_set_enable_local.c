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
struct octeon_core_chip_data {int bit; scalar_t__ desired_en; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_c0_status (unsigned int) ; 
 struct octeon_core_chip_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  set_c0_status (unsigned int) ; 

__attribute__((used)) static void octeon_irq_core_set_enable_local(void *arg)
{
	struct irq_data *data = arg;
	struct octeon_core_chip_data *cd = irq_data_get_irq_chip_data(data);
	unsigned int mask = 0x100 << cd->bit;

	/*
	 * Interrupts are already disabled, so these are atomic.
	 */
	if (cd->desired_en)
		set_c0_status(mask);
	else
		clear_c0_status(mask);

}