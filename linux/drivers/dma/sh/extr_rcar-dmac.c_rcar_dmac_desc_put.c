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
struct rcar_dmac_desc {int /*<<< orphan*/  node; int /*<<< orphan*/  chunks; } ;
struct TYPE_2__ {int /*<<< orphan*/  free; int /*<<< orphan*/  chunks_free; } ;
struct rcar_dmac_chan {int /*<<< orphan*/  lock; TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rcar_dmac_desc_put(struct rcar_dmac_chan *chan,
			       struct rcar_dmac_desc *desc)
{
	unsigned long flags;

	spin_lock_irqsave(&chan->lock, flags);
	list_splice_tail_init(&desc->chunks, &chan->desc.chunks_free);
	list_add(&desc->node, &chan->desc.free);
	spin_unlock_irqrestore(&chan->lock, flags);
}