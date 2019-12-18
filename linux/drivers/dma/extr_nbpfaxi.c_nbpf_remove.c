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
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct nbpf_device {int /*<<< orphan*/  clk; int /*<<< orphan*/  dma_dev; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  irq; struct nbpf_device* chan; TYPE_1__* config; int /*<<< orphan*/  eirq; } ;
struct nbpf_channel {int /*<<< orphan*/  clk; int /*<<< orphan*/  dma_dev; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  irq; struct nbpf_channel* chan; TYPE_1__* config; int /*<<< orphan*/  eirq; } ;
struct TYPE_3__ {int num_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_free_irq (TYPE_2__*,int /*<<< orphan*/ ,struct nbpf_device*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_dma_controller_free (int /*<<< orphan*/ ) ; 
 struct nbpf_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nbpf_remove(struct platform_device *pdev)
{
	struct nbpf_device *nbpf = platform_get_drvdata(pdev);
	int i;

	devm_free_irq(&pdev->dev, nbpf->eirq, nbpf);

	for (i = 0; i < nbpf->config->num_channels; i++) {
		struct nbpf_channel *chan = nbpf->chan + i;

		devm_free_irq(&pdev->dev, chan->irq, chan);

		tasklet_kill(&chan->tasklet);
	}

	of_dma_controller_free(pdev->dev.of_node);
	dma_async_device_unregister(&nbpf->dma_dev);
	clk_disable_unprepare(nbpf->clk);

	return 0;
}