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
typedef  int vm_paddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_PHYSICAL ; 
 int L2_S_PROT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int L2_S_PROTO ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PTE_KERNEL ; 
 int /*<<< orphan*/  PTE_SYNC (int*) ; 
 int /*<<< orphan*/  VM_PROT_WRITE ; 
 scalar_t__ _arm_bzero (void*,int,int /*<<< orphan*/ ) ; 
 int _min_bzero_size ; 
 int /*<<< orphan*/  bzero (void*,int) ; 
 int /*<<< orphan*/  bzero_page (scalar_t__) ; 
 int* cdst_pte ; 
 scalar_t__ cdstp ; 
 int /*<<< orphan*/  cmtx ; 
 int /*<<< orphan*/  cpu_cpwait () ; 
 int /*<<< orphan*/  cpu_tlb_flushD_SE (scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pmap_zero_page_generic(vm_paddr_t phys, int off, int size)
{

	if (_arm_bzero && size >= _min_bzero_size &&
	    _arm_bzero((void *)(phys + off), size, IS_PHYSICAL) == 0)
		return;

	mtx_lock(&cmtx);
	/*
	 * Hook in the page, zero it, invalidate the TLB as needed.
	 *
	 * Note the temporary zero-page mapping must be a non-cached page in
	 * order to work without corruption when write-allocate is enabled.
	 */
	*cdst_pte = L2_S_PROTO | phys | L2_S_PROT(PTE_KERNEL, VM_PROT_WRITE);
	PTE_SYNC(cdst_pte);
	cpu_tlb_flushD_SE(cdstp);
	cpu_cpwait();
	if (off || size != PAGE_SIZE)
		bzero((void *)(cdstp + off), size);
	else
		bzero_page(cdstp);

	mtx_unlock(&cmtx);
}