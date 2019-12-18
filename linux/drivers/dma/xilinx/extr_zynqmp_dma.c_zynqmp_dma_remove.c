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
struct zynqmp_dma_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  chan; int /*<<< orphan*/  common; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_dma_controller_free (int /*<<< orphan*/ ) ; 
 struct zynqmp_dma_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynqmp_dma_chan_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynqmp_dma_runtime_suspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zynqmp_dma_remove(struct platform_device *pdev)
{
	struct zynqmp_dma_device *zdev = platform_get_drvdata(pdev);

	of_dma_controller_free(pdev->dev.of_node);
	dma_async_device_unregister(&zdev->common);

	zynqmp_dma_chan_remove(zdev->chan);
	pm_runtime_disable(zdev->dev);
	if (!pm_runtime_enabled(zdev->dev))
		zynqmp_dma_runtime_suspend(zdev->dev);

	return 0;
}