#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int m64_segsize; int m32_segsize; int io_segsize; } ;
struct pnv_phb {TYPE_2__ ioda; } ;
struct pci_dev {TYPE_1__* bus; } ;
struct pci_controller {struct pnv_phb* private_data; } ;
struct pci_bus {struct pci_dev* self; } ;
typedef  int resource_size_t ;
struct TYPE_3__ {struct pci_dev* self; } ;

/* Variables and functions */
 unsigned long IORESOURCE_MEM ; 
 scalar_t__ PCI_EXP_TYPE_PCI_BRIDGE ; 
 struct pci_controller* pci_bus_to_host (struct pci_bus*) ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 
 scalar_t__ pnv_pci_is_m64_flags (unsigned long) ; 

__attribute__((used)) static resource_size_t pnv_pci_window_alignment(struct pci_bus *bus,
						unsigned long type)
{
	struct pci_dev *bridge;
	struct pci_controller *hose = pci_bus_to_host(bus);
	struct pnv_phb *phb = hose->private_data;
	int num_pci_bridges = 0;

	bridge = bus->self;
	while (bridge) {
		if (pci_pcie_type(bridge) == PCI_EXP_TYPE_PCI_BRIDGE) {
			num_pci_bridges++;
			if (num_pci_bridges >= 2)
				return 1;
		}

		bridge = bridge->bus->self;
	}

	/*
	 * We fall back to M32 if M64 isn't supported. We enforce the M64
	 * alignment for any 64-bit resource, PCIe doesn't care and
	 * bridges only do 64-bit prefetchable anyway.
	 */
	if (phb->ioda.m64_segsize && pnv_pci_is_m64_flags(type))
		return phb->ioda.m64_segsize;
	if (type & IORESOURCE_MEM)
		return phb->ioda.m32_segsize;

	return phb->ioda.io_segsize;
}