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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ EMMA2RH_IRQ_BASE ; 
 scalar_t__ NUM_EMMA2RH_IRQ ; 
 int /*<<< orphan*/  emma2rh_irq_controller ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler_name (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void emma2rh_irq_init(void)
{
	u32 i;

	for (i = 0; i < NUM_EMMA2RH_IRQ; i++)
		irq_set_chip_and_handler_name(EMMA2RH_IRQ_BASE + i,
					      &emma2rh_irq_controller,
					      handle_level_irq, "level");
}