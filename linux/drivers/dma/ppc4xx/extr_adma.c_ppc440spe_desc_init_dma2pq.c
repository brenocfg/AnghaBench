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
struct xor_cb {int /*<<< orphan*/  cbc; } ;
struct ppc440spe_adma_desc_slot {int src_cnt; int dst_cnt; scalar_t__ descs_per_op; struct xor_cb* reverse_flags; int /*<<< orphan*/ * hw_next; struct xor_cb* hw_desc; } ;

/* Variables and functions */
 unsigned long DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  XOR_CBCR_CBCE_BIT ; 
 int /*<<< orphan*/  XOR_CBCR_TGT_BIT ; 
 int /*<<< orphan*/  memset (struct xor_cb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ppc440spe_desc_init_dma2pq(struct ppc440spe_adma_desc_slot *desc,
		int dst_cnt, int src_cnt, unsigned long flags)
{
	struct xor_cb *hw_desc = desc->hw_desc;

	memset(desc->hw_desc, 0, sizeof(struct xor_cb));
	desc->hw_next = NULL;
	desc->src_cnt = src_cnt;
	desc->dst_cnt = dst_cnt;
	memset(desc->reverse_flags, 0, sizeof(desc->reverse_flags));
	desc->descs_per_op = 0;

	hw_desc->cbc = XOR_CBCR_TGT_BIT;
	if (flags & DMA_PREP_INTERRUPT)
		/* Enable interrupt on completion */
		hw_desc->cbc |= XOR_CBCR_CBCE_BIT;
}