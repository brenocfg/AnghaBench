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
struct device {scalar_t__ of_node; } ;
struct platform_device {struct device dev; } ;
struct mpc_dma {int /*<<< orphan*/  tasklet; int /*<<< orphan*/  irq; int /*<<< orphan*/  irq2; scalar_t__ is_mpc8308; int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 struct mpc_dma* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mpc_dma*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_dma_controller_free (scalar_t__) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mpc_dma_remove(struct platform_device *op)
{
	struct device *dev = &op->dev;
	struct mpc_dma *mdma = dev_get_drvdata(dev);

	if (dev->of_node)
		of_dma_controller_free(dev->of_node);
	dma_async_device_unregister(&mdma->dma);
	if (mdma->is_mpc8308) {
		free_irq(mdma->irq2, mdma);
		irq_dispose_mapping(mdma->irq2);
	}
	free_irq(mdma->irq, mdma);
	irq_dispose_mapping(mdma->irq);
	tasklet_kill(&mdma->tasklet);

	return 0;
}