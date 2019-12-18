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
typedef  scalar_t__ u32 ;
struct virt_dma_desc {int dummy; } ;
struct TYPE_4__ {scalar_t__ cookie; } ;
struct TYPE_5__ {TYPE_1__ tx; } ;
struct sprd_dma_chn_hw {scalar_t__ trsc_len; scalar_t__ blk_len; scalar_t__ frg_len; } ;
struct sprd_dma_desc {scalar_t__ dir; TYPE_2__ vd; struct sprd_dma_chn_hw chn_hw; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct sprd_dma_chn {TYPE_3__ vc; struct sprd_dma_desc* cur_desc; } ;
struct dma_tx_state {int dummy; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  scalar_t__ dma_cookie_t ;

/* Variables and functions */
 int DMA_COMPLETE ; 
 scalar_t__ DMA_DEV_TO_MEM ; 
 int dma_cookie_status (struct dma_chan*,scalar_t__,struct dma_tx_state*) ; 
 int /*<<< orphan*/  dma_set_residue (struct dma_tx_state*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ sprd_dma_get_dst_addr (struct sprd_dma_chn*) ; 
 scalar_t__ sprd_dma_get_src_addr (struct sprd_dma_chn*) ; 
 struct sprd_dma_chn* to_sprd_dma_chan (struct dma_chan*) ; 
 struct sprd_dma_desc* to_sprd_dma_desc (struct virt_dma_desc*) ; 
 struct virt_dma_desc* vchan_find_desc (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static enum dma_status sprd_dma_tx_status(struct dma_chan *chan,
					  dma_cookie_t cookie,
					  struct dma_tx_state *txstate)
{
	struct sprd_dma_chn *schan = to_sprd_dma_chan(chan);
	struct virt_dma_desc *vd;
	unsigned long flags;
	enum dma_status ret;
	u32 pos;

	ret = dma_cookie_status(chan, cookie, txstate);
	if (ret == DMA_COMPLETE || !txstate)
		return ret;

	spin_lock_irqsave(&schan->vc.lock, flags);
	vd = vchan_find_desc(&schan->vc, cookie);
	if (vd) {
		struct sprd_dma_desc *sdesc = to_sprd_dma_desc(vd);
		struct sprd_dma_chn_hw *hw = &sdesc->chn_hw;

		if (hw->trsc_len > 0)
			pos = hw->trsc_len;
		else if (hw->blk_len > 0)
			pos = hw->blk_len;
		else if (hw->frg_len > 0)
			pos = hw->frg_len;
		else
			pos = 0;
	} else if (schan->cur_desc && schan->cur_desc->vd.tx.cookie == cookie) {
		struct sprd_dma_desc *sdesc = schan->cur_desc;

		if (sdesc->dir == DMA_DEV_TO_MEM)
			pos = sprd_dma_get_dst_addr(schan);
		else
			pos = sprd_dma_get_src_addr(schan);
	} else {
		pos = 0;
	}
	spin_unlock_irqrestore(&schan->vc.lock, flags);

	dma_set_residue(txstate, pos);
	return ret;
}