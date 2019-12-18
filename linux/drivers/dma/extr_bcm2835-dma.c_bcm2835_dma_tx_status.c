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
struct virt_dma_desc {int /*<<< orphan*/  tx; } ;
struct dma_tx_state {int /*<<< orphan*/  residue; } ;
struct dma_chan {int dummy; } ;
struct TYPE_4__ {scalar_t__ cookie; } ;
struct TYPE_5__ {TYPE_1__ tx; } ;
struct bcm2835_desc {scalar_t__ dir; TYPE_2__ vd; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct bcm2835_chan {TYPE_3__ vc; scalar_t__ chan_base; struct bcm2835_desc* desc; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  scalar_t__ dma_cookie_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ BCM2835_DMA_DEST_AD ; 
 scalar_t__ BCM2835_DMA_SOURCE_AD ; 
 int DMA_COMPLETE ; 
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  bcm2835_dma_desc_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_dma_desc_size_pos (struct bcm2835_desc*,scalar_t__) ; 
 int dma_cookie_status (struct dma_chan*,scalar_t__,struct dma_tx_state*) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct bcm2835_chan* to_bcm2835_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  to_bcm2835_dma_desc (int /*<<< orphan*/ *) ; 
 struct virt_dma_desc* vchan_find_desc (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static enum dma_status bcm2835_dma_tx_status(struct dma_chan *chan,
	dma_cookie_t cookie, struct dma_tx_state *txstate)
{
	struct bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	struct virt_dma_desc *vd;
	enum dma_status ret;
	unsigned long flags;

	ret = dma_cookie_status(chan, cookie, txstate);
	if (ret == DMA_COMPLETE || !txstate)
		return ret;

	spin_lock_irqsave(&c->vc.lock, flags);
	vd = vchan_find_desc(&c->vc, cookie);
	if (vd) {
		txstate->residue =
			bcm2835_dma_desc_size(to_bcm2835_dma_desc(&vd->tx));
	} else if (c->desc && c->desc->vd.tx.cookie == cookie) {
		struct bcm2835_desc *d = c->desc;
		dma_addr_t pos;

		if (d->dir == DMA_MEM_TO_DEV)
			pos = readl(c->chan_base + BCM2835_DMA_SOURCE_AD);
		else if (d->dir == DMA_DEV_TO_MEM)
			pos = readl(c->chan_base + BCM2835_DMA_DEST_AD);
		else
			pos = 0;

		txstate->residue = bcm2835_dma_desc_size_pos(d, pos);
	} else {
		txstate->residue = 0;
	}

	spin_unlock_irqrestore(&c->vc.lock, flags);

	return ret;
}