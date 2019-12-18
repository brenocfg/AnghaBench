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
struct pl08x_dma_chan {TYPE_1__ vc; int /*<<< orphan*/  state; int /*<<< orphan*/  phychan; int /*<<< orphan*/  at; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PL08X_CHAN_PAUSED ; 
 int /*<<< orphan*/  pl08x_pause_phy_chan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pl08x_dma_chan* to_pl08x_chan (struct dma_chan*) ; 

__attribute__((used)) static int pl08x_pause(struct dma_chan *chan)
{
	struct pl08x_dma_chan *plchan = to_pl08x_chan(chan);
	unsigned long flags;

	/*
	 * Anything succeeds on channels with no physical allocation and
	 * no queued transfers.
	 */
	spin_lock_irqsave(&plchan->vc.lock, flags);
	if (!plchan->phychan && !plchan->at) {
		spin_unlock_irqrestore(&plchan->vc.lock, flags);
		return 0;
	}

	pl08x_pause_phy_chan(plchan->phychan);
	plchan->state = PL08X_CHAN_PAUSED;

	spin_unlock_irqrestore(&plchan->vc.lock, flags);

	return 0;
}