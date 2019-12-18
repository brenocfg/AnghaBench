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
 int ST0_ISC ; 
 int ST0_SWC ; 
 void* dcache_lsize ; 
 void* dcache_size ; 
 void* icache_lsize ; 
 void* icache_size ; 
 void* r3k_cache_lsize (int) ; 
 void* r3k_cache_size (int) ; 

__attribute__((used)) static void r3k_probe_cache(void)
{
	dcache_size = r3k_cache_size(ST0_ISC);
	if (dcache_size)
		dcache_lsize = r3k_cache_lsize(ST0_ISC);

	icache_size = r3k_cache_size(ST0_ISC|ST0_SWC);
	if (icache_size)
		icache_lsize = r3k_cache_lsize(ST0_ISC|ST0_SWC);
}