#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct virt_dma_desc {int /*<<< orphan*/  tx; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct edma_chan {TYPE_2__ vchan; TYPE_5__* edesc; } ;
struct dma_tx_state {int /*<<< orphan*/  residue; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  scalar_t__ dma_cookie_t ;
struct TYPE_6__ {scalar_t__ cookie; } ;
struct TYPE_8__ {TYPE_1__ tx; } ;
struct TYPE_10__ {TYPE_3__ vdesc; scalar_t__ polled; } ;
struct TYPE_9__ {int /*<<< orphan*/  residue; } ;

/* Variables and functions */
 int DMA_COMPLETE ; 
 int dma_cookie_status (struct dma_chan*,scalar_t__,struct dma_tx_state*) ; 
 int /*<<< orphan*/  edma_execute (struct edma_chan*) ; 
 int /*<<< orphan*/  edma_residue (TYPE_5__*) ; 
 int /*<<< orphan*/  edma_stop (struct edma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct edma_chan* to_edma_chan (struct dma_chan*) ; 
 TYPE_4__* to_edma_desc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_cookie_complete (TYPE_3__*) ; 
 struct virt_dma_desc* vchan_find_desc (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static enum dma_status edma_tx_status(struct dma_chan *chan,
				      dma_cookie_t cookie,
				      struct dma_tx_state *txstate)
{
	struct edma_chan *echan = to_edma_chan(chan);
	struct dma_tx_state txstate_tmp;
	enum dma_status ret;
	unsigned long flags;

	ret = dma_cookie_status(chan, cookie, txstate);

	if (ret == DMA_COMPLETE)
		return ret;

	/* Provide a dummy dma_tx_state for completion checking */
	if (!txstate)
		txstate = &txstate_tmp;

	spin_lock_irqsave(&echan->vchan.lock, flags);
	if (echan->edesc && echan->edesc->vdesc.tx.cookie == cookie) {
		txstate->residue = edma_residue(echan->edesc);
	} else {
		struct virt_dma_desc *vdesc = vchan_find_desc(&echan->vchan,
							      cookie);

		if (vdesc)
			txstate->residue = to_edma_desc(&vdesc->tx)->residue;
		else
			txstate->residue = 0;
	}

	/*
	 * Mark the cookie completed if the residue is 0 for non cyclic
	 * transfers
	 */
	if (ret != DMA_COMPLETE && !txstate->residue &&
	    echan->edesc && echan->edesc->polled &&
	    echan->edesc->vdesc.tx.cookie == cookie) {
		edma_stop(echan);
		vchan_cookie_complete(&echan->edesc->vdesc);
		echan->edesc = NULL;
		edma_execute(echan);
		ret = DMA_COMPLETE;
	}

	spin_unlock_irqrestore(&echan->vchan.lock, flags);

	return ret;
}