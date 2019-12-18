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
struct pci_dev {int /*<<< orphan*/  enable_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_pci_irq_disable (struct pci_dev*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_msi_enabled (struct pci_dev*) ; 

void
pcibios_disable_device (struct pci_dev *dev)
{
	BUG_ON(atomic_read(&dev->enable_cnt));
	if (!pci_dev_msi_enabled(dev))
		acpi_pci_irq_disable(dev);
}