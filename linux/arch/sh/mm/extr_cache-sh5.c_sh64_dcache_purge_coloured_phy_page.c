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
 unsigned long CACHE_OC_SYN_MASK ; 
 scalar_t__ L1_CACHE_BYTES ; 
 unsigned long MAGIC_PAGE0_START ; 
 unsigned long long PAGE_SIZE ; 
 int /*<<< orphan*/  get_asid () ; 
 int /*<<< orphan*/  sh64_setup_dtlb_cache_slot (unsigned long long,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  sh64_teardown_dtlb_cache_slot () ; 

__attribute__((used)) static void sh64_dcache_purge_coloured_phy_page(unsigned long paddr,
					        unsigned long eaddr)
{
	unsigned long long magic_page_start;
	unsigned long long magic_eaddr, magic_eaddr_end;

	magic_page_start = MAGIC_PAGE0_START + (eaddr & CACHE_OC_SYN_MASK);

	/* As long as the kernel is not pre-emptible, this doesn't need to be
	   under cli/sti. */
	sh64_setup_dtlb_cache_slot(magic_page_start, get_asid(), paddr);

	magic_eaddr = magic_page_start;
	magic_eaddr_end = magic_eaddr + PAGE_SIZE;

	while (magic_eaddr < magic_eaddr_end) {
		/* Little point in unrolling this loop - the OCBPs are blocking
		   and won't go any quicker (i.e. the loop overhead is parallel
		   to part of the OCBP execution.) */
		__asm__ __volatile__ ("ocbp %0, 0" : : "r" (magic_eaddr));
		magic_eaddr += L1_CACHE_BYTES;
	}

	sh64_teardown_dtlb_cache_slot();
}