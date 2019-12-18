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
typedef  scalar_t__ u32 ;
struct iop_adma_desc_slot {int slots_per_op; struct iop3xx_desc_aau* hw_desc; } ;
struct iop3xx_desc_aau {scalar_t__ byte_count; } ;

/* Variables and functions */
 scalar_t__ IOP_ADMA_ZERO_SUM_MAX_BYTE_COUNT ; 
 struct iop3xx_desc_aau* iop_hw_desc_slot_idx (struct iop3xx_desc_aau*,int) ; 

__attribute__((used)) static inline void
iop_desc_set_zero_sum_byte_count(struct iop_adma_desc_slot *desc, u32 len)
{
	int slots_per_op = desc->slots_per_op;
	struct iop3xx_desc_aau *hw_desc = desc->hw_desc, *iter;
	int i = 0;

	if (len <= IOP_ADMA_ZERO_SUM_MAX_BYTE_COUNT) {
		hw_desc->byte_count = len;
	} else {
		do {
			iter = iop_hw_desc_slot_idx(hw_desc, i);
			iter->byte_count = IOP_ADMA_ZERO_SUM_MAX_BYTE_COUNT;
			len -= IOP_ADMA_ZERO_SUM_MAX_BYTE_COUNT;
			i += slots_per_op;
		} while (len > IOP_ADMA_ZERO_SUM_MAX_BYTE_COUNT);

		iter = iop_hw_desc_slot_idx(hw_desc, i);
		iter->byte_count = len;
	}
}