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
 int /*<<< orphan*/  SPRN_TLB1CFG ; 
 int TLBnCFG_N_ENTRY ; 
 int /*<<< orphan*/  __this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_tlbcam_idx ; 
 int this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlbcam_index ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int tlb1_next(void)
{
	int index, ncams;

	ncams = mfspr(SPRN_TLB1CFG) & TLBnCFG_N_ENTRY;

	index = this_cpu_read(next_tlbcam_idx);

	/* Just round-robin the entries and wrap when we hit the end */
	if (unlikely(index == ncams - 1))
		__this_cpu_write(next_tlbcam_idx, tlbcam_index);
	else
		__this_cpu_inc(next_tlbcam_idx);

	return index;
}