#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int slb_cache_ptr; unsigned long* slb_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 int SLB_CACHE_ENTRIES ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 TYPE_1__* local_paca ; 

__attribute__((used)) static void slb_cache_update(unsigned long esid_data)
{
	int slb_cache_index;

	if (cpu_has_feature(CPU_FTR_ARCH_300))
		return; /* ISAv3.0B and later does not use slb_cache */

	/*
	 * Now update slb cache entries
	 */
	slb_cache_index = local_paca->slb_cache_ptr;
	if (slb_cache_index < SLB_CACHE_ENTRIES) {
		/*
		 * We have space in slb cache for optimized switch_slb().
		 * Top 36 bits from esid_data as per ISA
		 */
		local_paca->slb_cache[slb_cache_index++] = esid_data >> 28;
		local_paca->slb_cache_ptr++;
	} else {
		/*
		 * Our cache is full and the current cache content strictly
		 * doesn't indicate the active SLB conents. Bump the ptr
		 * so that switch_slb() will ignore the cache.
		 */
		local_paca->slb_cache_ptr = SLB_CACHE_ENTRIES + 1;
	}
}