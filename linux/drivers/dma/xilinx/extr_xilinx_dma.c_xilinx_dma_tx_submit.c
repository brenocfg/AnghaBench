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
struct xilinx_dma_tx_descriptor {scalar_t__ cyclic; } ;
struct xilinx_dma_chan {int cyclic; int /*<<< orphan*/  lock; scalar_t__ err; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  chan; } ;
typedef  int dma_cookie_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  append_desc_queue (struct xilinx_dma_chan*,struct xilinx_dma_tx_descriptor*) ; 
 int dma_cookie_assign (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct xilinx_dma_tx_descriptor* to_dma_tx_descriptor (struct dma_async_tx_descriptor*) ; 
 struct xilinx_dma_chan* to_xilinx_chan (int /*<<< orphan*/ ) ; 
 int xilinx_dma_chan_reset (struct xilinx_dma_chan*) ; 
 int /*<<< orphan*/  xilinx_dma_free_tx_descriptor (struct xilinx_dma_chan*,struct xilinx_dma_tx_descriptor*) ; 

__attribute__((used)) static dma_cookie_t xilinx_dma_tx_submit(struct dma_async_tx_descriptor *tx)
{
	struct xilinx_dma_tx_descriptor *desc = to_dma_tx_descriptor(tx);
	struct xilinx_dma_chan *chan = to_xilinx_chan(tx->chan);
	dma_cookie_t cookie;
	unsigned long flags;
	int err;

	if (chan->cyclic) {
		xilinx_dma_free_tx_descriptor(chan, desc);
		return -EBUSY;
	}

	if (chan->err) {
		/*
		 * If reset fails, need to hard reset the system.
		 * Channel is no longer functional
		 */
		err = xilinx_dma_chan_reset(chan);
		if (err < 0)
			return err;
	}

	spin_lock_irqsave(&chan->lock, flags);

	cookie = dma_cookie_assign(tx);

	/* Put this transaction onto the tail of the pending queue */
	append_desc_queue(chan, desc);

	if (desc->cyclic)
		chan->cyclic = true;

	spin_unlock_irqrestore(&chan->lock, flags);

	return cookie;
}