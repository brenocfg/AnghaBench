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
struct dma_async_tx_descriptor {int /*<<< orphan*/  cookie; } ;
struct txx9dmac_desc {int /*<<< orphan*/  desc_node; int /*<<< orphan*/  tx_list; struct dma_async_tx_descriptor txd; } ;
struct txx9dmac_chan {int /*<<< orphan*/  free_list; int /*<<< orphan*/  chan; } ;
struct dmaengine_desc_callback {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan2dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct txx9dmac_desc*) ; 
 int /*<<< orphan*/  dma_cookie_complete (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dma_descriptor_unmap (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dma_run_dependencies (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dmaengine_desc_callback_invoke (struct dmaengine_desc_callback*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmaengine_desc_get_callback (struct dma_async_tx_descriptor*,struct dmaengine_desc_callback*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txx9dmac_sync_desc_for_cpu (struct txx9dmac_chan*,struct txx9dmac_desc*) ; 

__attribute__((used)) static void
txx9dmac_descriptor_complete(struct txx9dmac_chan *dc,
			     struct txx9dmac_desc *desc)
{
	struct dmaengine_desc_callback cb;
	struct dma_async_tx_descriptor *txd = &desc->txd;

	dev_vdbg(chan2dev(&dc->chan), "descriptor %u %p complete\n",
		 txd->cookie, desc);

	dma_cookie_complete(txd);
	dmaengine_desc_get_callback(txd, &cb);

	txx9dmac_sync_desc_for_cpu(dc, desc);
	list_splice_init(&desc->tx_list, &dc->free_list);
	list_move(&desc->desc_node, &dc->free_list);

	dma_descriptor_unmap(txd);
	/*
	 * The API requires that no submissions are done from a
	 * callback, so we don't need to drop the lock here
	 */
	dmaengine_desc_callback_invoke(&cb, NULL);
	dma_run_dependencies(txd);
}