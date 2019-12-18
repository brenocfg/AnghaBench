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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct sun6i_dma_dev {int /*<<< orphan*/  task; int /*<<< orphan*/  irq; TYPE_1__ slave; int /*<<< orphan*/  tasklet_shutdown; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ DMA_IRQ_EN (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sun6i_dma_dev*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void sun6i_kill_tasklet(struct sun6i_dma_dev *sdev)
{
	/* Disable all interrupts from DMA */
	writel(0, sdev->base + DMA_IRQ_EN(0));
	writel(0, sdev->base + DMA_IRQ_EN(1));

	/* Prevent spurious interrupts from scheduling the tasklet */
	atomic_inc(&sdev->tasklet_shutdown);

	/* Make sure we won't have any further interrupts */
	devm_free_irq(sdev->slave.dev, sdev->irq, sdev);

	/* Actually prevent the tasklet from being scheduled */
	tasklet_kill(&sdev->task);
}