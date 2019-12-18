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
struct skd_msix_entry {int /*<<< orphan*/  isr_name; } ;
struct skd_device {char* devno; struct skd_msix_entry* msix_entries; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  handler; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 char* DRV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCI_IRQ_MSIX ; 
 int SKD_MAX_MSIX_COUNT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct skd_device*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct skd_device*) ; 
 struct skd_msix_entry* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct skd_msix_entry*) ; 
 TYPE_1__* msix_entries ; 
 int pci_alloc_irq_vectors (struct pci_dev*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skd_acquire_msix(struct skd_device *skdev)
{
	int i, rc;
	struct pci_dev *pdev = skdev->pdev;

	rc = pci_alloc_irq_vectors(pdev, SKD_MAX_MSIX_COUNT, SKD_MAX_MSIX_COUNT,
			PCI_IRQ_MSIX);
	if (rc < 0) {
		dev_err(&skdev->pdev->dev, "failed to enable MSI-X %d\n", rc);
		goto out;
	}

	skdev->msix_entries = kcalloc(SKD_MAX_MSIX_COUNT,
			sizeof(struct skd_msix_entry), GFP_KERNEL);
	if (!skdev->msix_entries) {
		rc = -ENOMEM;
		dev_err(&skdev->pdev->dev, "msix table allocation error\n");
		goto out;
	}

	/* Enable MSI-X vectors for the base queue */
	for (i = 0; i < SKD_MAX_MSIX_COUNT; i++) {
		struct skd_msix_entry *qentry = &skdev->msix_entries[i];

		snprintf(qentry->isr_name, sizeof(qentry->isr_name),
			 "%s%d-msix %s", DRV_NAME, skdev->devno,
			 msix_entries[i].name);

		rc = devm_request_irq(&skdev->pdev->dev,
				pci_irq_vector(skdev->pdev, i),
				msix_entries[i].handler, 0,
				qentry->isr_name, skdev);
		if (rc) {
			dev_err(&skdev->pdev->dev,
				"Unable to register(%d) MSI-X handler %d: %s\n",
				rc, i, qentry->isr_name);
			goto msix_out;
		}
	}

	dev_dbg(&skdev->pdev->dev, "%d msix irq(s) enabled\n",
		SKD_MAX_MSIX_COUNT);
	return 0;

msix_out:
	while (--i >= 0)
		devm_free_irq(&pdev->dev, pci_irq_vector(pdev, i), skdev);
out:
	kfree(skdev->msix_entries);
	skdev->msix_entries = NULL;
	return rc;
}