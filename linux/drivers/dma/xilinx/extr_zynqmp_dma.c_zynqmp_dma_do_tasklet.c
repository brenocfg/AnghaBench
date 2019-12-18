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
typedef  scalar_t__ u32 ;
struct zynqmp_dma_chan {int err; int /*<<< orphan*/  lock; scalar_t__ idle; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ ZYNQMP_DMA_IRQ_DST_ACCT ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  zynqmp_dma_chan_desc_cleanup (struct zynqmp_dma_chan*) ; 
 int /*<<< orphan*/  zynqmp_dma_complete_descriptor (struct zynqmp_dma_chan*) ; 
 int /*<<< orphan*/  zynqmp_dma_reset (struct zynqmp_dma_chan*) ; 
 int /*<<< orphan*/  zynqmp_dma_start_transfer (struct zynqmp_dma_chan*) ; 

__attribute__((used)) static void zynqmp_dma_do_tasklet(unsigned long data)
{
	struct zynqmp_dma_chan *chan = (struct zynqmp_dma_chan *)data;
	u32 count;
	unsigned long irqflags;

	spin_lock_irqsave(&chan->lock, irqflags);

	if (chan->err) {
		zynqmp_dma_reset(chan);
		chan->err = false;
		goto unlock;
	}

	count = readl(chan->regs + ZYNQMP_DMA_IRQ_DST_ACCT);

	while (count) {
		zynqmp_dma_complete_descriptor(chan);
		zynqmp_dma_chan_desc_cleanup(chan);
		count--;
	}

	if (chan->idle)
		zynqmp_dma_start_transfer(chan);

unlock:
	spin_unlock_irqrestore(&chan->lock, irqflags);
}