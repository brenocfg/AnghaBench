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
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PCI_FUNC (unsigned int) ; 
 int /*<<< orphan*/  PCI_SLOT (unsigned int) ; 
 int /*<<< orphan*/  RT2880_PCI_REG_CONFIG_ADDR ; 
 int /*<<< orphan*/  RT2880_PCI_REG_CONFIG_DATA ; 
 int rt2880_pci_get_cfgaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2880_pci_lock ; 
 int rt2880_pci_reg_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2880_pci_reg_write (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int rt2880_pci_config_read(struct pci_bus *bus, unsigned int devfn,
				  int where, int size, u32 *val)
{
	unsigned long flags;
	u32 address;
	u32 data;

	address = rt2880_pci_get_cfgaddr(bus->number, PCI_SLOT(devfn),
					 PCI_FUNC(devfn), where);

	spin_lock_irqsave(&rt2880_pci_lock, flags);
	rt2880_pci_reg_write(address, RT2880_PCI_REG_CONFIG_ADDR);
	data = rt2880_pci_reg_read(RT2880_PCI_REG_CONFIG_DATA);
	spin_unlock_irqrestore(&rt2880_pci_lock, flags);

	switch (size) {
	case 1:
		*val = (data >> ((where & 3) << 3)) & 0xff;
		break;
	case 2:
		*val = (data >> ((where & 3) << 3)) & 0xffff;
		break;
	case 4:
		*val = data;
		break;
	}

	return PCIBIOS_SUCCESSFUL;
}