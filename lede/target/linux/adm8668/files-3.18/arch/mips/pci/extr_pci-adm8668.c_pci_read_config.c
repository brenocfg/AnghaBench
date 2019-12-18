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
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  mkaddr (struct pci_bus*,unsigned int,int) ; 
 int /*<<< orphan*/  pci_lock ; 
 int read_cfgdata () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_cfgaddr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci_read_config(struct pci_bus *bus, unsigned int devfn,
				int where, int size, u32 *val)
{
	unsigned long flags;
	u32 data;

	spin_lock_irqsave(&pci_lock, flags);
	write_cfgaddr(mkaddr(bus, devfn, where));
	data = read_cfgdata();

	switch (size) {
	case 1:
		if (where & 1)
			data >>= 8;
		if (where & 2)
			data >>= 16;
		data &= 0xff;
		break;
	case 2:
		if (where & 2)
			data >>= 16;
		data &= 0xffff;
		break;
	}

	*val = data;

	spin_unlock_irqrestore(&pci_lock, flags);

	return PCIBIOS_SUCCESSFUL;
}