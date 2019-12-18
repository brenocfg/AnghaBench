#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  chan; } ;
struct ppc440spe_adma_desc_slot {int dst_cnt; int descs_per_op; struct ppc440spe_adma_desc_slot* group_head; int /*<<< orphan*/  flags; TYPE_1__ async_tx; } ;
struct ppc440spe_adma_chan {TYPE_2__* device; } ;
typedef  int dma_addr_t ;
struct TYPE_4__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int DMA_CUED_REGION_OFF ; 
 int DMA_CUED_XOR_BASE ; 
 int DMA_CUED_XOR_HB ; 
 int DMA_RXOR12 ; 
 int DMA_RXOR123 ; 
 int DMA_RXOR124 ; 
 int DMA_RXOR125 ; 
 int /*<<< orphan*/  PPC440SPE_DESC_RXOR ; 
 int /*<<< orphan*/  PPC440SPE_DESC_RXOR12 ; 
 int /*<<< orphan*/  PPC440SPE_DESC_RXOR123 ; 
 int /*<<< orphan*/  PPC440SPE_DESC_RXOR124 ; 
 int /*<<< orphan*/  PPC440SPE_DESC_RXOR125 ; 
#define  PPC440SPE_DMA0_ID 130 
#define  PPC440SPE_DMA1_ID 129 
#define  PPC440SPE_XOR_ID 128 
 int /*<<< orphan*/  PPC440SPE_ZERO_P ; 
 int /*<<< orphan*/  PPC440SPE_ZERO_Q ; 
 int /*<<< orphan*/  likely (struct ppc440spe_adma_desc_slot*) ; 
 int /*<<< orphan*/  ppc440spe_adma_dma2rxor_set_src (struct ppc440spe_adma_desc_slot*,int,int) ; 
 int /*<<< orphan*/  ppc440spe_desc_set_src_addr (struct ppc440spe_adma_desc_slot*,struct ppc440spe_adma_chan*,int /*<<< orphan*/ ,int,int) ; 
 struct ppc440spe_adma_desc_slot* ppc440spe_get_group_entry (struct ppc440spe_adma_desc_slot*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ppc440spe_adma_chan* to_ppc440spe_adma_chan (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ppc440spe_adma_pq_set_src(struct ppc440spe_adma_desc_slot *sw_desc,
		dma_addr_t addr, int index)
{
	struct ppc440spe_adma_chan *chan;
	dma_addr_t haddr = 0;
	struct ppc440spe_adma_desc_slot *iter = NULL;

	chan = to_ppc440spe_adma_chan(sw_desc->async_tx.chan);

	switch (chan->device->id) {
	case PPC440SPE_DMA0_ID:
	case PPC440SPE_DMA1_ID:
		/* DMA0,1 may do: WXOR, RXOR, RXOR+WXORs chain
		 */
		if (test_bit(PPC440SPE_DESC_RXOR, &sw_desc->flags)) {
			/* RXOR-only or RXOR/WXOR operation */
			int iskip = test_bit(PPC440SPE_DESC_RXOR12,
				&sw_desc->flags) ?  2 : 3;

			if (index == 0) {
				/* 1st slot (RXOR) */
				/* setup sources region (R1-2-3, R1-2-4,
				 * or R1-2-5)
				 */
				if (test_bit(PPC440SPE_DESC_RXOR12,
						&sw_desc->flags))
					haddr = DMA_RXOR12 <<
						DMA_CUED_REGION_OFF;
				else if (test_bit(PPC440SPE_DESC_RXOR123,
				    &sw_desc->flags))
					haddr = DMA_RXOR123 <<
						DMA_CUED_REGION_OFF;
				else if (test_bit(PPC440SPE_DESC_RXOR124,
				    &sw_desc->flags))
					haddr = DMA_RXOR124 <<
						DMA_CUED_REGION_OFF;
				else if (test_bit(PPC440SPE_DESC_RXOR125,
				    &sw_desc->flags))
					haddr = DMA_RXOR125 <<
						DMA_CUED_REGION_OFF;
				else
					BUG();
				haddr |= DMA_CUED_XOR_BASE;
				iter = ppc440spe_get_group_entry(sw_desc, 0);
			} else if (index < iskip) {
				/* 1st slot (RXOR)
				 * shall actually set source address only once
				 * instead of first <iskip>
				 */
				iter = NULL;
			} else {
				/* 2nd/3d and next slots (WXOR);
				 * skip first slot with RXOR
				 */
				haddr = DMA_CUED_XOR_HB;
				iter = ppc440spe_get_group_entry(sw_desc,
				    index - iskip + sw_desc->dst_cnt);
			}
		} else {
			int znum = 0;

			/* WXOR-only operation; skip first slots with
			 * zeroing destinations
			 */
			if (test_bit(PPC440SPE_ZERO_P, &sw_desc->flags))
				znum++;
			if (test_bit(PPC440SPE_ZERO_Q, &sw_desc->flags))
				znum++;

			haddr = DMA_CUED_XOR_HB;
			iter = ppc440spe_get_group_entry(sw_desc,
					index + znum);
		}

		if (likely(iter)) {
			ppc440spe_desc_set_src_addr(iter, chan, 0, haddr, addr);

			if (!index &&
			    test_bit(PPC440SPE_DESC_RXOR, &sw_desc->flags) &&
			    sw_desc->dst_cnt == 2) {
				/* if we have two destinations for RXOR, then
				 * setup source in the second descr too
				 */
				iter = ppc440spe_get_group_entry(sw_desc, 1);
				ppc440spe_desc_set_src_addr(iter, chan, 0,
					haddr, addr);
			}
		}
		break;

	case PPC440SPE_XOR_ID:
		/* DMA2 may do Biskup */
		iter = sw_desc->group_head;
		if (iter->dst_cnt == 2) {
			/* both P & Q calculations required; set P src here */
			ppc440spe_adma_dma2rxor_set_src(iter, index, addr);

			/* this is for Q */
			iter = ppc440spe_get_group_entry(sw_desc,
				sw_desc->descs_per_op);
		}
		ppc440spe_adma_dma2rxor_set_src(iter, index, addr);
		break;
	}
}