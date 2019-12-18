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
struct fsl_edma_chan {int idle; TYPE_1__ vchan; int /*<<< orphan*/  status; scalar_t__ edesc; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_IN_PROGRESS ; 
 int /*<<< orphan*/  fsl_edma_enable_request (struct fsl_edma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct fsl_edma_chan* to_fsl_edma_chan (struct dma_chan*) ; 

int fsl_edma_resume(struct dma_chan *chan)
{
	struct fsl_edma_chan *fsl_chan = to_fsl_edma_chan(chan);
	unsigned long flags;

	spin_lock_irqsave(&fsl_chan->vchan.lock, flags);
	if (fsl_chan->edesc) {
		fsl_edma_enable_request(fsl_chan);
		fsl_chan->status = DMA_IN_PROGRESS;
		fsl_chan->idle = false;
	}
	spin_unlock_irqrestore(&fsl_chan->vchan.lock, flags);
	return 0;
}