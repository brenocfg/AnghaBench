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
 int /*<<< orphan*/  flush_dcache_range (unsigned long,unsigned long) ; 

__attribute__((used)) static void dart_cache_sync(unsigned int *base, unsigned int count)
{
	/*
	 * We add 1 to the number of entries to flush, following a
	 * comment in Darwin indicating that the memory controller
	 * can prefetch unmapped memory under some circumstances.
	 */
	unsigned long start = (unsigned long)base;
	unsigned long end = start + (count + 1) * sizeof(unsigned int);
	unsigned int tmp;

	/* Perform a standard cache flush */
	flush_dcache_range(start, end);

	/*
	 * Perform the sequence described in the CPC925 manual to
	 * ensure all the data gets to a point the cache incoherent
	 * DART hardware will see.
	 */
	asm volatile(" sync;"
		     " isync;"
		     " dcbf 0,%1;"
		     " sync;"
		     " isync;"
		     " lwz %0,0(%1);"
		     " isync" : "=r" (tmp) : "r" (end) : "memory");
}