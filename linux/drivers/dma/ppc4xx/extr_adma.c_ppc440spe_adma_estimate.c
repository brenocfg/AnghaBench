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
struct page {int dummy; } ;
struct dma_chan {scalar_t__ chan_id; } ;
typedef  enum dma_transaction_type { ____Placeholder_dma_transaction_type } dma_transaction_type ;

/* Variables and functions */
 int DMA_PQ ; 
 int DMA_PQ_VAL ; 
 scalar_t__ PPC440SPE_XOR_ID ; 
 scalar_t__ likely (int) ; 
 scalar_t__ ppc440spe_can_rxor (struct page**,int,size_t) ; 
 int /*<<< orphan*/  ppc440spe_chan_is_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppc440spe_r6_enabled ; 
 int /*<<< orphan*/  to_ppc440spe_adma_chan (struct dma_chan*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ppc440spe_adma_estimate(struct dma_chan *chan,
	enum dma_transaction_type cap, struct page **dst_lst, int dst_cnt,
	struct page **src_lst, int src_cnt, size_t src_sz)
{
	int ef = 1;

	if (cap == DMA_PQ || cap == DMA_PQ_VAL) {
		/* If RAID-6 capabilities were not activated don't try
		 * to use them
		 */
		if (unlikely(!ppc440spe_r6_enabled))
			return -1;
	}
	/*  In the current implementation of ppc440spe ADMA driver it
	 * makes sense to pick out only pq case, because it may be
	 * processed:
	 * (1) either using Biskup method on DMA2;
	 * (2) or on DMA0/1.
	 *  Thus we give a favour to (1) if the sources are suitable;
	 * else let it be processed on one of the DMA0/1 engines.
	 *  In the sum_product case where destination is also the
	 * source process it on DMA0/1 only.
	 */
	if (cap == DMA_PQ && chan->chan_id == PPC440SPE_XOR_ID) {

		if (dst_cnt == 1 && src_cnt == 2 && dst_lst[0] == src_lst[1])
			ef = 0; /* sum_product case, process on DMA0/1 */
		else if (ppc440spe_can_rxor(src_lst, src_cnt, src_sz))
			ef = 3; /* override (DMA0/1 + idle) */
		else
			ef = 0; /* can't process on DMA2 if !rxor */
	}

	/* channel idleness increases the priority */
	if (likely(ef) &&
	    !ppc440spe_chan_is_busy(to_ppc440spe_adma_chan(chan)))
		ef++;

	return ef;
}