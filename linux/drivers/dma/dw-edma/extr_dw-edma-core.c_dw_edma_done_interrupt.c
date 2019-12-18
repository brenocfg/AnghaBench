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
struct dw_edma_desc {int /*<<< orphan*/  chunks_alloc; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct dw_edma_chan {int request; TYPE_1__ vc; void* status; } ;

/* Variables and functions */
#define  EDMA_REQ_NONE 130 
#define  EDMA_REQ_PAUSE 129 
#define  EDMA_REQ_STOP 128 
 void* EDMA_ST_BUSY ; 
 void* EDMA_ST_IDLE ; 
 void* EDMA_ST_PAUSE ; 
 int /*<<< orphan*/  dw_edma_start_transfer (struct dw_edma_chan*) ; 
 int /*<<< orphan*/  dw_edma_v0_core_clear_done_int (struct dw_edma_chan*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vchan_cookie_complete (struct virt_dma_desc*) ; 
 struct virt_dma_desc* vchan_next_desc (TYPE_1__*) ; 
 struct dw_edma_desc* vd2dw_edma_desc (struct virt_dma_desc*) ; 

__attribute__((used)) static void dw_edma_done_interrupt(struct dw_edma_chan *chan)
{
	struct dw_edma_desc *desc;
	struct virt_dma_desc *vd;
	unsigned long flags;

	dw_edma_v0_core_clear_done_int(chan);

	spin_lock_irqsave(&chan->vc.lock, flags);
	vd = vchan_next_desc(&chan->vc);
	if (vd) {
		switch (chan->request) {
		case EDMA_REQ_NONE:
			desc = vd2dw_edma_desc(vd);
			if (desc->chunks_alloc) {
				chan->status = EDMA_ST_BUSY;
				dw_edma_start_transfer(chan);
			} else {
				list_del(&vd->node);
				vchan_cookie_complete(vd);
				chan->status = EDMA_ST_IDLE;
			}
			break;

		case EDMA_REQ_STOP:
			list_del(&vd->node);
			vchan_cookie_complete(vd);
			chan->request = EDMA_REQ_NONE;
			chan->status = EDMA_ST_IDLE;
			break;

		case EDMA_REQ_PAUSE:
			chan->request = EDMA_REQ_NONE;
			chan->status = EDMA_ST_PAUSE;
			break;

		default:
			break;
		}
	}
	spin_unlock_irqrestore(&chan->vc.lock, flags);
}