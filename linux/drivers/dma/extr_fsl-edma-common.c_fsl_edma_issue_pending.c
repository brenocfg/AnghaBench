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
struct fsl_edma_chan {scalar_t__ pm_state; TYPE_1__ vchan; int /*<<< orphan*/  edesc; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ RUNNING ; 
 int /*<<< orphan*/  fsl_edma_xfer_desc (struct fsl_edma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct fsl_edma_chan* to_fsl_edma_chan (struct dma_chan*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vchan_issue_pending (TYPE_1__*) ; 

void fsl_edma_issue_pending(struct dma_chan *chan)
{
	struct fsl_edma_chan *fsl_chan = to_fsl_edma_chan(chan);
	unsigned long flags;

	spin_lock_irqsave(&fsl_chan->vchan.lock, flags);

	if (unlikely(fsl_chan->pm_state != RUNNING)) {
		spin_unlock_irqrestore(&fsl_chan->vchan.lock, flags);
		/* cannot submit due to suspend */
		return;
	}

	if (vchan_issue_pending(&fsl_chan->vchan) && !fsl_chan->edesc)
		fsl_edma_xfer_desc(fsl_chan);

	spin_unlock_irqrestore(&fsl_chan->vchan.lock, flags);
}