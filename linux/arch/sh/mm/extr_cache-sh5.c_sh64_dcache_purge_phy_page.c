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
 int CACHE_OC_N_SYNBITS ; 
 scalar_t__ L1_CACHE_BYTES ; 
 unsigned long long MAGIC_PAGE0_START ; 
 unsigned long long PAGE_SIZE ; 
 int /*<<< orphan*/  get_asid () ; 
 int /*<<< orphan*/  sh64_setup_dtlb_cache_slot (unsigned long long,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  sh64_teardown_dtlb_cache_slot () ; 

__attribute__((used)) static void sh64_dcache_purge_phy_page(unsigned long paddr)
{
	unsigned long long eaddr_start, eaddr, eaddr_end;
	int i;

	/* As long as the kernel is not pre-emptible, this doesn't need to be
	   under cli/sti. */
	eaddr_start = MAGIC_PAGE0_START;
	for (i = 0; i < (1 << CACHE_OC_N_SYNBITS); i++) {
		sh64_setup_dtlb_cache_slot(eaddr_start, get_asid(), paddr);

		eaddr = eaddr_start;
		eaddr_end = eaddr + PAGE_SIZE;
		while (eaddr < eaddr_end) {
			__asm__ __volatile__ ("ocbp %0, 0" : : "r" (eaddr));
			eaddr += L1_CACHE_BYTES;
		}

		sh64_teardown_dtlb_cache_slot();
		eaddr_start += PAGE_SIZE;
	}
}