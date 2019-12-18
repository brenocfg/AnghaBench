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
struct pci_dn {int dummy; } ;
struct eeh_dev {scalar_t__ pcie_cap; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_config ) (struct pci_dn*,scalar_t__,int,int) ;int /*<<< orphan*/  (* read_config ) (struct pci_dn*,scalar_t__,int,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EEH_PE_RST_HOLD_TIME ; 
 int /*<<< orphan*/  EEH_PE_RST_SETTLE_TIME ; 
#define  EEH_RESET_DEACTIVATE 130 
#define  EEH_RESET_FUNDAMENTAL 129 
#define  EEH_RESET_HOT 128 
 int ENOTTY ; 
 scalar_t__ PCI_EXP_DEVCAP ; 
 int PCI_EXP_DEVCAP_FLR ; 
 scalar_t__ PCI_EXP_DEVCTL ; 
 int PCI_EXP_DEVCTL_BCR_FLR ; 
 scalar_t__ PCI_EXP_DEVSTA ; 
 int /*<<< orphan*/  PCI_EXP_DEVSTA_TRPND ; 
 scalar_t__ WARN_ON (int) ; 
 TYPE_1__* eeh_ops ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 struct eeh_dev* pdn_to_eeh_dev (struct pci_dn*) ; 
 int /*<<< orphan*/  pnv_eeh_wait_for_pending (struct pci_dn*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pci_dn*,scalar_t__,int,int*) ; 
 int /*<<< orphan*/  stub2 (struct pci_dn*,scalar_t__,int,int*) ; 
 int /*<<< orphan*/  stub3 (struct pci_dn*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  stub4 (struct pci_dn*,scalar_t__,int,int*) ; 
 int /*<<< orphan*/  stub5 (struct pci_dn*,scalar_t__,int,int) ; 

__attribute__((used)) static int pnv_eeh_do_flr(struct pci_dn *pdn, int option)
{
	struct eeh_dev *edev = pdn_to_eeh_dev(pdn);
	u32 reg = 0;

	if (WARN_ON(!edev->pcie_cap))
		return -ENOTTY;

	eeh_ops->read_config(pdn, edev->pcie_cap + PCI_EXP_DEVCAP, 4, &reg);
	if (!(reg & PCI_EXP_DEVCAP_FLR))
		return -ENOTTY;

	switch (option) {
	case EEH_RESET_HOT:
	case EEH_RESET_FUNDAMENTAL:
		pnv_eeh_wait_for_pending(pdn, "",
					 edev->pcie_cap + PCI_EXP_DEVSTA,
					 PCI_EXP_DEVSTA_TRPND);
		eeh_ops->read_config(pdn, edev->pcie_cap + PCI_EXP_DEVCTL,
				     4, &reg);
		reg |= PCI_EXP_DEVCTL_BCR_FLR;
		eeh_ops->write_config(pdn, edev->pcie_cap + PCI_EXP_DEVCTL,
				      4, reg);
		msleep(EEH_PE_RST_HOLD_TIME);
		break;
	case EEH_RESET_DEACTIVATE:
		eeh_ops->read_config(pdn, edev->pcie_cap + PCI_EXP_DEVCTL,
				     4, &reg);
		reg &= ~PCI_EXP_DEVCTL_BCR_FLR;
		eeh_ops->write_config(pdn, edev->pcie_cap + PCI_EXP_DEVCTL,
				      4, reg);
		msleep(EEH_PE_RST_SETTLE_TIME);
		break;
	}

	return 0;
}