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
struct sirfsoc_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  queued; int /*<<< orphan*/  active; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 struct sirfsoc_dma_chan* dma_chan_to_sirfsoc_dma_chan (struct dma_chan*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sirfsoc_dma_execute (struct sirfsoc_dma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sirfsoc_dma_issue_pending(struct dma_chan *chan)
{
	struct sirfsoc_dma_chan *schan = dma_chan_to_sirfsoc_dma_chan(chan);
	unsigned long flags;

	spin_lock_irqsave(&schan->lock, flags);

	if (list_empty(&schan->active) && !list_empty(&schan->queued))
		sirfsoc_dma_execute(schan);

	spin_unlock_irqrestore(&schan->lock, flags);
}