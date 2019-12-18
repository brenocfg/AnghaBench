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
typedef  int u64 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ CNTCV_HI ; 
 scalar_t__ CNTCV_LO ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 
 scalar_t__ sys_ctr_base ; 

__attribute__((used)) static inline u64 sysctr_read_counter(void)
{
	u32 cnt_hi, tmp_hi, cnt_lo;

	do {
		cnt_hi = readl_relaxed(sys_ctr_base + CNTCV_HI);
		cnt_lo = readl_relaxed(sys_ctr_base + CNTCV_LO);
		tmp_hi = readl_relaxed(sys_ctr_base + CNTCV_HI);
	} while (tmp_hi != cnt_hi);

	return  ((u64) cnt_hi << 32) | cnt_lo;
}