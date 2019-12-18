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
 int /*<<< orphan*/  DBG (char*,int,...) ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PCI_FUNC (unsigned int) ; 
 int /*<<< orphan*/  PCI_SLOT (unsigned int) ; 
 int /*<<< orphan*/  mkaddr (struct pci_bus*,unsigned int,int) ; 
 int /*<<< orphan*/  pci_lock ; 
 int read_cfgdata () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_cfgaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cfgdata (int) ; 

__attribute__((used)) static int pci_config_write(struct pci_bus *bus, unsigned int devfn, int where,
		int size, u32 val)
{
	unsigned long flags;
	u32 data;
	int s;

	spin_lock_irqsave(&pci_lock, flags);

	write_cfgaddr(mkaddr(bus, devfn, where));
	data = read_cfgdata();

	DBG("PCI: cfg_write %02u.%02u.%01u/%02X:%01d, cfg:0x%08X",
		bus->number, PCI_SLOT(devfn), PCI_FUNC(devfn),
		where, size, data);

	switch (size) {
	case 1:
		s = ((where & 3) << 3);
		data &= ~(0xFF << s);
		data |= ((val & 0xFF) << s);
		break;
	case 2:
		s = ((where & 2) << 4);
		data &= ~(0xFFFF << s);
		data |= ((val & 0xFFFF) << s);
		break;
	case 4:
		data = val;
		break;
	}

	write_cfgdata(data);
	DBG(", 0x%08X written\n", data);

	spin_unlock_irqrestore(&pci_lock, flags);

	return PCIBIOS_SUCCESSFUL;
}