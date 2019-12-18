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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  blast_inv_scache_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  invalidate_tcache_page (unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  rm7k_tcache_init ; 
 int tc_pagesize ; 

__attribute__((used)) static void rm7k_sc_inv(unsigned long addr, unsigned long size)
{
	unsigned long end, a;

	pr_debug("rm7k_sc_inv[%08lx,%08lx]", addr, size);

	/* Catch bad driver code */
	BUG_ON(size == 0);

	blast_inv_scache_range(addr, addr + size);

	if (!rm7k_tcache_init)
		return;

	a = addr & ~(tc_pagesize - 1);
	end = (addr + size - 1) & ~(tc_pagesize - 1);
	while(1) {
		invalidate_tcache_page(a);	/* Page_Invalidate_T */
		if (a == end)
			break;
		a += tc_pagesize;
	}
}