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
 int L1_CACHE_BYTES ; 
 int /*<<< orphan*/  sync_is () ; 

void dma_wb_range(unsigned long start, unsigned long end)
{
	unsigned long i = start & ~(L1_CACHE_BYTES - 1);

	for (; i < end; i += L1_CACHE_BYTES)
		asm volatile("dcache.cva %0\n"::"r"(i):"memory");
	sync_is();
}