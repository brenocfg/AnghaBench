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
typedef  int vm_size_t ;
typedef  int vm_offset_t ;

/* Variables and functions */
 int CACHEOP_R4K_INDEX_INV ; 
 int CACHE_R4K_I ; 
 int MIPS_PHYS_TO_KSEG0 (int) ; 
 int /*<<< orphan*/  cache_op_r4k_line (int,int) ; 
 int /*<<< orphan*/  cache_r4k_op_8lines_16 (int,int) ; 
 int /*<<< orphan*/  mips_intern_dcache_wbinv_range_index (int,int) ; 
 int picache_loopcount ; 
 int picache_stride ; 
 int picache_way_mask ; 
 int round_line16 (int) ; 
 int trunc_line16 (int) ; 

void
mipsNN_icache_sync_range_index_16(vm_offset_t va, vm_size_t size)
{
	vm_offset_t eva, tmpva;
	int i, stride, loopcount;

	/*
	 * Since we're doing Index ops, we expect to not be able
	 * to access the address we've been given.  So, get the
	 * bits that determine the cache index, and make a KSEG0
	 * address out of them.
	 */
	va = MIPS_PHYS_TO_KSEG0(va & picache_way_mask);

	eva = round_line16(va + size);
	va = trunc_line16(va);

	/*
	 * GCC generates better code in the loops if we reference local
	 * copies of these global variables.
	 */
	stride = picache_stride;
	loopcount = picache_loopcount;

	mips_intern_dcache_wbinv_range_index(va, (eva - va));

	while ((eva - va) >= (8 * 16)) {
		tmpva = va;
		for (i = 0; i < loopcount; i++, tmpva += stride)
			cache_r4k_op_8lines_16(tmpva,
			    CACHE_R4K_I|CACHEOP_R4K_INDEX_INV);
		va += 8 * 16;
	}

	while (va < eva) {
		tmpva = va;
		for (i = 0; i < loopcount; i++, tmpva += stride)
			cache_op_r4k_line(tmpva,
			    CACHE_R4K_I|CACHEOP_R4K_INDEX_INV);
		va += 16;
	}
}