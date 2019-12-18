#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dma_chan {int dummy; } ;
struct coh901318_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  coh901318_queue_start (struct coh901318_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct coh901318_chan* to_coh901318_chan (struct dma_chan*) ; 

__attribute__((used)) static void
coh901318_issue_pending(struct dma_chan *chan)
{
	struct coh901318_chan *cohc = to_coh901318_chan(chan);
	unsigned long flags;

	spin_lock_irqsave(&cohc->lock, flags);

	/*
	 * Busy means that pending jobs are already being processed,
	 * and then there is no point in starting the queue: the
	 * terminal count interrupt on the channel will take the next
	 * job on the queue and execute it anyway.
	 */
	if (!cohc->busy)
		coh901318_queue_start(cohc);

	spin_unlock_irqrestore(&cohc->lock, flags);
}