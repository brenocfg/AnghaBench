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
struct fsldma_chan {int /*<<< orphan*/  desc_lock; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsl_chan_xfer_ld_queue (struct fsldma_chan*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct fsldma_chan* to_fsl_chan (struct dma_chan*) ; 

__attribute__((used)) static void fsl_dma_memcpy_issue_pending(struct dma_chan *dchan)
{
	struct fsldma_chan *chan = to_fsl_chan(dchan);

	spin_lock_bh(&chan->desc_lock);
	fsl_chan_xfer_ld_queue(chan);
	spin_unlock_bh(&chan->desc_lock);
}