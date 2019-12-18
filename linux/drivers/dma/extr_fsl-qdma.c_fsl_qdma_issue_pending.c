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
struct fsl_qdma_queue {int /*<<< orphan*/  queue_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct fsl_qdma_chan {TYPE_1__ vchan; struct fsl_qdma_queue* queue; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsl_qdma_enqueue_desc (struct fsl_qdma_chan*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct fsl_qdma_chan* to_fsl_qdma_chan (struct dma_chan*) ; 
 scalar_t__ vchan_issue_pending (TYPE_1__*) ; 

__attribute__((used)) static void fsl_qdma_issue_pending(struct dma_chan *chan)
{
	unsigned long flags;
	struct fsl_qdma_chan *fsl_chan = to_fsl_qdma_chan(chan);
	struct fsl_qdma_queue *fsl_queue = fsl_chan->queue;

	spin_lock_irqsave(&fsl_queue->queue_lock, flags);
	spin_lock(&fsl_chan->vchan.lock);
	if (vchan_issue_pending(&fsl_chan->vchan))
		fsl_qdma_enqueue_desc(fsl_chan);
	spin_unlock(&fsl_chan->vchan.lock);
	spin_unlock_irqrestore(&fsl_queue->queue_lock, flags);
}