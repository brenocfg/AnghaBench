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
 int /*<<< orphan*/  dma_cache_wback (unsigned long,int) ; 
 int /*<<< orphan*/  instruction_hazard () ; 
 int /*<<< orphan*/  local_flush_icache_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  memcpy (void*,char*,int) ; 

__attribute__((used)) static void bmips_wr_vec(unsigned long dst, char *start, char *end)
{
	memcpy((void *)dst, start, end - start);
	dma_cache_wback(dst, end - start);
	local_flush_icache_range(dst, dst + (end - start));
	instruction_hazard();
}