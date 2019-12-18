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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ phys; } ;
struct iop_adma_desc_slot {int slot_cnt; int slots_per_op; TYPE_1__ async_tx; struct iop3xx_desc_aau* hw_desc; } ;
struct iop3xx_desc_aau {scalar_t__ next_desc; scalar_t__ desc_ctrl; } ;
struct iop3xx_aau_desc_ctrl {int zero_result_en; unsigned long int_en; scalar_t__ dest_write_en; } ;

/* Variables and functions */
 unsigned long DMA_PREP_INTERRUPT ; 
 scalar_t__ iop3xx_desc_init_xor (struct iop3xx_desc_aau*,int,unsigned long) ; 
 struct iop3xx_desc_aau* iop_hw_desc_slot_idx (struct iop3xx_desc_aau*,int) ; 

__attribute__((used)) static inline int
iop_desc_init_zero_sum(struct iop_adma_desc_slot *desc, int src_cnt,
		       unsigned long flags)
{
	int slot_cnt = desc->slot_cnt, slots_per_op = desc->slots_per_op;
	struct iop3xx_desc_aau *hw_desc, *prev_hw_desc, *iter;
	union {
		u32 value;
		struct iop3xx_aau_desc_ctrl field;
	} u_desc_ctrl;
	int i, j;

	hw_desc = desc->hw_desc;

	for (i = 0, j = 0; (slot_cnt -= slots_per_op) >= 0;
		i += slots_per_op, j++) {
		iter = iop_hw_desc_slot_idx(hw_desc, i);
		u_desc_ctrl.value = iop3xx_desc_init_xor(iter, src_cnt, flags);
		u_desc_ctrl.field.dest_write_en = 0;
		u_desc_ctrl.field.zero_result_en = 1;
		u_desc_ctrl.field.int_en = flags & DMA_PREP_INTERRUPT;
		iter->desc_ctrl = u_desc_ctrl.value;

		/* for the subsequent descriptors preserve the store queue
		 * and chain them together
		 */
		if (i) {
			prev_hw_desc =
				iop_hw_desc_slot_idx(hw_desc, i - slots_per_op);
			prev_hw_desc->next_desc =
				(u32) (desc->async_tx.phys + (i << 5));
		}
	}

	return j;
}