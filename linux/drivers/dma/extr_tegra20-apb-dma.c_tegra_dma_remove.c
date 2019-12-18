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
struct tegra_dma_channel {int /*<<< orphan*/  tasklet; int /*<<< orphan*/  irq; } ;
struct tegra_dma {struct tegra_dma_channel* channels; TYPE_1__* chip_data; int /*<<< orphan*/  dma_dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int nr_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct tegra_dma_channel*) ; 
 struct tegra_dma* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_dma_runtime_suspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra_dma_remove(struct platform_device *pdev)
{
	struct tegra_dma *tdma = platform_get_drvdata(pdev);
	int i;
	struct tegra_dma_channel *tdc;

	dma_async_device_unregister(&tdma->dma_dev);

	for (i = 0; i < tdma->chip_data->nr_channels; ++i) {
		tdc = &tdma->channels[i];
		free_irq(tdc->irq, tdc);
		tasklet_kill(&tdc->tasklet);
	}

	pm_runtime_disable(&pdev->dev);
	if (!pm_runtime_status_suspended(&pdev->dev))
		tegra_dma_runtime_suspend(&pdev->dev);

	return 0;
}