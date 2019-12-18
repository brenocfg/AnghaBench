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
struct sa11x0_dma_dev {int /*<<< orphan*/  base; int /*<<< orphan*/  task; int /*<<< orphan*/ * phy; int /*<<< orphan*/  slave; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 unsigned int NR_PHY_CHAN ; 
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sa11x0_dma_dev*) ; 
 struct sa11x0_dma_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sa11x0_dma_free_channels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sa11x0_dma_free_irq (struct platform_device*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sa11x0_dma_remove(struct platform_device *pdev)
{
	struct sa11x0_dma_dev *d = platform_get_drvdata(pdev);
	unsigned pch;

	dma_async_device_unregister(&d->slave);

	sa11x0_dma_free_channels(&d->slave);
	for (pch = 0; pch < NR_PHY_CHAN; pch++)
		sa11x0_dma_free_irq(pdev, pch, &d->phy[pch]);
	tasklet_kill(&d->task);
	iounmap(d->base);
	kfree(d);

	return 0;
}