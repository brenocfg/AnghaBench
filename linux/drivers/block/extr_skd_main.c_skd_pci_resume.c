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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ u32 ;
struct skd_device {int pcie_error_reporting_is_enabled; scalar_t__* mem_map; int /*<<< orphan*/  waitq; scalar_t__* mem_size; scalar_t__* mem_phys; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENODEV ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int SKD_MAX_BARS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 scalar_t__ ioremap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int pci_enable_pcie_error_reporting (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_wake (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct skd_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_len (struct pci_dev*,int) ; 
 scalar_t__ pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int skd_acquire_irq (struct skd_device*) ; 
 int /*<<< orphan*/  skd_release_irq (struct skd_device*) ; 
 int /*<<< orphan*/  skd_start_device (struct skd_device*) ; 
 int skd_start_timer (struct skd_device*) ; 
 int /*<<< orphan*/  skd_stop_device (struct skd_device*) ; 

__attribute__((used)) static int skd_pci_resume(struct pci_dev *pdev)
{
	int i;
	int rc = 0;
	struct skd_device *skdev;

	skdev = pci_get_drvdata(pdev);
	if (!skdev) {
		dev_err(&pdev->dev, "no device data for PCI\n");
		return -1;
	}

	pci_set_power_state(pdev, PCI_D0);
	pci_enable_wake(pdev, PCI_D0, 0);
	pci_restore_state(pdev);

	rc = pci_enable_device(pdev);
	if (rc)
		return rc;
	rc = pci_request_regions(pdev, DRV_NAME);
	if (rc)
		goto err_out;
	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	if (rc)
		rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	if (rc) {
		dev_err(&pdev->dev, "DMA mask error %d\n", rc);
		goto err_out_regions;
	}

	pci_set_master(pdev);
	rc = pci_enable_pcie_error_reporting(pdev);
	if (rc) {
		dev_err(&pdev->dev,
			"bad enable of PCIe error reporting rc=%d\n", rc);
		skdev->pcie_error_reporting_is_enabled = 0;
	} else
		skdev->pcie_error_reporting_is_enabled = 1;

	for (i = 0; i < SKD_MAX_BARS; i++) {

		skdev->mem_phys[i] = pci_resource_start(pdev, i);
		skdev->mem_size[i] = (u32)pci_resource_len(pdev, i);
		skdev->mem_map[i] = ioremap(skdev->mem_phys[i],
					    skdev->mem_size[i]);
		if (!skdev->mem_map[i]) {
			dev_err(&pdev->dev, "Unable to map adapter memory!\n");
			rc = -ENODEV;
			goto err_out_iounmap;
		}
		dev_dbg(&pdev->dev, "mem_map=%p, phyd=%016llx, size=%d\n",
			skdev->mem_map[i], (uint64_t)skdev->mem_phys[i],
			skdev->mem_size[i]);
	}
	rc = skd_acquire_irq(skdev);
	if (rc) {
		dev_err(&pdev->dev, "interrupt resource error %d\n", rc);
		goto err_out_iounmap;
	}

	rc = skd_start_timer(skdev);
	if (rc)
		goto err_out_timer;

	init_waitqueue_head(&skdev->waitq);

	skd_start_device(skdev);

	return rc;

err_out_timer:
	skd_stop_device(skdev);
	skd_release_irq(skdev);

err_out_iounmap:
	for (i = 0; i < SKD_MAX_BARS; i++)
		if (skdev->mem_map[i])
			iounmap(skdev->mem_map[i]);

	if (skdev->pcie_error_reporting_is_enabled)
		pci_disable_pcie_error_reporting(pdev);

err_out_regions:
	pci_release_regions(pdev);

err_out:
	pci_disable_device(pdev);
	return rc;
}