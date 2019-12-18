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
struct irq_domain {int dummy; } ;
struct irq_desc {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq_data; } ;
struct irq_chip {int /*<<< orphan*/  (* irq_unmask ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* irq_ack ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* irq_mask ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 unsigned int __hlwd_pic_get_irq (struct irq_domain*) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct irq_domain* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  irqd_irq_disabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hlwd_pic_irq_cascade(struct irq_desc *desc)
{
	struct irq_chip *chip = irq_desc_get_chip(desc);
	struct irq_domain *irq_domain = irq_desc_get_handler_data(desc);
	unsigned int virq;

	raw_spin_lock(&desc->lock);
	chip->irq_mask(&desc->irq_data); /* IRQ_LEVEL */
	raw_spin_unlock(&desc->lock);

	virq = __hlwd_pic_get_irq(irq_domain);
	if (virq)
		generic_handle_irq(virq);
	else
		pr_err("spurious interrupt!\n");

	raw_spin_lock(&desc->lock);
	chip->irq_ack(&desc->irq_data); /* IRQ_LEVEL */
	if (!irqd_irq_disabled(&desc->irq_data) && chip->irq_unmask)
		chip->irq_unmask(&desc->irq_data);
	raw_spin_unlock(&desc->lock);
}