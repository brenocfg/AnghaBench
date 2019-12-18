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
 int /*<<< orphan*/  blast_inv_dcache_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  iob () ; 

__attribute__((used)) static void tx39h_dma_cache_wback_inv(unsigned long addr, unsigned long size)
{
	/* Catch bad driver code */
	BUG_ON(size == 0);

	iob();
	blast_inv_dcache_range(addr, addr + size);
}