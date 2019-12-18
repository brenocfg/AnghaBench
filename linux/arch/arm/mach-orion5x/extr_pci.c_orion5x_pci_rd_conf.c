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
typedef  int u32 ;
struct pci_bus {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int /*<<< orphan*/  PCI_FUNC (int) ; 
 int /*<<< orphan*/  PCI_SLOT (int) ; 
 int orion5x_pci_hw_rd_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  orion5x_pci_valid_config (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int orion5x_pci_rd_conf(struct pci_bus *bus, u32 devfn,
				int where, int size, u32 *val)
{
	if (!orion5x_pci_valid_config(bus->number, devfn)) {
		*val = 0xffffffff;
		return PCIBIOS_DEVICE_NOT_FOUND;
	}

	return orion5x_pci_hw_rd_conf(bus->number, PCI_SLOT(devfn),
					PCI_FUNC(devfn), where, size, val);
}