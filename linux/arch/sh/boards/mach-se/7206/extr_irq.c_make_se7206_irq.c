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

/* Variables and functions */
 int /*<<< orphan*/  disable_irq_nosync (unsigned int) ; 
 int /*<<< orphan*/  disable_se7206_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_get_irq_data (unsigned int) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler_name (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  se7206_irq_chip ; 

__attribute__((used)) static void make_se7206_irq(unsigned int irq)
{
	disable_irq_nosync(irq);
	irq_set_chip_and_handler_name(irq, &se7206_irq_chip,
				      handle_level_irq, "level");
	disable_se7206_irq(irq_get_irq_data(irq));
}