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
struct xgene_dma_desc_sw {int /*<<< orphan*/  tx_list; } ;
struct xgene_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  ld_pending; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  chan; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  dma_cookie_assign (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct xgene_dma_chan* to_dma_chan (int /*<<< orphan*/ ) ; 
 struct xgene_dma_desc_sw* to_dma_desc_sw (struct dma_async_tx_descriptor*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static dma_cookie_t xgene_dma_tx_submit(struct dma_async_tx_descriptor *tx)
{
	struct xgene_dma_desc_sw *desc;
	struct xgene_dma_chan *chan;
	dma_cookie_t cookie;

	if (unlikely(!tx))
		return -EINVAL;

	chan = to_dma_chan(tx->chan);
	desc = to_dma_desc_sw(tx);

	spin_lock_bh(&chan->lock);

	cookie = dma_cookie_assign(tx);

	/* Add this transaction list onto the tail of the pending queue */
	list_splice_tail_init(&desc->tx_list, &chan->ld_pending);

	spin_unlock_bh(&chan->lock);

	return cookie;
}