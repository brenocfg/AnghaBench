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
struct TYPE_4__ {TYPE_1__* running; } ;
struct rcar_dmac_chan {int /*<<< orphan*/  lock; TYPE_2__ desc; } ;
struct dma_tx_state {int dummy; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  int /*<<< orphan*/  dma_cookie_t ;
struct TYPE_3__ {int cyclic; } ;

/* Variables and functions */
 int DMA_COMPLETE ; 
 int dma_cookie_status (struct dma_chan*,int /*<<< orphan*/ ,struct dma_tx_state*) ; 
 int /*<<< orphan*/  dma_set_residue (struct dma_tx_state*,unsigned int) ; 
 unsigned int rcar_dmac_chan_get_residue (struct rcar_dmac_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct rcar_dmac_chan* to_rcar_dmac_chan (struct dma_chan*) ; 

__attribute__((used)) static enum dma_status rcar_dmac_tx_status(struct dma_chan *chan,
					   dma_cookie_t cookie,
					   struct dma_tx_state *txstate)
{
	struct rcar_dmac_chan *rchan = to_rcar_dmac_chan(chan);
	enum dma_status status;
	unsigned long flags;
	unsigned int residue;
	bool cyclic;

	status = dma_cookie_status(chan, cookie, txstate);
	if (status == DMA_COMPLETE || !txstate)
		return status;

	spin_lock_irqsave(&rchan->lock, flags);
	residue = rcar_dmac_chan_get_residue(rchan, cookie);
	cyclic = rchan->desc.running ? rchan->desc.running->cyclic : false;
	spin_unlock_irqrestore(&rchan->lock, flags);

	/* if there's no residue, the cookie is complete */
	if (!residue && !cyclic)
		return DMA_COMPLETE;

	dma_set_residue(txstate, residue);

	return status;
}