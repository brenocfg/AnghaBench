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
struct fsldma_chan {int dummy; } ;
struct dma_async_tx_descriptor {scalar_t__ cookie; } ;
struct fsl_desc_sw {struct dma_async_tx_descriptor async_tx; } ;
typedef  scalar_t__ dma_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dma_descriptor_unmap (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dma_run_dependencies (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dmaengine_desc_get_callback_invoke (struct dma_async_tx_descriptor*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static dma_cookie_t fsldma_run_tx_complete_actions(struct fsldma_chan *chan,
		struct fsl_desc_sw *desc, dma_cookie_t cookie)
{
	struct dma_async_tx_descriptor *txd = &desc->async_tx;
	dma_cookie_t ret = cookie;

	BUG_ON(txd->cookie < 0);

	if (txd->cookie > 0) {
		ret = txd->cookie;

		dma_descriptor_unmap(txd);
		/* Run the link descriptor callback function */
		dmaengine_desc_get_callback_invoke(txd, NULL);
	}

	/* Run any dependencies */
	dma_run_dependencies(txd);

	return ret;
}