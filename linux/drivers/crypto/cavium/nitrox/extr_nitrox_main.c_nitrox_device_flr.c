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
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_flr (struct pci_dev*) ; 
 scalar_t__ pcie_has_flr (struct pci_dev*) ; 

__attribute__((used)) static int nitrox_device_flr(struct pci_dev *pdev)
{
	int pos = 0;

	pos = pci_save_state(pdev);
	if (pos) {
		dev_err(&pdev->dev, "Failed to save pci state\n");
		return -ENOMEM;
	}

	/* check flr support */
	if (pcie_has_flr(pdev))
		pcie_flr(pdev);

	pci_restore_state(pdev);

	return 0;
}