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
struct sdma_engine {struct sdma_channel* channel; int /*<<< orphan*/  clk_ipg; int /*<<< orphan*/  clk_ahb; int /*<<< orphan*/  script_addrs; int /*<<< orphan*/  dma_device; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  chan; int /*<<< orphan*/  task; } ;
struct sdma_channel {TYPE_1__ vc; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MAX_DMA_CHANNELS ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sdma_engine*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct sdma_engine* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdma_free_chan_resources (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sdma_remove(struct platform_device *pdev)
{
	struct sdma_engine *sdma = platform_get_drvdata(pdev);
	int i;

	devm_free_irq(&pdev->dev, sdma->irq, sdma);
	dma_async_device_unregister(&sdma->dma_device);
	kfree(sdma->script_addrs);
	clk_unprepare(sdma->clk_ahb);
	clk_unprepare(sdma->clk_ipg);
	/* Kill the tasklet */
	for (i = 0; i < MAX_DMA_CHANNELS; i++) {
		struct sdma_channel *sdmac = &sdma->channel[i];

		tasklet_kill(&sdmac->vc.task);
		sdma_free_chan_resources(&sdmac->vc.chan);
	}

	platform_set_drvdata(pdev, NULL);
	return 0;
}