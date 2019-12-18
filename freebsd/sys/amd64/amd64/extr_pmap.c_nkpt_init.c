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
typedef  int /*<<< orphan*/  vm_paddr_t ;

/* Variables and functions */
 scalar_t__ NKPDPE (int) ; 
 int NKPT ; 
 int PDRSHIFT ; 
 int howmany (int /*<<< orphan*/ ,int) ; 
 int nkpt ; 

__attribute__((used)) static void
nkpt_init(vm_paddr_t addr)
{
	int pt_pages;
	
#ifdef NKPT
	pt_pages = NKPT;
#else
	pt_pages = howmany(addr, 1 << PDRSHIFT);
	pt_pages += NKPDPE(pt_pages);

	/*
	 * Add some slop beyond the bare minimum required for bootstrapping
	 * the kernel.
	 *
	 * This is quite important when allocating KVA for kernel modules.
	 * The modules are required to be linked in the negative 2GB of
	 * the address space.  If we run out of KVA in this region then
	 * pmap_growkernel() will need to allocate page table pages to map
	 * the entire 512GB of KVA space which is an unnecessary tax on
	 * physical memory.
	 *
	 * Secondly, device memory mapped as part of setting up the low-
	 * level console(s) is taken from KVA, starting at virtual_avail.
	 * This is because cninit() is called after pmap_bootstrap() but
	 * before vm_init() and pmap_init(). 20MB for a frame buffer is
	 * not uncommon.
	 */
	pt_pages += 32;		/* 64MB additional slop. */
#endif
	nkpt = pt_pages;
}