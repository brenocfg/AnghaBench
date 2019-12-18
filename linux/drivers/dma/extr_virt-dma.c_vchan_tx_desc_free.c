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
struct TYPE_6__ {int /*<<< orphan*/  cookie; } ;
struct virt_dma_desc {TYPE_3__ tx; int /*<<< orphan*/  node; } ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct virt_dma_chan {int /*<<< orphan*/  (* desc_free ) (struct virt_dma_desc*) ;TYPE_2__ chan; int /*<<< orphan*/  lock; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  chan; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct virt_dma_chan*,struct virt_dma_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct virt_dma_desc*) ; 
 struct virt_dma_chan* to_virt_chan (int /*<<< orphan*/ ) ; 
 struct virt_dma_desc* to_virt_desc (struct dma_async_tx_descriptor*) ; 

int vchan_tx_desc_free(struct dma_async_tx_descriptor *tx)
{
	struct virt_dma_chan *vc = to_virt_chan(tx->chan);
	struct virt_dma_desc *vd = to_virt_desc(tx);
	unsigned long flags;

	spin_lock_irqsave(&vc->lock, flags);
	list_del(&vd->node);
	spin_unlock_irqrestore(&vc->lock, flags);

	dev_dbg(vc->chan.device->dev, "vchan %p: txd %p[%x]: freeing\n",
		vc, vd, vd->tx.cookie);
	vc->desc_free(vd);
	return 0;
}