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
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 scalar_t__ L1_S_SIZE ; 
 int /*<<< orphan*/  cpu_cpwait () ; 
 int /*<<< orphan*/  cpu_dcache_wbinv_all () ; 
 int /*<<< orphan*/  cpu_l2cache_wbinv_all () ; 
 int /*<<< orphan*/  cpu_tlb_flushD () ; 
 int /*<<< orphan*/  kernel_pmap ; 
 scalar_t__ kernel_vm_end ; 
 scalar_t__ pmap_curmaxkvaddr ; 
 int /*<<< orphan*/  pmap_grow_l2_bucket (int /*<<< orphan*/ ,scalar_t__) ; 

void
pmap_growkernel(vm_offset_t addr)
{
	pmap_t kpm = kernel_pmap;

	if (addr <= pmap_curmaxkvaddr)
		return;		/* we are OK */

	/*
	 * whoops!   we need to add kernel PTPs
	 */

	/* Map 1MB at a time */
	for (; pmap_curmaxkvaddr < addr; pmap_curmaxkvaddr += L1_S_SIZE)
		pmap_grow_l2_bucket(kpm, pmap_curmaxkvaddr);

	/*
	 * flush out the cache, expensive but growkernel will happen so
	 * rarely
	 */
	cpu_dcache_wbinv_all();
	cpu_l2cache_wbinv_all();
	cpu_tlb_flushD();
	cpu_cpwait();
	kernel_vm_end = pmap_curmaxkvaddr;
}