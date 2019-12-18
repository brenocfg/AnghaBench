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
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcar_dmac_clear_chcr_de (struct rcar_dmac_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct rcar_dmac_chan* to_rcar_dmac_chan (struct dma_chan*) ; 

__attribute__((used)) static int rcar_dmac_chan_pause(struct dma_chan *chan)
{
	unsigned long flags;
	struct rcar_dmac_chan *rchan = to_rcar_dmac_chan(chan);

	spin_lock_irqsave(&rchan->lock, flags);
	rcar_dmac_clear_chcr_de(rchan);
	spin_unlock_irqrestore(&rchan->lock, flags);

	return 0;
}