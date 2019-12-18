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
struct virt_dma_desc {int /*<<< orphan*/  node; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct dw_edma_chan {int /*<<< orphan*/  status; int /*<<< orphan*/  request; TYPE_1__ vc; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDMA_REQ_NONE ; 
 int /*<<< orphan*/  EDMA_ST_IDLE ; 
 int /*<<< orphan*/  dw_edma_v0_core_clear_abort_int (struct dw_edma_chan*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vchan_cookie_complete (struct virt_dma_desc*) ; 
 struct virt_dma_desc* vchan_next_desc (TYPE_1__*) ; 

__attribute__((used)) static void dw_edma_abort_interrupt(struct dw_edma_chan *chan)
{
	struct virt_dma_desc *vd;
	unsigned long flags;

	dw_edma_v0_core_clear_abort_int(chan);

	spin_lock_irqsave(&chan->vc.lock, flags);
	vd = vchan_next_desc(&chan->vc);
	if (vd) {
		list_del(&vd->node);
		vchan_cookie_complete(vd);
	}
	spin_unlock_irqrestore(&chan->vc.lock, flags);
	chan->request = EDMA_REQ_NONE;
	chan->status = EDMA_ST_IDLE;
}