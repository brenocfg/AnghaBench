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
struct sun6i_dma_dev {int /*<<< orphan*/  rstc; int /*<<< orphan*/  clk; int /*<<< orphan*/  clk_mbus; int /*<<< orphan*/  slave; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_dma_controller_free (int /*<<< orphan*/ ) ; 
 struct sun6i_dma_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun6i_dma_free (struct sun6i_dma_dev*) ; 
 int /*<<< orphan*/  sun6i_kill_tasklet (struct sun6i_dma_dev*) ; 

__attribute__((used)) static int sun6i_dma_remove(struct platform_device *pdev)
{
	struct sun6i_dma_dev *sdc = platform_get_drvdata(pdev);

	of_dma_controller_free(pdev->dev.of_node);
	dma_async_device_unregister(&sdc->slave);

	sun6i_kill_tasklet(sdc);

	clk_disable_unprepare(sdc->clk_mbus);
	clk_disable_unprepare(sdc->clk);
	reset_control_assert(sdc->rstc);

	sun6i_dma_free(sdc);

	return 0;
}