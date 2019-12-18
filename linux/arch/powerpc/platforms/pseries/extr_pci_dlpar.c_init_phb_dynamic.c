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
struct pci_controller {int /*<<< orphan*/  bus; int /*<<< orphan*/  controller_ops; } ;
struct device_node {scalar_t__ child; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DN (struct device_node*) ; 
 int /*<<< orphan*/  eeh_add_device_tree_early (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeh_dev_phb_init_dynamic (struct pci_controller*) ; 
 int /*<<< orphan*/  pci_devs_phb_init_dynamic (struct pci_controller*) ; 
 int /*<<< orphan*/  pci_process_bridge_OF_ranges (struct pci_controller*,struct device_node*,int /*<<< orphan*/ ) ; 
 struct pci_controller* pcibios_alloc_controller (struct device_node*) ; 
 int /*<<< orphan*/  pcibios_finish_adding_to_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcibios_scan_phb (struct pci_controller*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct device_node*) ; 
 int /*<<< orphan*/  pseries_pci_controller_ops ; 
 int /*<<< orphan*/  rtas_setup_phb (struct pci_controller*) ; 

struct pci_controller *init_phb_dynamic(struct device_node *dn)
{
	struct pci_controller *phb;

	pr_debug("PCI: Initializing new hotplug PHB %pOF\n", dn);

	phb = pcibios_alloc_controller(dn);
	if (!phb)
		return NULL;
	rtas_setup_phb(phb);
	pci_process_bridge_OF_ranges(phb, dn, 0);
	phb->controller_ops = pseries_pci_controller_ops;

	pci_devs_phb_init_dynamic(phb);

	/* Create EEH devices for the PHB */
	eeh_dev_phb_init_dynamic(phb);

	if (dn->child)
		eeh_add_device_tree_early(PCI_DN(dn));

	pcibios_scan_phb(phb);
	pcibios_finish_adding_to_bus(phb->bus);

	return phb;
}