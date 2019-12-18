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
typedef  enum slb_index { ____Placeholder_slb_index } slb_index ;
struct TYPE_2__ {unsigned int slb_used_bitmap; unsigned int slb_kern_bitmap; int stab_rr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int SLB_NUM_BOLTED ; 
 unsigned int U32_MAX ; 
 int ffz (unsigned int) ; 
 TYPE_1__* local_paca ; 
 int mmu_slb_size ; 

__attribute__((used)) static enum slb_index alloc_slb_index(bool kernel)
{
	enum slb_index index;

	/*
	 * The allocation bitmaps can become out of synch with the SLB
	 * when the _switch code does slbie when bolting a new stack
	 * segment and it must not be anywhere else in the SLB. This leaves
	 * a kernel allocated entry that is unused in the SLB. With very
	 * large systems or small segment sizes, the bitmaps could slowly
	 * fill with these entries. They will eventually be cleared out
	 * by the round robin allocator in that case, so it's probably not
	 * worth accounting for.
	 */

	/*
	 * SLBs beyond 32 entries are allocated with stab_rr only
	 * POWER7/8/9 have 32 SLB entries, this could be expanded if a
	 * future CPU has more.
	 */
	if (local_paca->slb_used_bitmap != U32_MAX) {
		index = ffz(local_paca->slb_used_bitmap);
		local_paca->slb_used_bitmap |= 1U << index;
		if (kernel)
			local_paca->slb_kern_bitmap |= 1U << index;
	} else {
		/* round-robin replacement of slb starting at SLB_NUM_BOLTED. */
		index = local_paca->stab_rr;
		if (index < (mmu_slb_size - 1))
			index++;
		else
			index = SLB_NUM_BOLTED;
		local_paca->stab_rr = index;
		if (index < 32) {
			if (kernel)
				local_paca->slb_kern_bitmap |= 1U << index;
			else
				local_paca->slb_kern_bitmap &= ~(1U << index);
		}
	}
	BUG_ON(index < SLB_NUM_BOLTED);

	return index;
}