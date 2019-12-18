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
struct dma_async_tx_descriptor {int /*<<< orphan*/  cookie; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct at_dma_chan {int /*<<< orphan*/  free_list; TYPE_1__ chan_common; } ;
struct at_dma {int /*<<< orphan*/  memset_pool; } ;
struct at_desc {int memset_buffer; int /*<<< orphan*/  desc_node; int /*<<< orphan*/  tx_list; int /*<<< orphan*/  memset_paddr; int /*<<< orphan*/  memset_vaddr; struct dma_async_tx_descriptor txd; } ;

/* Variables and functions */
 int /*<<< orphan*/  atc_chan_is_cyclic (struct at_dma_chan*) ; 
 int /*<<< orphan*/  chan2dev (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cookie_complete (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dma_descriptor_unmap (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_run_dependencies (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dmaengine_desc_get_callback_invoke (struct dma_async_tx_descriptor*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct at_dma* to_at_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
atc_chain_complete(struct at_dma_chan *atchan, struct at_desc *desc)
{
	struct dma_async_tx_descriptor	*txd = &desc->txd;
	struct at_dma			*atdma = to_at_dma(atchan->chan_common.device);

	dev_vdbg(chan2dev(&atchan->chan_common),
		"descriptor %u complete\n", txd->cookie);

	/* mark the descriptor as complete for non cyclic cases only */
	if (!atc_chan_is_cyclic(atchan))
		dma_cookie_complete(txd);

	/* If the transfer was a memset, free our temporary buffer */
	if (desc->memset_buffer) {
		dma_pool_free(atdma->memset_pool, desc->memset_vaddr,
			      desc->memset_paddr);
		desc->memset_buffer = false;
	}

	/* move children to free_list */
	list_splice_init(&desc->tx_list, &atchan->free_list);
	/* move myself to free_list */
	list_move(&desc->desc_node, &atchan->free_list);

	dma_descriptor_unmap(txd);
	/* for cyclic transfers,
	 * no need to replay callback function while stopping */
	if (!atc_chan_is_cyclic(atchan)) {
		/*
		 * The API requires that no submissions are done from a
		 * callback, so we don't need to drop the lock here
		 */
		dmaengine_desc_get_callback_invoke(txd, NULL);
	}

	dma_run_dependencies(txd);
}