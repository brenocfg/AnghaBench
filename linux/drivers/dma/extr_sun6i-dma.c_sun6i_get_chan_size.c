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
struct sun6i_pchan {scalar_t__ base; struct sun6i_desc* desc; } ;
struct sun6i_dma_lli {scalar_t__ p_lli_next; scalar_t__ len; struct sun6i_dma_lli* v_lli_next; } ;
struct sun6i_desc {struct sun6i_dma_lli* v_lli; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ DMA_CHAN_CUR_CNT ; 
 scalar_t__ DMA_CHAN_LLI_ADDR ; 
 scalar_t__ LLI_LAST_ITEM ; 
 void* readl (scalar_t__) ; 

__attribute__((used)) static size_t sun6i_get_chan_size(struct sun6i_pchan *pchan)
{
	struct sun6i_desc *txd = pchan->desc;
	struct sun6i_dma_lli *lli;
	size_t bytes;
	dma_addr_t pos;

	pos = readl(pchan->base + DMA_CHAN_LLI_ADDR);
	bytes = readl(pchan->base + DMA_CHAN_CUR_CNT);

	if (pos == LLI_LAST_ITEM)
		return bytes;

	for (lli = txd->v_lli; lli; lli = lli->v_lli_next) {
		if (lli->p_lli_next == pos) {
			for (lli = lli->v_lli_next; lli; lli = lli->v_lli_next)
				bytes += lli->len;
			break;
		}
	}

	return bytes;
}