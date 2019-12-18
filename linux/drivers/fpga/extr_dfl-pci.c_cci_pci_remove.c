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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cci_pci_sriov_configure (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cci_remove_feature_devs (struct pci_dev*) ; 
 scalar_t__ dev_is_pf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 

__attribute__((used)) static void cci_pci_remove(struct pci_dev *pcidev)
{
	if (dev_is_pf(&pcidev->dev))
		cci_pci_sriov_configure(pcidev, 0);

	cci_remove_feature_devs(pcidev);
	pci_disable_pcie_error_reporting(pcidev);
}