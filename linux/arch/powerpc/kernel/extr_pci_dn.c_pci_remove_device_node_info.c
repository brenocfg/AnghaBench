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
struct pci_dn {int /*<<< orphan*/  flags; int /*<<< orphan*/  devfn; int /*<<< orphan*/  busno; TYPE_1__* phb; int /*<<< orphan*/  list; int /*<<< orphan*/  child_list; } ;
struct pci_dev {int dummy; } ;
struct eeh_dev {int /*<<< orphan*/ * pdn; } ;
struct device_node {int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {int /*<<< orphan*/  global_number; } ;

/* Variables and functions */
 struct pci_dn* PCI_DN (struct device_node*) ; 
 int /*<<< orphan*/  PCI_DN_FLAG_DEAD ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct pci_dn*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct device_node* of_get_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  pci_dbg (struct pci_dev*,char*,struct device_node*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_domain_bus_and_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct eeh_dev* pdn_to_eeh_dev (struct pci_dn*) ; 

void pci_remove_device_node_info(struct device_node *dn)
{
	struct pci_dn *pdn = dn ? PCI_DN(dn) : NULL;
	struct device_node *parent;
	struct pci_dev *pdev;
#ifdef CONFIG_EEH
	struct eeh_dev *edev = pdn_to_eeh_dev(pdn);

	if (edev)
		edev->pdn = NULL;
#endif

	if (!pdn)
		return;

	WARN_ON(!list_empty(&pdn->child_list));
	list_del(&pdn->list);

	/* Drop the parent pci_dn's ref to our backing dt node */
	parent = of_get_parent(dn);
	if (parent)
		of_node_put(parent);

	/*
	 * At this point we *might* still have a pci_dev that was
	 * instantiated from this pci_dn. So defer free()ing it until
	 * the pci_dev's release function is called.
	 */
	pdev = pci_get_domain_bus_and_slot(pdn->phb->global_number,
			pdn->busno, pdn->devfn);
	if (pdev) {
		/* NB: pdev has a ref to dn */
		pci_dbg(pdev, "marked pdn (from %pOF) as dead\n", dn);
		pdn->flags |= PCI_DN_FLAG_DEAD;
	} else {
		dn->data = NULL;
		kfree(pdn);
	}

	pci_dev_put(pdev);
}