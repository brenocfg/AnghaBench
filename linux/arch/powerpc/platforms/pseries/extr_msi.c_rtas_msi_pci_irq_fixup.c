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
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ check_req_msi (struct pci_dev*,int) ; 
 scalar_t__ check_req_msix (struct pci_dev*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  rtas_disable_msi (struct pci_dev*) ; 

__attribute__((used)) static void rtas_msi_pci_irq_fixup(struct pci_dev *pdev)
{
	/* No LSI -> leave MSIs (if any) configured */
	if (!pdev->irq) {
		dev_dbg(&pdev->dev, "rtas_msi: no LSI, nothing to do.\n");
		return;
	}

	/* No MSI -> MSIs can't have been assigned by fw, leave LSI */
	if (check_req_msi(pdev, 1) && check_req_msix(pdev, 1)) {
		dev_dbg(&pdev->dev, "rtas_msi: no req#msi/x, nothing to do.\n");
		return;
	}

	dev_dbg(&pdev->dev, "rtas_msi: disabling existing MSI.\n");
	rtas_disable_msi(pdev);
}