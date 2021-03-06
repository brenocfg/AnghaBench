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
struct irq_data {int hwirq; } ;

/* Variables and functions */
 int ARCV2_IRQ_DEF_PRIO ; 
 int /*<<< orphan*/  AUX_IRQ_ENABLE ; 
 int /*<<< orphan*/  AUX_IRQ_PRIORITY ; 
 int /*<<< orphan*/  AUX_IRQ_SELECT ; 
 int /*<<< orphan*/  write_aux_reg (int /*<<< orphan*/ ,int) ; 

void arcv2_irq_enable(struct irq_data *data)
{
	/* set default priority */
	write_aux_reg(AUX_IRQ_SELECT, data->hwirq);
	write_aux_reg(AUX_IRQ_PRIORITY, ARCV2_IRQ_DEF_PRIO);

	/*
	 * hw auto enables (linux unmask) all by default
	 * So no need to do IRQ_ENABLE here
	 * XXX: However OSCI LAN need it
	 */
	write_aux_reg(AUX_IRQ_ENABLE, 1);
}