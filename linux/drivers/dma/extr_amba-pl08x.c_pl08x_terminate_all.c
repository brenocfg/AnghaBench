#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pl08x_driver_data {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct pl08x_dma_chan {TYPE_2__ vc; TYPE_1__* at; scalar_t__ phychan; int /*<<< orphan*/  state; struct pl08x_driver_data* host; } ;
struct dma_chan {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  vd; } ;

/* Variables and functions */
 int /*<<< orphan*/  PL08X_CHAN_IDLE ; 
 int /*<<< orphan*/  pl08x_free_txd_list (struct pl08x_driver_data*,struct pl08x_dma_chan*) ; 
 int /*<<< orphan*/  pl08x_phy_free (struct pl08x_dma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pl08x_dma_chan* to_pl08x_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_terminate_vdesc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pl08x_terminate_all(struct dma_chan *chan)
{
	struct pl08x_dma_chan *plchan = to_pl08x_chan(chan);
	struct pl08x_driver_data *pl08x = plchan->host;
	unsigned long flags;

	spin_lock_irqsave(&plchan->vc.lock, flags);
	if (!plchan->phychan && !plchan->at) {
		spin_unlock_irqrestore(&plchan->vc.lock, flags);
		return 0;
	}

	plchan->state = PL08X_CHAN_IDLE;

	if (plchan->phychan) {
		/*
		 * Mark physical channel as free and free any slave
		 * signal
		 */
		pl08x_phy_free(plchan);
	}
	/* Dequeue jobs and free LLIs */
	if (plchan->at) {
		vchan_terminate_vdesc(&plchan->at->vd);
		plchan->at = NULL;
	}
	/* Dequeue jobs not yet fired as well */
	pl08x_free_txd_list(pl08x, plchan);

	spin_unlock_irqrestore(&plchan->vc.lock, flags);

	return 0;
}