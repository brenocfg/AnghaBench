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
struct xgene_dma {int err_irq; TYPE_1__* chan; void* csr_efuse; void* csr_ring_cmd; void* csr_ring; void* csr_dma; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int rx_irq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int XGENE_DMA_MAX_CHANNEL ; 
 scalar_t__ XGENE_DMA_RING_CMD_SM_OFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int xgene_dma_get_resources(struct platform_device *pdev,
				   struct xgene_dma *pdma)
{
	struct resource *res;
	int irq, i;

	/* Get DMA csr region */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "Failed to get csr region\n");
		return -ENXIO;
	}

	pdma->csr_dma = devm_ioremap(&pdev->dev, res->start,
				     resource_size(res));
	if (!pdma->csr_dma) {
		dev_err(&pdev->dev, "Failed to ioremap csr region");
		return -ENOMEM;
	}

	/* Get DMA ring csr region */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!res) {
		dev_err(&pdev->dev, "Failed to get ring csr region\n");
		return -ENXIO;
	}

	pdma->csr_ring =  devm_ioremap(&pdev->dev, res->start,
				       resource_size(res));
	if (!pdma->csr_ring) {
		dev_err(&pdev->dev, "Failed to ioremap ring csr region");
		return -ENOMEM;
	}

	/* Get DMA ring cmd csr region */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 2);
	if (!res) {
		dev_err(&pdev->dev, "Failed to get ring cmd csr region\n");
		return -ENXIO;
	}

	pdma->csr_ring_cmd = devm_ioremap(&pdev->dev, res->start,
					  resource_size(res));
	if (!pdma->csr_ring_cmd) {
		dev_err(&pdev->dev, "Failed to ioremap ring cmd csr region");
		return -ENOMEM;
	}

	pdma->csr_ring_cmd += XGENE_DMA_RING_CMD_SM_OFFSET;

	/* Get efuse csr region */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 3);
	if (!res) {
		dev_err(&pdev->dev, "Failed to get efuse csr region\n");
		return -ENXIO;
	}

	pdma->csr_efuse = devm_ioremap(&pdev->dev, res->start,
				       resource_size(res));
	if (!pdma->csr_efuse) {
		dev_err(&pdev->dev, "Failed to ioremap efuse csr region");
		return -ENOMEM;
	}

	/* Get DMA error interrupt */
	irq = platform_get_irq(pdev, 0);
	if (irq <= 0)
		return -ENXIO;

	pdma->err_irq = irq;

	/* Get DMA Rx ring descriptor interrupts for all DMA channels */
	for (i = 1; i <= XGENE_DMA_MAX_CHANNEL; i++) {
		irq = platform_get_irq(pdev, i);
		if (irq <= 0)
			return -ENXIO;

		pdma->chan[i - 1].rx_irq = irq;
	}

	return 0;
}