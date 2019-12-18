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
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset_secondary_bus ) (struct pci_dev*) ;} ;
struct pci_controller {TYPE_1__ controller_ops; } ;

/* Variables and functions */
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_reset_secondary_bus (struct pci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct pci_dev*) ; 

void pcibios_reset_secondary_bus(struct pci_dev *dev)
{
	struct pci_controller *phb = pci_bus_to_host(dev->bus);

	if (phb->controller_ops.reset_secondary_bus) {
		phb->controller_ops.reset_secondary_bus(dev);
		return;
	}

	pci_reset_secondary_bus(dev);
}