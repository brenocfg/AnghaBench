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
typedef  scalar_t__ vm_offset_t ;

/* Variables and functions */
 int CACHEOP_R4K_INDEX_WB_INV ; 
 int CACHE_R4K_SD ; 
 scalar_t__ MIPS_PHYS_TO_KSEG0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_r4k_op_32lines_32 (scalar_t__,int) ; 
 scalar_t__ sdcache_size ; 

void
mipsNN_sdcache_wbinv_all_32(void)
{
	vm_offset_t va = MIPS_PHYS_TO_KSEG0(0);
	vm_offset_t eva = va + sdcache_size;

	while (va < eva) {
		cache_r4k_op_32lines_32(va,
		    CACHE_R4K_SD|CACHEOP_R4K_INDEX_WB_INV);
		va += (32 * 32);
	}
}