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
struct pch_dma_chan {int /*<<< orphan*/  lock; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pdc_advance_work (struct pch_dma_chan*) ; 
 scalar_t__ pdc_is_idle (struct pch_dma_chan*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct pch_dma_chan* to_pd_chan (struct dma_chan*) ; 

__attribute__((used)) static void pd_issue_pending(struct dma_chan *chan)
{
	struct pch_dma_chan *pd_chan = to_pd_chan(chan);

	if (pdc_is_idle(pd_chan)) {
		spin_lock(&pd_chan->lock);
		pdc_advance_work(pd_chan);
		spin_unlock(&pd_chan->lock);
	}
}