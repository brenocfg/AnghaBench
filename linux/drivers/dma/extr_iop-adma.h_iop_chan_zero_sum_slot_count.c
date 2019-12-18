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

/* Variables and functions */
 size_t IOP_ADMA_ZERO_SUM_MAX_BYTE_COUNT ; 
 int iop3xx_aau_xor_slot_count (size_t,int,int*) ; 

__attribute__((used)) static inline int iop_chan_zero_sum_slot_count(size_t len, int src_cnt,
						int *slots_per_op)
{
	int slot_cnt = iop3xx_aau_xor_slot_count(len, src_cnt, slots_per_op);

	if (len <= IOP_ADMA_ZERO_SUM_MAX_BYTE_COUNT)
		return slot_cnt;

	len -= IOP_ADMA_ZERO_SUM_MAX_BYTE_COUNT;
	while (len > IOP_ADMA_ZERO_SUM_MAX_BYTE_COUNT) {
		len -= IOP_ADMA_ZERO_SUM_MAX_BYTE_COUNT;
		slot_cnt += *slots_per_op;
	}

	slot_cnt += *slots_per_op;

	return slot_cnt;
}