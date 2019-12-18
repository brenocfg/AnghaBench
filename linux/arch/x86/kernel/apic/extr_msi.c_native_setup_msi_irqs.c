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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct irq_domain {int dummy; } ;
struct irq_alloc_info {struct pci_dev* msi_dev; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  X86_IRQ_ALLOC_TYPE_MSI ; 
 int /*<<< orphan*/  init_irq_alloc_info (struct irq_alloc_info*,int /*<<< orphan*/ *) ; 
 struct irq_domain* irq_remapping_get_irq_domain (struct irq_alloc_info*) ; 
 struct irq_domain* msi_default_domain ; 
 int msi_domain_alloc_irqs (struct irq_domain*,int /*<<< orphan*/ *,int) ; 

int native_setup_msi_irqs(struct pci_dev *dev, int nvec, int type)
{
	struct irq_domain *domain;
	struct irq_alloc_info info;

	init_irq_alloc_info(&info, NULL);
	info.type = X86_IRQ_ALLOC_TYPE_MSI;
	info.msi_dev = dev;

	domain = irq_remapping_get_irq_domain(&info);
	if (domain == NULL)
		domain = msi_default_domain;
	if (domain == NULL)
		return -ENOSYS;

	return msi_domain_alloc_irqs(domain, &dev->dev, nvec);
}