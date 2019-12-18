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
struct pci_bus {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int PCI_ASSIGN_ROMS ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int pci_probe ; 
 int /*<<< orphan*/  pcibios_allocate_bus_resources (struct pci_bus*) ; 
 int /*<<< orphan*/  pcibios_allocate_resources (struct pci_bus*,int) ; 
 int /*<<< orphan*/  pcibios_allocate_rom_resources (struct pci_bus*) ; 

void pcibios_resource_survey_bus(struct pci_bus *bus)
{
	dev_printk(KERN_DEBUG, &bus->dev, "Allocating resources\n");

	pcibios_allocate_bus_resources(bus);

	pcibios_allocate_resources(bus, 0);
	pcibios_allocate_resources(bus, 1);

	if (!(pci_probe & PCI_ASSIGN_ROMS))
		pcibios_allocate_rom_resources(bus);
}