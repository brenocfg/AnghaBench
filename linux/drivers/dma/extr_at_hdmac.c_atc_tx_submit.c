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
struct dma_async_tx_descriptor {int /*<<< orphan*/  chan; } ;
struct at_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; int /*<<< orphan*/  active_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  cookie; } ;
struct at_desc {int /*<<< orphan*/  desc_node; TYPE_1__ txd; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  atc_dostart (struct at_dma_chan*,struct at_desc*) ; 
 int /*<<< orphan*/  chan2dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cookie_assign (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct at_dma_chan* to_at_dma_chan (int /*<<< orphan*/ ) ; 
 struct at_desc* txd_to_at_desc (struct dma_async_tx_descriptor*) ; 

__attribute__((used)) static dma_cookie_t atc_tx_submit(struct dma_async_tx_descriptor *tx)
{
	struct at_desc		*desc = txd_to_at_desc(tx);
	struct at_dma_chan	*atchan = to_at_dma_chan(tx->chan);
	dma_cookie_t		cookie;
	unsigned long		flags;

	spin_lock_irqsave(&atchan->lock, flags);
	cookie = dma_cookie_assign(tx);

	if (list_empty(&atchan->active_list)) {
		dev_vdbg(chan2dev(tx->chan), "tx_submit: started %u\n",
				desc->txd.cookie);
		atc_dostart(atchan, desc);
		list_add_tail(&desc->desc_node, &atchan->active_list);
	} else {
		dev_vdbg(chan2dev(tx->chan), "tx_submit: queued %u\n",
				desc->txd.cookie);
		list_add_tail(&desc->desc_node, &atchan->queue);
	}

	spin_unlock_irqrestore(&atchan->lock, flags);

	return cookie;
}