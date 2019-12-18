#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct bam_device {size_t num_channels; int /*<<< orphan*/  bamclk; int /*<<< orphan*/  task; TYPE_2__* channels; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  common; } ;
struct TYPE_4__ {int /*<<< orphan*/  task; int /*<<< orphan*/  chan; } ;
struct TYPE_5__ {int /*<<< orphan*/  fifo_phys; int /*<<< orphan*/  fifo_virt; TYPE_1__ vc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAM_DESC_FIFO_SIZE ; 
 int /*<<< orphan*/  BAM_IRQ_SRCS_MSK_EE ; 
 int /*<<< orphan*/  bam_addr (struct bam_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bam_dma_terminate_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bam_device*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_dma_controller_free (int /*<<< orphan*/ ) ; 
 struct bam_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_force_suspend (TYPE_3__*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bam_dma_remove(struct platform_device *pdev)
{
	struct bam_device *bdev = platform_get_drvdata(pdev);
	u32 i;

	pm_runtime_force_suspend(&pdev->dev);

	of_dma_controller_free(pdev->dev.of_node);
	dma_async_device_unregister(&bdev->common);

	/* mask all interrupts for this execution environment */
	writel_relaxed(0, bam_addr(bdev, 0,  BAM_IRQ_SRCS_MSK_EE));

	devm_free_irq(bdev->dev, bdev->irq, bdev);

	for (i = 0; i < bdev->num_channels; i++) {
		bam_dma_terminate_all(&bdev->channels[i].vc.chan);
		tasklet_kill(&bdev->channels[i].vc.task);

		if (!bdev->channels[i].fifo_virt)
			continue;

		dma_free_wc(bdev->dev, BAM_DESC_FIFO_SIZE,
			    bdev->channels[i].fifo_virt,
			    bdev->channels[i].fifo_phys);
	}

	tasklet_kill(&bdev->task);

	clk_disable_unprepare(bdev->bamclk);

	return 0;
}