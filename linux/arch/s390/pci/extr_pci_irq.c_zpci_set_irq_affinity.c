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
struct msi_msg {int address_lo; } ;
struct msi_desc {struct msi_msg msg; } ;
struct irq_data {int /*<<< orphan*/  irq; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int IRQ_SET_MASK_OK ; 
 int cpumask_first (struct cpumask const*) ; 
 struct msi_desc* irq_get_msi_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_msi_msg (int /*<<< orphan*/ ,struct msi_msg*) ; 

__attribute__((used)) static int zpci_set_irq_affinity(struct irq_data *data, const struct cpumask *dest,
				 bool force)
{
	struct msi_desc *entry = irq_get_msi_desc(data->irq);
	struct msi_msg msg = entry->msg;

	msg.address_lo &= 0xff0000ff;
	msg.address_lo |= (cpumask_first(dest) << 8);
	pci_write_msi_msg(data->irq, &msg);

	return IRQ_SET_MASK_OK;
}