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
struct rcar_dmac_chan {int /*<<< orphan*/  lock; } ;
struct rcar_dmac {unsigned int n_channels; int channels_mask; struct rcar_dmac_chan* channels; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  rcar_dmac_chan_halt (struct rcar_dmac_chan*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rcar_dmac_stop_all_chan(struct rcar_dmac *dmac)
{
	unsigned int i;

	/* Stop all channels. */
	for (i = 0; i < dmac->n_channels; ++i) {
		struct rcar_dmac_chan *chan = &dmac->channels[i];

		if (!(dmac->channels_mask & BIT(i)))
			continue;

		/* Stop and reinitialize the channel. */
		spin_lock_irq(&chan->lock);
		rcar_dmac_chan_halt(chan);
		spin_unlock_irq(&chan->lock);
	}
}