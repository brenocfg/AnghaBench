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
typedef  int /*<<< orphan*/  u32 ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PCI_CONFIG_DATA ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_virtio_guest_write_config_addr (struct pci_bus*,unsigned int,int) ; 

__attribute__((used)) static int pci_virtio_guest_read_config(struct pci_bus *bus, unsigned int devfn,
					int reg, int size, u32 *val)
{
	pci_virtio_guest_write_config_addr(bus, devfn, reg);

	switch (size) {
	case 1:
		*val = inb(PCI_CONFIG_DATA + (reg & 3));
		break;
	case 2:
		*val = inw(PCI_CONFIG_DATA + (reg & 2));
		break;
	case 4:
		*val = inl(PCI_CONFIG_DATA);
		break;
	}
	return PCIBIOS_SUCCESSFUL;
}