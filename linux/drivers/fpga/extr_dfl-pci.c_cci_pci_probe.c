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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int EIO ; 
 int cci_enumerate_feature_devs (struct pci_dev*) ; 
 int cci_init_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 int pci_enable_pcie_error_reporting (struct pci_dev*) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 

__attribute__((used)) static
int cci_pci_probe(struct pci_dev *pcidev, const struct pci_device_id *pcidevid)
{
	int ret;

	ret = pcim_enable_device(pcidev);
	if (ret < 0) {
		dev_err(&pcidev->dev, "Failed to enable device %d.\n", ret);
		return ret;
	}

	ret = pci_enable_pcie_error_reporting(pcidev);
	if (ret && ret != -EINVAL)
		dev_info(&pcidev->dev, "PCIE AER unavailable %d.\n", ret);

	pci_set_master(pcidev);

	if (!pci_set_dma_mask(pcidev, DMA_BIT_MASK(64))) {
		ret = pci_set_consistent_dma_mask(pcidev, DMA_BIT_MASK(64));
		if (ret)
			goto disable_error_report_exit;
	} else if (!pci_set_dma_mask(pcidev, DMA_BIT_MASK(32))) {
		ret = pci_set_consistent_dma_mask(pcidev, DMA_BIT_MASK(32));
		if (ret)
			goto disable_error_report_exit;
	} else {
		ret = -EIO;
		dev_err(&pcidev->dev, "No suitable DMA support available.\n");
		goto disable_error_report_exit;
	}

	ret = cci_init_drvdata(pcidev);
	if (ret) {
		dev_err(&pcidev->dev, "Fail to init drvdata %d.\n", ret);
		goto disable_error_report_exit;
	}

	ret = cci_enumerate_feature_devs(pcidev);
	if (ret) {
		dev_err(&pcidev->dev, "enumeration failure %d.\n", ret);
		goto disable_error_report_exit;
	}

	return ret;

disable_error_report_exit:
	pci_disable_pcie_error_reporting(pcidev);
	return ret;
}