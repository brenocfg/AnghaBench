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
typedef  int uint32_t ;
struct pci_dn {int dummy; } ;
struct eeh_dev {int mode; int pcie_cap; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read_config ) (struct pci_dn*,scalar_t__,int,int*) ;int /*<<< orphan*/  (* write_config ) (struct pci_dn*,scalar_t__,int,int) ;} ;

/* Variables and functions */
 int EEH_DEV_DS_PORT ; 
 int EEH_DEV_ROOT_PORT ; 
 scalar_t__ PCI_EXP_LNKCAP ; 
 int PCI_EXP_LNKCAP_DLLLARC ; 
 scalar_t__ PCI_EXP_LNKCTL ; 
 int PCI_EXP_LNKCTL_LD ; 
 scalar_t__ PCI_EXP_LNKSTA ; 
 int PCI_EXP_LNKSTA_CLS_2_5GB ; 
 int PCI_EXP_LNKSTA_DLLLA ; 
 scalar_t__ PCI_EXP_SLTCAP ; 
 int PCI_EXP_SLTCAP_PCP ; 
 scalar_t__ PCI_EXP_SLTCTL ; 
 int PCI_EXP_SLTCTL_PCC ; 
 int PCI_EXP_SLTCTL_PIC ; 
 scalar_t__ PCI_EXP_SLTSTA ; 
 int PCI_EXP_SLTSTA_PDS ; 
 struct pci_dn* eeh_dev_to_pdn (struct eeh_dev*) ; 
 int /*<<< orphan*/  eeh_edev_dbg (struct eeh_dev*,char*,...) ; 
 TYPE_1__* eeh_ops ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct pci_dn*,scalar_t__,int,int*) ; 
 int /*<<< orphan*/  stub2 (struct pci_dn*,scalar_t__,int,int*) ; 
 int /*<<< orphan*/  stub3 (struct pci_dn*,scalar_t__,int,int*) ; 
 int /*<<< orphan*/  stub4 (struct pci_dn*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  stub5 (struct pci_dn*,scalar_t__,int,int*) ; 
 int /*<<< orphan*/  stub6 (struct pci_dn*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  stub7 (struct pci_dn*,scalar_t__,int,int*) ; 
 int /*<<< orphan*/  stub8 (struct pci_dn*,scalar_t__,int,int*) ; 

__attribute__((used)) static void eeh_bridge_check_link(struct eeh_dev *edev)
{
	struct pci_dn *pdn = eeh_dev_to_pdn(edev);
	int cap;
	uint32_t val;
	int timeout = 0;

	/*
	 * We only check root port and downstream ports of
	 * PCIe switches
	 */
	if (!(edev->mode & (EEH_DEV_ROOT_PORT | EEH_DEV_DS_PORT)))
		return;

	eeh_edev_dbg(edev, "Checking PCIe link...\n");

	/* Check slot status */
	cap = edev->pcie_cap;
	eeh_ops->read_config(pdn, cap + PCI_EXP_SLTSTA, 2, &val);
	if (!(val & PCI_EXP_SLTSTA_PDS)) {
		eeh_edev_dbg(edev, "No card in the slot (0x%04x) !\n", val);
		return;
	}

	/* Check power status if we have the capability */
	eeh_ops->read_config(pdn, cap + PCI_EXP_SLTCAP, 2, &val);
	if (val & PCI_EXP_SLTCAP_PCP) {
		eeh_ops->read_config(pdn, cap + PCI_EXP_SLTCTL, 2, &val);
		if (val & PCI_EXP_SLTCTL_PCC) {
			eeh_edev_dbg(edev, "In power-off state, power it on ...\n");
			val &= ~(PCI_EXP_SLTCTL_PCC | PCI_EXP_SLTCTL_PIC);
			val |= (0x0100 & PCI_EXP_SLTCTL_PIC);
			eeh_ops->write_config(pdn, cap + PCI_EXP_SLTCTL, 2, val);
			msleep(2 * 1000);
		}
	}

	/* Enable link */
	eeh_ops->read_config(pdn, cap + PCI_EXP_LNKCTL, 2, &val);
	val &= ~PCI_EXP_LNKCTL_LD;
	eeh_ops->write_config(pdn, cap + PCI_EXP_LNKCTL, 2, val);

	/* Check link */
	eeh_ops->read_config(pdn, cap + PCI_EXP_LNKCAP, 4, &val);
	if (!(val & PCI_EXP_LNKCAP_DLLLARC)) {
		eeh_edev_dbg(edev, "No link reporting capability (0x%08x) \n", val);
		msleep(1000);
		return;
	}

	/* Wait the link is up until timeout (5s) */
	timeout = 0;
	while (timeout < 5000) {
		msleep(20);
		timeout += 20;

		eeh_ops->read_config(pdn, cap + PCI_EXP_LNKSTA, 2, &val);
		if (val & PCI_EXP_LNKSTA_DLLLA)
			break;
	}

	if (val & PCI_EXP_LNKSTA_DLLLA)
		eeh_edev_dbg(edev, "Link up (%s)\n",
			 (val & PCI_EXP_LNKSTA_CLS_2_5GB) ? "2.5GB" : "5GB");
	else
		eeh_edev_dbg(edev, "Link not ready (0x%04x)\n", val);
}