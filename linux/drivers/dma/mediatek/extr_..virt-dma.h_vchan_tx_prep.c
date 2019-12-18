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
struct dma_async_tx_descriptor {unsigned long flags; int /*<<< orphan*/  desc_free; int /*<<< orphan*/  tx_submit; } ;
struct TYPE_2__ {scalar_t__ residue; int /*<<< orphan*/  result; } ;
struct virt_dma_desc {struct dma_async_tx_descriptor tx; int /*<<< orphan*/  node; TYPE_1__ tx_result; } ;
struct virt_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  desc_allocated; int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TRANS_NOERROR ; 
 int /*<<< orphan*/  dma_async_tx_descriptor_init (struct dma_async_tx_descriptor*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vchan_tx_desc_free ; 
 int /*<<< orphan*/  vchan_tx_submit ; 

__attribute__((used)) static inline struct dma_async_tx_descriptor *vchan_tx_prep(struct virt_dma_chan *vc,
	struct virt_dma_desc *vd, unsigned long tx_flags)
{
	unsigned long flags;

	dma_async_tx_descriptor_init(&vd->tx, &vc->chan);
	vd->tx.flags = tx_flags;
	vd->tx.tx_submit = vchan_tx_submit;
	vd->tx.desc_free = vchan_tx_desc_free;

	vd->tx_result.result = DMA_TRANS_NOERROR;
	vd->tx_result.residue = 0;

	spin_lock_irqsave(&vc->lock, flags);
	list_add_tail(&vd->node, &vc->desc_allocated);
	spin_unlock_irqrestore(&vc->lock, flags);

	return &vd->tx;
}