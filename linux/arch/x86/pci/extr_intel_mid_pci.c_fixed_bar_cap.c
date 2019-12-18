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
typedef  int u32 ;
struct pci_bus {int /*<<< orphan*/  number; } ;
struct TYPE_2__ {scalar_t__ (* read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int,int*) ;} ;

/* Variables and functions */
 int PCIE_CAP_OFFSET ; 
 int PCIE_VNDR_CAP_ID_FIXED_BAR ; 
 int PCI_EXT_CAP_ID (int) ; 
 int PCI_EXT_CAP_ID_VNDR ; 
 int PCI_EXT_CAP_NEXT (int) ; 
 int /*<<< orphan*/  pci_domain_nr (struct pci_bus*) ; 
 TYPE_1__* raw_pci_ext_ops ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int,int*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int,int*) ; 

__attribute__((used)) static int fixed_bar_cap(struct pci_bus *bus, unsigned int devfn)
{
	int pos;
	u32 pcie_cap = 0, cap_data;

	pos = PCIE_CAP_OFFSET;

	if (!raw_pci_ext_ops)
		return 0;

	while (pos) {
		if (raw_pci_ext_ops->read(pci_domain_nr(bus), bus->number,
					  devfn, pos, 4, &pcie_cap))
			return 0;

		if (PCI_EXT_CAP_ID(pcie_cap) == 0x0000 ||
			PCI_EXT_CAP_ID(pcie_cap) == 0xffff)
			break;

		if (PCI_EXT_CAP_ID(pcie_cap) == PCI_EXT_CAP_ID_VNDR) {
			raw_pci_ext_ops->read(pci_domain_nr(bus), bus->number,
					      devfn, pos + 4, 4, &cap_data);
			if ((cap_data & 0xffff) == PCIE_VNDR_CAP_ID_FIXED_BAR)
				return pos;
		}

		pos = PCI_EXT_CAP_NEXT(pcie_cap);
	}

	return 0;
}