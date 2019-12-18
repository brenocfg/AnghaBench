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
struct iop_adma_desc_slot {int slot_cnt; int slots_per_op; struct iop3xx_desc_aau* hw_desc; } ;
struct iop3xx_desc_aau {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ IOP_ADMA_XOR_MAX_BYTE_COUNT ; 
 int /*<<< orphan*/  iop3xx_aau_desc_set_src_addr (struct iop3xx_desc_aau*,int,int /*<<< orphan*/ ) ; 
 struct iop3xx_desc_aau* iop_hw_desc_slot_idx (struct iop3xx_desc_aau*,int) ; 

__attribute__((used)) static inline void iop_desc_set_xor_src_addr(struct iop_adma_desc_slot *desc,
					int src_idx, dma_addr_t addr)
{

	struct iop3xx_desc_aau *hw_desc = desc->hw_desc, *iter;
	int slot_cnt = desc->slot_cnt, slots_per_op = desc->slots_per_op;
	int i;

	for (i = 0; (slot_cnt -= slots_per_op) >= 0;
		i += slots_per_op, addr += IOP_ADMA_XOR_MAX_BYTE_COUNT) {
		iter = iop_hw_desc_slot_idx(hw_desc, i);
		iop3xx_aau_desc_set_src_addr(iter, src_idx, addr);
	}
}