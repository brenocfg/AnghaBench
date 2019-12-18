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
 int /*<<< orphan*/  get_irq_regs () ; 
 int in_nmi ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  show_registers (int /*<<< orphan*/ ) ; 

irqreturn_t mac_nmi_handler(int irq, void *dev_id)
{
	if (in_nmi)
		return IRQ_HANDLED;
	in_nmi = 1;

	pr_info("Non-Maskable Interrupt\n");
	show_registers(get_irq_regs());

	in_nmi = 0;
	return IRQ_HANDLED;
}