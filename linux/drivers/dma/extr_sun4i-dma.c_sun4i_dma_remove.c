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
struct sun4i_dma_dev {int /*<<< orphan*/  clk; int /*<<< orphan*/  slave; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_dma_controller_free (int /*<<< orphan*/ ) ; 
 struct sun4i_dma_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int sun4i_dma_remove(struct platform_device *pdev)
{
	struct sun4i_dma_dev *priv = platform_get_drvdata(pdev);

	/* Disable IRQ so no more work is scheduled */
	disable_irq(priv->irq);

	of_dma_controller_free(pdev->dev.of_node);
	dma_async_device_unregister(&priv->slave);

	clk_disable_unprepare(priv->clk);

	return 0;
}