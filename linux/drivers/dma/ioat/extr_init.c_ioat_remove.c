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
struct ioatdma_device {int /*<<< orphan*/ * dca; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_dca_provider (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioat_dma_remove (struct ioatdma_device*) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 struct ioatdma_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_dca_provider (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ioat_remove(struct pci_dev *pdev)
{
	struct ioatdma_device *device = pci_get_drvdata(pdev);

	if (!device)
		return;

	dev_err(&pdev->dev, "Removing dma and dca services\n");
	if (device->dca) {
		unregister_dca_provider(device->dca, &pdev->dev);
		free_dca_provider(device->dca);
		device->dca = NULL;
	}

	pci_disable_pcie_error_reporting(pdev);
	ioat_dma_remove(device);
}