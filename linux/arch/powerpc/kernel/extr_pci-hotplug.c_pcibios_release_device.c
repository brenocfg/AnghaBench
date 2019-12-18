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
struct pci_dn {int flags; } ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* release_device ) (struct pci_dev*) ;} ;
struct pci_controller {TYPE_1__ controller_ops; } ;

/* Variables and functions */
 int PCI_DN_FLAG_DEAD ; 
 int /*<<< orphan*/  eeh_remove_device (struct pci_dev*) ; 
 int /*<<< orphan*/  kfree (struct pci_dn*) ; 
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dbg (struct pci_dev*,char*) ; 
 struct pci_dn* pci_get_pdn (struct pci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct pci_dev*) ; 

void pcibios_release_device(struct pci_dev *dev)
{
	struct pci_controller *phb = pci_bus_to_host(dev->bus);
	struct pci_dn *pdn = pci_get_pdn(dev);

	eeh_remove_device(dev);

	if (phb->controller_ops.release_device)
		phb->controller_ops.release_device(dev);

	/* free()ing the pci_dn has been deferred to us, do it now */
	if (pdn && (pdn->flags & PCI_DN_FLAG_DEAD)) {
		pci_dbg(dev, "freeing dead pdn\n");
		kfree(pdn);
	}
}