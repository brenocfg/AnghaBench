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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct hidma_dev {TYPE_1__ ddev; int /*<<< orphan*/  lldev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ hidma_ll_disable (int /*<<< orphan*/ ) ; 
 struct hidma_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hidma_shutdown(struct platform_device *pdev)
{
	struct hidma_dev *dmadev = platform_get_drvdata(pdev);

	dev_info(dmadev->ddev.dev, "HI-DMA engine shutdown\n");

	pm_runtime_get_sync(dmadev->ddev.dev);
	if (hidma_ll_disable(dmadev->lldev))
		dev_warn(dmadev->ddev.dev, "channel did not stop\n");
	pm_runtime_mark_last_busy(dmadev->ddev.dev);
	pm_runtime_put_autosuspend(dmadev->ddev.dev);

}