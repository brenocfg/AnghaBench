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
struct fsldma_chan {int idle; int /*<<< orphan*/  desc_lock; int /*<<< orphan*/  ld_completed; int /*<<< orphan*/  ld_running; int /*<<< orphan*/  ld_pending; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dma_halt (struct fsldma_chan*) ; 
 int /*<<< orphan*/  fsldma_free_desc_list (struct fsldma_chan*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct fsldma_chan* to_fsl_chan (struct dma_chan*) ; 

__attribute__((used)) static int fsl_dma_device_terminate_all(struct dma_chan *dchan)
{
	struct fsldma_chan *chan;

	if (!dchan)
		return -EINVAL;

	chan = to_fsl_chan(dchan);

	spin_lock_bh(&chan->desc_lock);

	/* Halt the DMA engine */
	dma_halt(chan);

	/* Remove and free all of the descriptors in the LD queue */
	fsldma_free_desc_list(chan, &chan->ld_pending);
	fsldma_free_desc_list(chan, &chan->ld_running);
	fsldma_free_desc_list(chan, &chan->ld_completed);
	chan->idle = true;

	spin_unlock_bh(&chan->desc_lock);
	return 0;
}