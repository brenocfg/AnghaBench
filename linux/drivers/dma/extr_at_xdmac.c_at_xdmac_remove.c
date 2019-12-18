#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct at_xdmac_chan {int /*<<< orphan*/  chan; int /*<<< orphan*/  tasklet; } ;
struct TYPE_4__ {int chancnt; } ;
struct at_xdmac {struct at_xdmac_chan* chan; TYPE_2__ dma; int /*<<< orphan*/  irq; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  at_xdmac_free_chan_resources (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  at_xdmac_off (struct at_xdmac*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_async_device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct at_xdmac*) ; 
 int /*<<< orphan*/  of_dma_controller_free (int /*<<< orphan*/ ) ; 
 scalar_t__ platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int at_xdmac_remove(struct platform_device *pdev)
{
	struct at_xdmac	*atxdmac = (struct at_xdmac *)platform_get_drvdata(pdev);
	int		i;

	at_xdmac_off(atxdmac);
	of_dma_controller_free(pdev->dev.of_node);
	dma_async_device_unregister(&atxdmac->dma);
	clk_disable_unprepare(atxdmac->clk);

	free_irq(atxdmac->irq, atxdmac);

	for (i = 0; i < atxdmac->dma.chancnt; i++) {
		struct at_xdmac_chan *atchan = &atxdmac->chan[i];

		tasklet_kill(&atchan->tasklet);
		at_xdmac_free_chan_resources(&atchan->chan);
	}

	return 0;
}