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
struct mp_chip_data {scalar_t__ count; scalar_t__ isa_irq; } ;
struct irq_data {struct mp_chip_data* chip_data; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioapic_mutex ; 
 int /*<<< orphan*/  irq_domain_free_irqs (int,int) ; 
 struct irq_data* irq_get_irq_data (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mp_unmap_irq(int irq)
{
	struct irq_data *irq_data = irq_get_irq_data(irq);
	struct mp_chip_data *data;

	if (!irq_data || !irq_data->domain)
		return;

	data = irq_data->chip_data;
	if (!data || data->isa_irq)
		return;

	mutex_lock(&ioapic_mutex);
	if (--data->count == 0)
		irq_domain_free_irqs(irq, 1);
	mutex_unlock(&ioapic_mutex);
}