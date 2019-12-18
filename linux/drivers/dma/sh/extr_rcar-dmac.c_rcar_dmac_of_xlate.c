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
struct rcar_dmac_chan {int /*<<< orphan*/  mid_rid; } ;
struct of_phandle_args {int args_count; int /*<<< orphan*/ * args; } ;
struct of_dma {int /*<<< orphan*/  of_node; } ;
struct dma_chan {int dummy; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SLAVE ; 
 struct dma_chan* __dma_request_channel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct of_phandle_args*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_dmac_chan_filter ; 
 struct rcar_dmac_chan* to_rcar_dmac_chan (struct dma_chan*) ; 

__attribute__((used)) static struct dma_chan *rcar_dmac_of_xlate(struct of_phandle_args *dma_spec,
					   struct of_dma *ofdma)
{
	struct rcar_dmac_chan *rchan;
	struct dma_chan *chan;
	dma_cap_mask_t mask;

	if (dma_spec->args_count != 1)
		return NULL;

	/* Only slave DMA channels can be allocated via DT */
	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	chan = __dma_request_channel(&mask, rcar_dmac_chan_filter, dma_spec,
				     ofdma->of_node);
	if (!chan)
		return NULL;

	rchan = to_rcar_dmac_chan(chan);
	rchan->mid_rid = dma_spec->args[0];

	return chan;
}