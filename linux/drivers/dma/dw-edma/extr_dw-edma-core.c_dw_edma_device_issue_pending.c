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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct dw_edma_chan {scalar_t__ request; scalar_t__ status; TYPE_1__ vc; scalar_t__ configured; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ EDMA_REQ_NONE ; 
 scalar_t__ EDMA_ST_BUSY ; 
 scalar_t__ EDMA_ST_IDLE ; 
 struct dw_edma_chan* dchan2dw_edma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  dw_edma_start_transfer (struct dw_edma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ vchan_issue_pending (TYPE_1__*) ; 

__attribute__((used)) static void dw_edma_device_issue_pending(struct dma_chan *dchan)
{
	struct dw_edma_chan *chan = dchan2dw_edma_chan(dchan);
	unsigned long flags;

	spin_lock_irqsave(&chan->vc.lock, flags);
	if (chan->configured && chan->request == EDMA_REQ_NONE &&
	    chan->status == EDMA_ST_IDLE && vchan_issue_pending(&chan->vc)) {
		chan->status = EDMA_ST_BUSY;
		dw_edma_start_transfer(chan);
	}
	spin_unlock_irqrestore(&chan->vc.lock, flags);
}