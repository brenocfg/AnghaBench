#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct pci_bus {int /*<<< orphan*/  number; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcicfgd; } ;

/* Variables and functions */
 unsigned char PCI_ACCESS_WRITE ; 
 int /*<<< orphan*/  PCI_CFG_SET (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  PCI_FUNC (unsigned int) ; 
 unsigned int PCI_SLOT (unsigned int) ; 
 TYPE_1__* rc32434_pci ; 
 int /*<<< orphan*/  rc32434_sync () ; 

__attribute__((used)) static inline int config_access(unsigned char access_type,
				struct pci_bus *bus, unsigned int devfn,
				unsigned char where, u32 *data)
{
	unsigned int slot = PCI_SLOT(devfn);
	u8 func = PCI_FUNC(devfn);

	/* Setup address */
	PCI_CFG_SET(bus->number, slot, func, where);
	rc32434_sync();

	if (access_type == PCI_ACCESS_WRITE)
		rc32434_pci->pcicfgd = *data;
	else
		*data = rc32434_pci->pcicfgd;

	rc32434_sync();

	return 0;
}