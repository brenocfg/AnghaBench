#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct virt_dma_desc {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct st_fdma_chan {TYPE_4__ vchan; TYPE_3__* fdesc; } ;
struct dma_tx_state {void* residue; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  scalar_t__ dma_cookie_t ;
struct TYPE_5__ {scalar_t__ cookie; } ;
struct TYPE_6__ {TYPE_1__ tx; } ;
struct TYPE_7__ {TYPE_2__ vdesc; } ;

/* Variables and functions */
 int DMA_COMPLETE ; 
 int dma_cookie_status (struct dma_chan*,scalar_t__,struct dma_tx_state*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 void* st_fdma_desc_residue (struct st_fdma_chan*,struct virt_dma_desc*,int) ; 
 struct st_fdma_chan* to_st_fdma_chan (struct dma_chan*) ; 
 struct virt_dma_desc* vchan_find_desc (TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static enum dma_status st_fdma_tx_status(struct dma_chan *chan,
					 dma_cookie_t cookie,
					 struct dma_tx_state *txstate)
{
	struct st_fdma_chan *fchan = to_st_fdma_chan(chan);
	struct virt_dma_desc *vd;
	enum dma_status ret;
	unsigned long flags;

	ret = dma_cookie_status(chan, cookie, txstate);
	if (ret == DMA_COMPLETE || !txstate)
		return ret;

	spin_lock_irqsave(&fchan->vchan.lock, flags);
	vd = vchan_find_desc(&fchan->vchan, cookie);
	if (fchan->fdesc && cookie == fchan->fdesc->vdesc.tx.cookie)
		txstate->residue = st_fdma_desc_residue(fchan, vd, true);
	else if (vd)
		txstate->residue = st_fdma_desc_residue(fchan, vd, false);
	else
		txstate->residue = 0;

	spin_unlock_irqrestore(&fchan->vchan.lock, flags);

	return ret;
}