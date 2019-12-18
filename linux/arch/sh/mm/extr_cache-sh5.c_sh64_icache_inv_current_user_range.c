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
 unsigned long long L1_CACHE_ALIGN (unsigned long) ; 
 scalar_t__ L1_CACHE_BYTES ; 

__attribute__((used)) static void sh64_icache_inv_current_user_range(unsigned long start, unsigned long end)
{
	/* The icbi instruction never raises ITLBMISS.  i.e. if there's not a
	   cache hit on the virtual tag the instruction ends there, without a
	   TLB lookup. */

	unsigned long long aligned_start;
	unsigned long long ull_end;
	unsigned long long addr;

	ull_end = end;

	/* Just invalidate over the range using the natural addresses.  TLB
	   miss handling will be OK (TBC).  Since it's for the current process,
	   either we're already in the right ASID context, or the ASIDs have
	   been recycled since we were last active in which case we might just
	   invalidate another processes I-cache entries : no worries, just a
	   performance drop for him. */
	aligned_start = L1_CACHE_ALIGN(start);
	addr = aligned_start;
	while (addr < ull_end) {
		__asm__ __volatile__ ("icbi %0, 0" : : "r" (addr));
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");
		addr += L1_CACHE_BYTES;
	}
}