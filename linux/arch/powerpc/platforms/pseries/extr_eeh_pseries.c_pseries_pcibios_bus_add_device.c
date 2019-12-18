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
struct pci_dn {size_t vf_index; int busno; int devfn; int /*<<< orphan*/ * pe_num_map; int /*<<< orphan*/  pe_number; scalar_t__ last_allow_rc; int /*<<< orphan*/  class_code; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  device_id; } ;
struct pci_dev {scalar_t__ is_virtfn; struct pci_dev* physfn; int /*<<< orphan*/  class; int /*<<< orphan*/  vendor; int /*<<< orphan*/  device; int /*<<< orphan*/  dev; } ;
struct eeh_dev {int pe_config_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEH_FORCE_DISABLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  eeh_add_device_early (struct pci_dn*) ; 
 int /*<<< orphan*/  eeh_add_device_late (struct pci_dev*) ; 
 int /*<<< orphan*/  eeh_add_to_parent_pe (struct eeh_dev*) ; 
 scalar_t__ eeh_has_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeh_rmv_from_parent_pe (struct eeh_dev*) ; 
 int /*<<< orphan*/  eeh_sysfs_add_device (struct pci_dev*) ; 
 struct pci_dn* pci_get_pdn (struct pci_dev*) ; 
 struct eeh_dev* pdn_to_eeh_dev (struct pci_dn*) ; 

void pseries_pcibios_bus_add_device(struct pci_dev *pdev)
{
	struct pci_dn *pdn = pci_get_pdn(pdev);

	if (eeh_has_flag(EEH_FORCE_DISABLED))
		return;

	dev_dbg(&pdev->dev, "EEH: Setting up device\n");
#ifdef CONFIG_PCI_IOV
	if (pdev->is_virtfn) {
		struct pci_dn *physfn_pdn;

		pdn->device_id  =  pdev->device;
		pdn->vendor_id  =  pdev->vendor;
		pdn->class_code =  pdev->class;
		/*
		 * Last allow unfreeze return code used for retrieval
		 * by user space in eeh-sysfs to show the last command
		 * completion from platform.
		 */
		pdn->last_allow_rc =  0;
		physfn_pdn      =  pci_get_pdn(pdev->physfn);
		pdn->pe_number  =  physfn_pdn->pe_num_map[pdn->vf_index];
	}
#endif
	eeh_add_device_early(pdn);
	eeh_add_device_late(pdev);
#ifdef CONFIG_PCI_IOV
	if (pdev->is_virtfn) {
		struct eeh_dev *edev = pdn_to_eeh_dev(pdn);

		edev->pe_config_addr =  (pdn->busno << 16) | (pdn->devfn << 8);
		eeh_rmv_from_parent_pe(edev); /* Remove as it is adding to bus pe */
		eeh_add_to_parent_pe(edev);   /* Add as VF PE type */
	}
#endif
	eeh_sysfs_add_device(pdev);
}