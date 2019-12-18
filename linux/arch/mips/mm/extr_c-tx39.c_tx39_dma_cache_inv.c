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
 int PAGE_SIZE ; 
 int /*<<< orphan*/  blast_inv_dcache_range (unsigned long,unsigned long) ; 
 unsigned long dcache_size ; 
 int /*<<< orphan*/  tx39_blast_dcache () ; 
 int /*<<< orphan*/  tx39_blast_dcache_page (unsigned long) ; 

__attribute__((used)) static void tx39_dma_cache_inv(unsigned long addr, unsigned long size)
{
	unsigned long end;

	if (((size | addr) & (PAGE_SIZE - 1)) == 0) {
		end = addr + size;
		do {
			tx39_blast_dcache_page(addr);
			addr += PAGE_SIZE;
		} while(addr != end);
	} else if (size > dcache_size) {
		tx39_blast_dcache();
	} else {
		blast_inv_dcache_range(addr, addr + size);
	}
}