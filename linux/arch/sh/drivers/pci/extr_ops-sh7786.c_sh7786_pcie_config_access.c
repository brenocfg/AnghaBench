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
struct pci_channel {int dummy; } ;
struct pci_bus {int number; int /*<<< orphan*/  parent; struct pci_channel* sysdata; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_FUNC_NOT_SUPPORTED ; 
 int PCIBIOS_SUCCESSFUL ; 
 unsigned char PCI_ACCESS_READ ; 
 int PCI_FUNC (unsigned int) ; 
 int /*<<< orphan*/  PCI_REG (int) ; 
 int PCI_SLOT (unsigned int) ; 
 int /*<<< orphan*/  SH4A_PCIEERRFR ; 
 int /*<<< orphan*/  SH4A_PCIEPAR ; 
 int /*<<< orphan*/  SH4A_PCIEPCICONF1 ; 
 int /*<<< orphan*/  SH4A_PCIEPCTLR ; 
 int /*<<< orphan*/  SH4A_PCIEPDR ; 
 scalar_t__ pci_is_root_bus (struct pci_bus*) ; 
 int pci_read_reg (struct pci_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_reg (struct pci_channel*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh7786_pcie_config_access(unsigned char access_type,
		struct pci_bus *bus, unsigned int devfn, int where, u32 *data)
{
	struct pci_channel *chan = bus->sysdata;
	int dev, func, type, reg;

	dev = PCI_SLOT(devfn);
	func = PCI_FUNC(devfn);
	type = !!bus->parent;
	reg = where & ~3;

	if (bus->number > 255 || dev > 31 || func > 7)
		return PCIBIOS_FUNC_NOT_SUPPORTED;

	/*
	 * While each channel has its own memory-mapped extended config
	 * space, it's generally only accessible when in endpoint mode.
	 * When in root complex mode, the controller is unable to target
	 * itself with either type 0 or type 1 accesses, and indeed, any
	 * controller initiated target transfer to its own config space
	 * result in a completer abort.
	 *
	 * Each channel effectively only supports a single device, but as
	 * the same channel <-> device access works for any PCI_SLOT()
	 * value, we cheat a bit here and bind the controller's config
	 * space to devfn 0 in order to enable self-enumeration. In this
	 * case the regular PAR/PDR path is sidelined and the mangled
	 * config access itself is initiated as a SuperHyway transaction.
	 */
	if (pci_is_root_bus(bus)) {
		if (dev == 0) {
			if (access_type == PCI_ACCESS_READ)
				*data = pci_read_reg(chan, PCI_REG(reg));
			else
				pci_write_reg(chan, *data, PCI_REG(reg));

			return PCIBIOS_SUCCESSFUL;
		} else if (dev > 1)
			return PCIBIOS_DEVICE_NOT_FOUND;
	}

	/* Clear errors */
	pci_write_reg(chan, pci_read_reg(chan, SH4A_PCIEERRFR), SH4A_PCIEERRFR);

	/* Set the PIO address */
	pci_write_reg(chan, (bus->number << 24) | (dev << 19) |
				(func << 16) | reg, SH4A_PCIEPAR);

	/* Enable the configuration access */
	pci_write_reg(chan, (1 << 31) | (type << 8), SH4A_PCIEPCTLR);

	/* Check for errors */
	if (pci_read_reg(chan, SH4A_PCIEERRFR) & 0x10)
		return PCIBIOS_DEVICE_NOT_FOUND;

	/* Check for master and target aborts */
	if (pci_read_reg(chan, SH4A_PCIEPCICONF1) & ((1 << 29) | (1 << 28)))
		return PCIBIOS_DEVICE_NOT_FOUND;

	if (access_type == PCI_ACCESS_READ)
		*data = pci_read_reg(chan, SH4A_PCIEPDR);
	else
		pci_write_reg(chan, *data, SH4A_PCIEPDR);

	/* Disable the configuration access */
	pci_write_reg(chan, 0, SH4A_PCIEPCTLR);

	return PCIBIOS_SUCCESSFUL;
}