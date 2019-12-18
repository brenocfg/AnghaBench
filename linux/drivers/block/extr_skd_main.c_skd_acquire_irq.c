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
struct skd_device {struct pci_dev* pdev; int /*<<< orphan*/  isr_name; int /*<<< orphan*/  devno; } ;
struct pci_dev {int /*<<< orphan*/  dev; scalar_t__ msi_enabled; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 char* DRV_NAME ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 unsigned int PCI_IRQ_LEGACY ; 
 unsigned int PCI_IRQ_MSI ; 
 scalar_t__ SKD_IRQ_LEGACY ; 
 scalar_t__ SKD_IRQ_MSIX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct skd_device*) ; 
 int pci_alloc_irq_vectors (struct pci_dev*,int,int,unsigned int) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int skd_acquire_msix (struct skd_device*) ; 
 int /*<<< orphan*/  skd_isr ; 
 scalar_t__ skd_isr_type ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skd_acquire_irq(struct skd_device *skdev)
{
	struct pci_dev *pdev = skdev->pdev;
	unsigned int irq_flag = PCI_IRQ_LEGACY;
	int rc;

	if (skd_isr_type == SKD_IRQ_MSIX) {
		rc = skd_acquire_msix(skdev);
		if (!rc)
			return 0;

		dev_err(&skdev->pdev->dev,
			"failed to enable MSI-X, re-trying with MSI %d\n", rc);
	}

	snprintf(skdev->isr_name, sizeof(skdev->isr_name), "%s%d", DRV_NAME,
			skdev->devno);

	if (skd_isr_type != SKD_IRQ_LEGACY)
		irq_flag |= PCI_IRQ_MSI;
	rc = pci_alloc_irq_vectors(pdev, 1, 1, irq_flag);
	if (rc < 0) {
		dev_err(&skdev->pdev->dev,
			"failed to allocate the MSI interrupt %d\n", rc);
		return rc;
	}

	rc = devm_request_irq(&pdev->dev, pdev->irq, skd_isr,
			pdev->msi_enabled ? 0 : IRQF_SHARED,
			skdev->isr_name, skdev);
	if (rc) {
		pci_free_irq_vectors(pdev);
		dev_err(&skdev->pdev->dev, "failed to allocate interrupt %d\n",
			rc);
		return rc;
	}

	return 0;
}