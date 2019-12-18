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
 int CACHEOP_R4K_INDEX_INV ; 
 int CACHE_R4K_I ; 
 scalar_t__ MIPS_PHYS_TO_KSEG0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYNC ; 
 int /*<<< orphan*/  cache_r4k_op_32lines_16 (scalar_t__,int) ; 
 int /*<<< orphan*/  mips_intern_dcache_wbinv_all () ; 
 scalar_t__ picache_size ; 

void
mipsNN_icache_sync_all_16(void)
{
	vm_offset_t va, eva;

	va = MIPS_PHYS_TO_KSEG0(0);
	eva = va + picache_size;

	/*
	 * Since we're hitting the whole thing, we don't have to
	 * worry about the N different "ways".
	 */

	mips_intern_dcache_wbinv_all();

	while (va < eva) {
		cache_r4k_op_32lines_16(va, CACHE_R4K_I|CACHEOP_R4K_INDEX_INV);
		va += (32 * 16);
	}

	SYNC;
}