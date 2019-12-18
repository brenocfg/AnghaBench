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
struct dma_slave_config {int src_maxburst; int dst_maxburst; void* dst_addr_width; void* src_addr_width; } ;
struct sun4i_dma_vchan {int /*<<< orphan*/  vc; scalar_t__ is_dedicated; struct dma_slave_config cfg; } ;
struct sun4i_dma_promise {int cfg; int /*<<< orphan*/  list; } ;
struct sun4i_dma_contract {int /*<<< orphan*/  vd; int /*<<< orphan*/  demands; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEM_TO_MEM ; 
 void* DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int /*<<< orphan*/  SUN4I_DDMA_DRQ_TYPE_SDRAM ; 
 int SUN4I_DMA_CFG_DST_DRQ_TYPE (int /*<<< orphan*/ ) ; 
 int SUN4I_DMA_CFG_SRC_DRQ_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_NDMA_DRQ_TYPE_SDRAM ; 
 struct sun4i_dma_promise* generate_ddma_promise (struct dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,struct dma_slave_config*) ; 
 struct sun4i_dma_contract* generate_dma_contract () ; 
 struct sun4i_dma_promise* generate_ndma_promise (struct dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,struct dma_slave_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sun4i_dma_contract*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sun4i_dma_vchan* to_sun4i_dma_vchan (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* vchan_tx_prep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *
sun4i_dma_prep_dma_memcpy(struct dma_chan *chan, dma_addr_t dest,
			  dma_addr_t src, size_t len, unsigned long flags)
{
	struct sun4i_dma_vchan *vchan = to_sun4i_dma_vchan(chan);
	struct dma_slave_config *sconfig = &vchan->cfg;
	struct sun4i_dma_promise *promise;
	struct sun4i_dma_contract *contract;

	contract = generate_dma_contract();
	if (!contract)
		return NULL;

	/*
	 * We can only do the copy to bus aligned addresses, so
	 * choose the best one so we get decent performance. We also
	 * maximize the burst size for this same reason.
	 */
	sconfig->src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	sconfig->dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	sconfig->src_maxburst = 8;
	sconfig->dst_maxburst = 8;

	if (vchan->is_dedicated)
		promise = generate_ddma_promise(chan, src, dest, len, sconfig);
	else
		promise = generate_ndma_promise(chan, src, dest, len, sconfig,
						DMA_MEM_TO_MEM);

	if (!promise) {
		kfree(contract);
		return NULL;
	}

	/* Configure memcpy mode */
	if (vchan->is_dedicated) {
		promise->cfg |= SUN4I_DMA_CFG_SRC_DRQ_TYPE(SUN4I_DDMA_DRQ_TYPE_SDRAM) |
				SUN4I_DMA_CFG_DST_DRQ_TYPE(SUN4I_DDMA_DRQ_TYPE_SDRAM);
	} else {
		promise->cfg |= SUN4I_DMA_CFG_SRC_DRQ_TYPE(SUN4I_NDMA_DRQ_TYPE_SDRAM) |
				SUN4I_DMA_CFG_DST_DRQ_TYPE(SUN4I_NDMA_DRQ_TYPE_SDRAM);
	}

	/* Fill the contract with our only promise */
	list_add_tail(&promise->list, &contract->demands);

	/* And add it to the vchan */
	return vchan_tx_prep(&vchan->vc, &contract->vd, flags);
}