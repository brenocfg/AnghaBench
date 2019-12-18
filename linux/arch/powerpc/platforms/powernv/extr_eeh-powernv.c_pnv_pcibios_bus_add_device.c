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
struct pci_dn {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEH_FORCE_DISABLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  eeh_add_device_early (struct pci_dn*) ; 
 int /*<<< orphan*/  eeh_add_device_late (struct pci_dev*) ; 
 scalar_t__ eeh_has_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeh_sysfs_add_device (struct pci_dev*) ; 
 struct pci_dn* pci_get_pdn (struct pci_dev*) ; 

void pnv_pcibios_bus_add_device(struct pci_dev *pdev)
{
	struct pci_dn *pdn = pci_get_pdn(pdev);

	if (!pdn || eeh_has_flag(EEH_FORCE_DISABLED))
		return;

	dev_dbg(&pdev->dev, "EEH: Setting up device\n");
	eeh_add_device_early(pdn);
	eeh_add_device_late(pdev);
	eeh_sysfs_add_device(pdev);
}