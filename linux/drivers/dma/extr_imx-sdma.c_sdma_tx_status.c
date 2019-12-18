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
typedef  scalar_t__ u32 ;
struct virt_dma_desc {int /*<<< orphan*/  tx; } ;
struct sdma_desc {int num_bd; int buf_ptail; int period_len; scalar_t__ chn_real_count; scalar_t__ chn_count; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct sdma_channel {int flags; int status; TYPE_4__ vc; TYPE_3__* desc; } ;
struct dma_tx_state {int dummy; } ;
struct dma_chan {int /*<<< orphan*/  cookie; int /*<<< orphan*/  completed_cookie; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  scalar_t__ dma_cookie_t ;
struct TYPE_5__ {scalar_t__ cookie; } ;
struct TYPE_6__ {TYPE_1__ tx; } ;
struct TYPE_7__ {scalar_t__ chn_real_count; scalar_t__ chn_count; TYPE_2__ vd; } ;

/* Variables and functions */
 int DMA_COMPLETE ; 
 int IMX_DMA_SG_LOOP ; 
 int dma_cookie_status (struct dma_chan*,scalar_t__,struct dma_tx_state*) ; 
 int /*<<< orphan*/  dma_set_tx_state (struct dma_tx_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct sdma_channel* to_sdma_chan (struct dma_chan*) ; 
 struct sdma_desc* to_sdma_desc (int /*<<< orphan*/ *) ; 
 struct virt_dma_desc* vchan_find_desc (TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static enum dma_status sdma_tx_status(struct dma_chan *chan,
				      dma_cookie_t cookie,
				      struct dma_tx_state *txstate)
{
	struct sdma_channel *sdmac = to_sdma_chan(chan);
	struct sdma_desc *desc;
	u32 residue;
	struct virt_dma_desc *vd;
	enum dma_status ret;
	unsigned long flags;

	ret = dma_cookie_status(chan, cookie, txstate);
	if (ret == DMA_COMPLETE || !txstate)
		return ret;

	spin_lock_irqsave(&sdmac->vc.lock, flags);
	vd = vchan_find_desc(&sdmac->vc, cookie);
	if (vd) {
		desc = to_sdma_desc(&vd->tx);
		if (sdmac->flags & IMX_DMA_SG_LOOP)
			residue = (desc->num_bd - desc->buf_ptail) *
				desc->period_len - desc->chn_real_count;
		else
			residue = desc->chn_count - desc->chn_real_count;
	} else if (sdmac->desc && sdmac->desc->vd.tx.cookie == cookie) {
		residue = sdmac->desc->chn_count - sdmac->desc->chn_real_count;
	} else {
		residue = 0;
	}
	spin_unlock_irqrestore(&sdmac->vc.lock, flags);

	dma_set_tx_state(txstate, chan->completed_cookie, chan->cookie,
			 residue);

	return sdmac->status;
}