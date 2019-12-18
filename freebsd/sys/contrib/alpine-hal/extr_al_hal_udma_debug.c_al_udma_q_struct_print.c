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
typedef  size_t uintmax_t ;
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
struct al_udma_q {size_t q_regs; size_t desc_base_ptr; size_t cdesc_base_ptr; size_t end_cdesc_ptr; size_t comp_head_ptr; size_t udma; scalar_t__ qid; scalar_t__ status; scalar_t__ size; scalar_t__ flags; scalar_t__ cdesc_phy_base; scalar_t__ desc_phy_base; scalar_t__ comp_ring_id; scalar_t__ pkt_crnt_descs; scalar_t__ comp_head_idx; scalar_t__ next_cdesc_idx; scalar_t__ cdesc_size; scalar_t__ desc_ring_id; scalar_t__ next_desc_idx; scalar_t__ size_mask; } ;
struct al_udma {struct al_udma_q* udma_q; } ;

/* Variables and functions */
 size_t DMA_MAX_Q ; 
 int /*<<< orphan*/  al_dbg (char*,size_t) ; 

void al_udma_q_struct_print(struct al_udma *udma, uint32_t qid)
{
	struct al_udma_q *queue;

	if (!udma)
		return;

	if (qid >= DMA_MAX_Q)
		return;

	queue = &udma->udma_q[qid];

	al_dbg("Q[%d] struct:\n", qid);
	al_dbg(" size_mask = 0x%08x\n", (uint32_t)queue->size_mask);
	al_dbg(" q_regs = %p\n", queue->q_regs);
	al_dbg(" desc_base_ptr = %p\n", queue->desc_base_ptr);
	al_dbg(" next_desc_idx = %d\n", (uint16_t)queue->next_desc_idx);
	al_dbg(" desc_ring_id = %d\n", (uint32_t)queue->desc_ring_id);
	al_dbg(" cdesc_base_ptr = %p\n", queue->cdesc_base_ptr);
	al_dbg(" cdesc_size = %d\n", (uint32_t)queue->cdesc_size);
	al_dbg(" next_cdesc_idx = %d\n", (uint16_t)queue->next_cdesc_idx);
	al_dbg(" end_cdesc_ptr = %p\n", queue->end_cdesc_ptr);
	al_dbg(" comp_head_idx = %d\n", (uint16_t)queue->comp_head_idx);
	al_dbg(" comp_head_ptr = %p\n", queue->comp_head_ptr);
	al_dbg(" pkt_crnt_descs = %d\n", (uint32_t)queue->pkt_crnt_descs);
	al_dbg(" comp_ring_id = %d\n", (uint32_t)queue->comp_ring_id);
	al_dbg(" desc_phy_base = 0x%016jx\n", (uintmax_t)queue->desc_phy_base);
	al_dbg(" cdesc_phy_base = 0x%016jx\n",
			(uintmax_t)queue->cdesc_phy_base);
	al_dbg(" flags = 0x%08x\n", (uint32_t)queue->flags);
	al_dbg(" size = %d\n", (uint32_t)queue->size);
	al_dbg(" status = %d\n", (uint32_t)queue->status);
	al_dbg(" udma = %p\n", queue->udma);
	al_dbg(" qid = %d\n", (uint32_t)queue->qid);
}