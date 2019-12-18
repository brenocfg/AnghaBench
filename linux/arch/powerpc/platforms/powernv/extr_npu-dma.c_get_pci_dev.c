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
struct pci_dn {int /*<<< orphan*/  devfn; int /*<<< orphan*/  busno; TYPE_1__* phb; } ;
struct pci_dev {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 struct pci_dn* PCI_DN (struct device_node*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_domain_nr (int /*<<< orphan*/ ) ; 
 struct pci_dev* pci_get_domain_bus_and_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pci_dev *get_pci_dev(struct device_node *dn)
{
	struct pci_dn *pdn = PCI_DN(dn);
	struct pci_dev *pdev;

	pdev = pci_get_domain_bus_and_slot(pci_domain_nr(pdn->phb->bus),
					   pdn->busno, pdn->devfn);

	/*
	 * pci_get_domain_bus_and_slot() increased the reference count of
	 * the PCI device, but callers don't need that actually as the PE
	 * already holds a reference to the device. Since callers aren't
	 * aware of the reference count change, call pci_dev_put() now to
	 * avoid leaks.
	 */
	if (pdev)
		pci_dev_put(pdev);

	return pdev;
}