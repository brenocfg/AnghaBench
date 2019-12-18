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
struct ppc440spe_adma_desc_slot {int src_cnt; int dst_cnt; int /*<<< orphan*/  flags; int /*<<< orphan*/ * hw_next; struct dma_cdb* hw_desc; } ;
struct dma_cdb {int /*<<< orphan*/  opc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CDB_OPC_MV_SG1_SG2 ; 
 unsigned long DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  PPC440SPE_DESC_INT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct dma_cdb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ppc440spe_desc_init_memcpy(struct ppc440spe_adma_desc_slot *desc,
					unsigned long flags)
{
	struct dma_cdb *hw_desc = desc->hw_desc;

	memset(desc->hw_desc, 0, sizeof(struct dma_cdb));
	desc->hw_next = NULL;
	desc->src_cnt = 1;
	desc->dst_cnt = 1;

	if (flags & DMA_PREP_INTERRUPT)
		set_bit(PPC440SPE_DESC_INT, &desc->flags);
	else
		clear_bit(PPC440SPE_DESC_INT, &desc->flags);

	hw_desc->opc = DMA_CDB_OPC_MV_SG1_SG2;
}