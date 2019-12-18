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
struct xgene_dma_chan {int /*<<< orphan*/  lock; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct xgene_dma_chan* to_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  xgene_chan_xfer_ld_pending (struct xgene_dma_chan*) ; 

__attribute__((used)) static void xgene_dma_issue_pending(struct dma_chan *dchan)
{
	struct xgene_dma_chan *chan = to_dma_chan(dchan);

	spin_lock_bh(&chan->lock);
	xgene_chan_xfer_ld_pending(chan);
	spin_unlock_bh(&chan->lock);
}