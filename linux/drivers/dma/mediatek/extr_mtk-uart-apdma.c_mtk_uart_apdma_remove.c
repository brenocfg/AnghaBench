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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mtk_uart_apdmadev {int /*<<< orphan*/  ddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_uart_apdma_free (struct mtk_uart_apdmadev*) ; 
 int /*<<< orphan*/  of_dma_controller_free (int /*<<< orphan*/ ) ; 
 struct mtk_uart_apdmadev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 

__attribute__((used)) static int mtk_uart_apdma_remove(struct platform_device *pdev)
{
	struct mtk_uart_apdmadev *mtkd = platform_get_drvdata(pdev);

	of_dma_controller_free(pdev->dev.of_node);

	mtk_uart_apdma_free(mtkd);

	dma_async_device_unregister(&mtkd->ddev);

	pm_runtime_disable(&pdev->dev);

	return 0;
}