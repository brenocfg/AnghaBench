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
struct pl08x_dma_chan {scalar_t__ state; TYPE_1__ vc; int /*<<< orphan*/  phychan; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ PL08X_CHAN_WAITING ; 
 int /*<<< orphan*/  pl08x_phy_alloc_and_start (struct pl08x_dma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pl08x_dma_chan* to_pl08x_chan (struct dma_chan*) ; 
 scalar_t__ vchan_issue_pending (TYPE_1__*) ; 

__attribute__((used)) static void pl08x_issue_pending(struct dma_chan *chan)
{
	struct pl08x_dma_chan *plchan = to_pl08x_chan(chan);
	unsigned long flags;

	spin_lock_irqsave(&plchan->vc.lock, flags);
	if (vchan_issue_pending(&plchan->vc)) {
		if (!plchan->phychan && plchan->state != PL08X_CHAN_WAITING)
			pl08x_phy_alloc_and_start(plchan);
	}
	spin_unlock_irqrestore(&plchan->vc.lock, flags);
}