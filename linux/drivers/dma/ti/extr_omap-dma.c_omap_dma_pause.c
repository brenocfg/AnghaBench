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
struct omap_dmadev {int /*<<< orphan*/  irq_lock; } ;
struct omap_chan {int paused; TYPE_1__* desc; scalar_t__ cyclic; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {scalar_t__ dir; } ;

/* Variables and functions */
 scalar_t__ DMA_DEV_TO_MEM ; 
 int EINVAL ; 
 int omap_dma_stop (struct omap_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct omap_chan* to_omap_dma_chan (struct dma_chan*) ; 
 struct omap_dmadev* to_omap_dma_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_dma_pause(struct dma_chan *chan)
{
	struct omap_chan *c = to_omap_dma_chan(chan);
	struct omap_dmadev *od = to_omap_dma_dev(chan->device);
	unsigned long flags;
	int ret = -EINVAL;
	bool can_pause = false;

	spin_lock_irqsave(&od->irq_lock, flags);

	if (!c->desc)
		goto out;

	if (c->cyclic)
		can_pause = true;

	/*
	 * We do not allow DMA_MEM_TO_DEV transfers to be paused.
	 * From the AM572x TRM, 16.1.4.18 Disabling a Channel During Transfer:
	 * "When a channel is disabled during a transfer, the channel undergoes
	 * an abort, unless it is hardware-source-synchronized …".
	 * A source-synchronised channel is one where the fetching of data is
	 * under control of the device. In other words, a device-to-memory
	 * transfer. So, a destination-synchronised channel (which would be a
	 * memory-to-device transfer) undergoes an abort if the the CCR_ENABLE
	 * bit is cleared.
	 * From 16.1.4.20.4.6.2 Abort: "If an abort trigger occurs, the channel
	 * aborts immediately after completion of current read/write
	 * transactions and then the FIFO is cleaned up." The term "cleaned up"
	 * is not defined. TI recommends to check that RD_ACTIVE and WR_ACTIVE
	 * are both clear _before_ disabling the channel, otherwise data loss
	 * will occur.
	 * The problem is that if the channel is active, then device activity
	 * can result in DMA activity starting between reading those as both
	 * clear and the write to DMA_CCR to clear the enable bit hitting the
	 * hardware. If the DMA hardware can't drain the data in its FIFO to the
	 * destination, then data loss "might" occur (say if we write to an UART
	 * and the UART is not accepting any further data).
	 */
	else if (c->desc->dir == DMA_DEV_TO_MEM)
		can_pause = true;

	if (can_pause && !c->paused) {
		ret = omap_dma_stop(c);
		if (!ret)
			c->paused = true;
	}
out:
	spin_unlock_irqrestore(&od->irq_lock, flags);

	return ret;
}