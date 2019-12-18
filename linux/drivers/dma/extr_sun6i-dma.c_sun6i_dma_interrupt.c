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
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct sun6i_vchan {int irq_type; TYPE_3__ vc; scalar_t__ cyclic; } ;
struct sun6i_pchan {TYPE_2__* desc; TYPE_2__* done; struct sun6i_vchan* vchan; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct sun6i_dma_dev {int num_pchans; int /*<<< orphan*/  task; int /*<<< orphan*/  tasklet_shutdown; struct sun6i_pchan* pchans; scalar_t__ base; TYPE_1__ slave; } ;
typedef  int irqreturn_t ;
struct TYPE_5__ {int /*<<< orphan*/  vd; } ;

/* Variables and functions */
 int DMA_IRQ_CHAN_NR ; 
 int DMA_IRQ_CHAN_WIDTH ; 
 scalar_t__ DMA_IRQ_STAT (int) ; 
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_cookie_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_cyclic_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t sun6i_dma_interrupt(int irq, void *dev_id)
{
	struct sun6i_dma_dev *sdev = dev_id;
	struct sun6i_vchan *vchan;
	struct sun6i_pchan *pchan;
	int i, j, ret = IRQ_NONE;
	u32 status;

	for (i = 0; i < sdev->num_pchans / DMA_IRQ_CHAN_NR; i++) {
		status = readl(sdev->base + DMA_IRQ_STAT(i));
		if (!status)
			continue;

		dev_dbg(sdev->slave.dev, "DMA irq status %s: 0x%x\n",
			i ? "high" : "low", status);

		writel(status, sdev->base + DMA_IRQ_STAT(i));

		for (j = 0; (j < DMA_IRQ_CHAN_NR) && status; j++) {
			pchan = sdev->pchans + j;
			vchan = pchan->vchan;
			if (vchan && (status & vchan->irq_type)) {
				if (vchan->cyclic) {
					vchan_cyclic_callback(&pchan->desc->vd);
				} else {
					spin_lock(&vchan->vc.lock);
					vchan_cookie_complete(&pchan->desc->vd);
					pchan->done = pchan->desc;
					spin_unlock(&vchan->vc.lock);
				}
			}

			status = status >> DMA_IRQ_CHAN_WIDTH;
		}

		if (!atomic_read(&sdev->tasklet_shutdown))
			tasklet_schedule(&sdev->task);
		ret = IRQ_HANDLED;
	}

	return ret;
}