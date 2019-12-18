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
struct fsldma_chan {int idle; int /*<<< orphan*/  desc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan_dbg (struct fsldma_chan*,char*) ; 
 int /*<<< orphan*/  fsldma_cleanup_descriptors (struct fsldma_chan*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dma_do_tasklet(unsigned long data)
{
	struct fsldma_chan *chan = (struct fsldma_chan *)data;

	chan_dbg(chan, "tasklet entry\n");

	spin_lock(&chan->desc_lock);

	/* the hardware is now idle and ready for more */
	chan->idle = true;

	/* Run all cleanup for descriptors which have been completed */
	fsldma_cleanup_descriptors(chan);

	spin_unlock(&chan->desc_lock);

	chan_dbg(chan, "tasklet exit\n");
}