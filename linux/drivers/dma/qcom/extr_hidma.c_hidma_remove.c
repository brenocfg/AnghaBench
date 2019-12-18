#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct hidma_dev {TYPE_1__* lldev; int /*<<< orphan*/  task; int /*<<< orphan*/  irq; TYPE_2__ ddev; } ;
struct TYPE_4__ {int /*<<< orphan*/  msi_support; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  hidma_debug_uninit (struct hidma_dev*) ; 
 int /*<<< orphan*/  hidma_free (struct hidma_dev*) ; 
 int /*<<< orphan*/  hidma_free_msis (struct hidma_dev*) ; 
 int /*<<< orphan*/  hidma_ll_uninit (TYPE_1__*) ; 
 int /*<<< orphan*/  hidma_sysfs_uninit (struct hidma_dev*) ; 
 struct hidma_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync_suspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hidma_remove(struct platform_device *pdev)
{
	struct hidma_dev *dmadev = platform_get_drvdata(pdev);

	pm_runtime_get_sync(dmadev->ddev.dev);
	dma_async_device_unregister(&dmadev->ddev);
	if (!dmadev->lldev->msi_support)
		devm_free_irq(dmadev->ddev.dev, dmadev->irq, dmadev->lldev);
	else
		hidma_free_msis(dmadev);

	tasklet_kill(&dmadev->task);
	hidma_sysfs_uninit(dmadev);
	hidma_debug_uninit(dmadev);
	hidma_ll_uninit(dmadev->lldev);
	hidma_free(dmadev);

	dev_info(&pdev->dev, "HI-DMA engine removed\n");
	pm_runtime_put_sync_suspend(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	return 0;
}