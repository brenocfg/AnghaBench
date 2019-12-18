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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int acpi_pci_irq_enable (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_dev_msi_enabled (struct pci_dev*) ; 
 int pci_enable_resources (struct pci_dev*,int) ; 

int
pcibios_enable_device (struct pci_dev *dev, int mask)
{
	int ret;

	ret = pci_enable_resources(dev, mask);
	if (ret < 0)
		return ret;

	if (!pci_dev_msi_enabled(dev))
		return acpi_pci_irq_enable(dev);
	return 0;
}