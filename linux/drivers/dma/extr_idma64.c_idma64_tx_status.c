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
struct virt_dma_desc {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;
struct idma64_chan {TYPE_4__ vchan; TYPE_3__* desc; } ;
struct dma_tx_state {int dummy; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  scalar_t__ dma_cookie_t ;
struct TYPE_10__ {size_t length; } ;
struct TYPE_6__ {scalar_t__ cookie; } ;
struct TYPE_7__ {TYPE_1__ tx; } ;
struct TYPE_8__ {int status; TYPE_2__ vdesc; } ;

/* Variables and functions */
 int DMA_COMPLETE ; 
 int dma_cookie_status (struct dma_chan*,scalar_t__,struct dma_tx_state*) ; 
 int /*<<< orphan*/  dma_set_residue (struct dma_tx_state*,size_t) ; 
 size_t idma64_active_desc_size (struct idma64_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct idma64_chan* to_idma64_chan (struct dma_chan*) ; 
 TYPE_5__* to_idma64_desc (struct virt_dma_desc*) ; 
 struct virt_dma_desc* vchan_find_desc (TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static enum dma_status idma64_tx_status(struct dma_chan *chan,
		dma_cookie_t cookie, struct dma_tx_state *state)
{
	struct idma64_chan *idma64c = to_idma64_chan(chan);
	struct virt_dma_desc *vdesc;
	enum dma_status status;
	size_t bytes;
	unsigned long flags;

	status = dma_cookie_status(chan, cookie, state);
	if (status == DMA_COMPLETE)
		return status;

	spin_lock_irqsave(&idma64c->vchan.lock, flags);
	vdesc = vchan_find_desc(&idma64c->vchan, cookie);
	if (idma64c->desc && cookie == idma64c->desc->vdesc.tx.cookie) {
		bytes = idma64_active_desc_size(idma64c);
		dma_set_residue(state, bytes);
		status = idma64c->desc->status;
	} else if (vdesc) {
		bytes = to_idma64_desc(vdesc)->length;
		dma_set_residue(state, bytes);
	}
	spin_unlock_irqrestore(&idma64c->vchan.lock, flags);

	return status;
}