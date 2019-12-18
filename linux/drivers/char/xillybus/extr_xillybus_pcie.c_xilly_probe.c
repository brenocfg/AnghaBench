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
struct xilly_endpoint {int dma_using_dac; int /*<<< orphan*/  dev; int /*<<< orphan*/  registers; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  PCIE_LINK_STATE_L0S ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xilly_endpoint*) ; 
 int /*<<< orphan*/  pci_disable_link_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_enable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_hw ; 
 int pci_resource_flags (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct xilly_endpoint*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int pcim_iomap_regions (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pcim_iomap_table (struct pci_dev*) ; 
 int xillybus_endpoint_discovery (struct xilly_endpoint*) ; 
 struct xilly_endpoint* xillybus_init_endpoint (struct pci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xillybus_isr ; 
 int /*<<< orphan*/  xillyname ; 

__attribute__((used)) static int xilly_probe(struct pci_dev *pdev,
		       const struct pci_device_id *ent)
{
	struct xilly_endpoint *endpoint;
	int rc;

	endpoint = xillybus_init_endpoint(pdev, &pdev->dev, &pci_hw);

	if (!endpoint)
		return -ENOMEM;

	pci_set_drvdata(pdev, endpoint);

	rc = pcim_enable_device(pdev);
	if (rc) {
		dev_err(endpoint->dev,
			"pcim_enable_device() failed. Aborting.\n");
		return rc;
	}

	/* L0s has caused packet drops. No power saving, thank you. */

	pci_disable_link_state(pdev, PCIE_LINK_STATE_L0S);

	if (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) {
		dev_err(endpoint->dev,
			"Incorrect BAR configuration. Aborting.\n");
		return -ENODEV;
	}

	rc = pcim_iomap_regions(pdev, 0x01, xillyname);
	if (rc) {
		dev_err(endpoint->dev,
			"pcim_iomap_regions() failed. Aborting.\n");
		return rc;
	}

	endpoint->registers = pcim_iomap_table(pdev)[0];

	pci_set_master(pdev);

	/* Set up a single MSI interrupt */
	if (pci_enable_msi(pdev)) {
		dev_err(endpoint->dev,
			"Failed to enable MSI interrupts. Aborting.\n");
		return -ENODEV;
	}
	rc = devm_request_irq(&pdev->dev, pdev->irq, xillybus_isr, 0,
			      xillyname, endpoint);
	if (rc) {
		dev_err(endpoint->dev,
			"Failed to register MSI handler. Aborting.\n");
		return -ENODEV;
	}

	/*
	 * Some (old and buggy?) hardware drops 64-bit addressed PCIe packets,
	 * even when the PCIe driver claims that a 64-bit mask is OK. On the
	 * other hand, on some architectures, 64-bit addressing is mandatory.
	 * So go for the 64-bit mask only when failing is the other option.
	 */

	if (!pci_set_dma_mask(pdev, DMA_BIT_MASK(32))) {
		endpoint->dma_using_dac = 0;
	} else if (!pci_set_dma_mask(pdev, DMA_BIT_MASK(64))) {
		endpoint->dma_using_dac = 1;
	} else {
		dev_err(endpoint->dev, "Failed to set DMA mask. Aborting.\n");
		return -ENODEV;
	}

	return xillybus_endpoint_discovery(endpoint);
}