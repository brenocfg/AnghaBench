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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mmp_pdma_phy {int dma_channels; int /*<<< orphan*/  device; struct mmp_pdma_phy* phy; } ;
struct mmp_pdma_device {int dma_channels; int /*<<< orphan*/  device; struct mmp_pdma_device* phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,int,struct mmp_pdma_phy*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 struct mmp_pdma_phy* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int) ; 

__attribute__((used)) static int mmp_pdma_remove(struct platform_device *op)
{
	struct mmp_pdma_device *pdev = platform_get_drvdata(op);
	struct mmp_pdma_phy *phy;
	int i, irq = 0, irq_num = 0;


	for (i = 0; i < pdev->dma_channels; i++) {
		if (platform_get_irq(op, i) > 0)
			irq_num++;
	}

	if (irq_num != pdev->dma_channels) {
		irq = platform_get_irq(op, 0);
		devm_free_irq(&op->dev, irq, pdev);
	} else {
		for (i = 0; i < pdev->dma_channels; i++) {
			phy = &pdev->phy[i];
			irq = platform_get_irq(op, i);
			devm_free_irq(&op->dev, irq, phy);
		}
	}

	dma_async_device_unregister(&pdev->device);
	return 0;
}