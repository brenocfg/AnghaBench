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
typedef  int uint32_t ;
struct jz4780_dma_desc {int /*<<< orphan*/  vdesc; TYPE_1__* desc; } ;
struct jz4780_dma_chan {size_t transfer_shift; int /*<<< orphan*/  vchan; int /*<<< orphan*/  transfer_type; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  size_t dma_addr_t ;
struct TYPE_2__ {size_t dsa; size_t dta; int dcm; size_t dtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEMCPY ; 
 int JZ_DMA_DCM_DAI ; 
 int JZ_DMA_DCM_DP_SHIFT ; 
 int JZ_DMA_DCM_SAI ; 
 int JZ_DMA_DCM_SP_SHIFT ; 
 int JZ_DMA_DCM_TIE ; 
 int JZ_DMA_DCM_TSZ_SHIFT ; 
 int /*<<< orphan*/  JZ_DMA_DRT_AUTO ; 
 int JZ_DMA_WIDTH_32_BIT ; 
 struct jz4780_dma_desc* jz4780_dma_desc_alloc (struct jz4780_dma_chan*,int,int /*<<< orphan*/ ) ; 
 int jz4780_dma_transfer_size (struct jz4780_dma_chan*,size_t,size_t*) ; 
 struct jz4780_dma_chan* to_jz4780_dma_chan (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* vchan_tx_prep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *jz4780_dma_prep_dma_memcpy(
	struct dma_chan *chan, dma_addr_t dest, dma_addr_t src,
	size_t len, unsigned long flags)
{
	struct jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);
	struct jz4780_dma_desc *desc;
	uint32_t tsz;

	desc = jz4780_dma_desc_alloc(jzchan, 1, DMA_MEMCPY);
	if (!desc)
		return NULL;

	tsz = jz4780_dma_transfer_size(jzchan, dest | src | len,
				       &jzchan->transfer_shift);

	jzchan->transfer_type = JZ_DMA_DRT_AUTO;

	desc->desc[0].dsa = src;
	desc->desc[0].dta = dest;
	desc->desc[0].dcm = JZ_DMA_DCM_TIE | JZ_DMA_DCM_SAI | JZ_DMA_DCM_DAI |
			    tsz << JZ_DMA_DCM_TSZ_SHIFT |
			    JZ_DMA_WIDTH_32_BIT << JZ_DMA_DCM_SP_SHIFT |
			    JZ_DMA_WIDTH_32_BIT << JZ_DMA_DCM_DP_SHIFT;
	desc->desc[0].dtc = len >> jzchan->transfer_shift;

	return vchan_tx_prep(&jzchan->vchan, &desc->vdesc, flags);
}