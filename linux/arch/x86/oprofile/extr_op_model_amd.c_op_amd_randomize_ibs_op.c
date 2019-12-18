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
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int IBS_CAPS_RDWROPCNT ; 
 unsigned int IBS_RANDOM_MASK ; 
 int ibs_caps ; 
 unsigned int lfsr_random () ; 

__attribute__((used)) static inline u64 op_amd_randomize_ibs_op(u64 val)
{
	unsigned int random = lfsr_random();

	if (!(ibs_caps & IBS_CAPS_RDWROPCNT))
		/*
		 * Work around if the hw can not write to IbsOpCurCnt
		 *
		 * Randomize the lower 8 bits of the 16 bit
		 * IbsOpMaxCnt [15:0] value in the range of -128 to
		 * +127 by adding/subtracting an offset to the
		 * maximum count (IbsOpMaxCnt).
		 *
		 * To avoid over or underflows and protect upper bits
		 * starting at bit 16, the initial value for
		 * IbsOpMaxCnt must fit in the range from 0x0081 to
		 * 0xff80.
		 */
		val += (s8)(random >> 4);
	else
		val |= (u64)(random & IBS_RANDOM_MASK) << 32;

	return val;
}