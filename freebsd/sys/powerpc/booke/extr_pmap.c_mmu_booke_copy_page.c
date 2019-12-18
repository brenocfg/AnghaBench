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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  mmu_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ PHYS_TO_DMAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 scalar_t__ copy_page_dst_va ; 
 int /*<<< orphan*/  copy_page_mutex ; 
 scalar_t__ copy_page_src_va ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_booke_kenter (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_booke_kremove (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mmu_booke_copy_page(mmu_t mmu, vm_page_t sm, vm_page_t dm)
{
	vm_offset_t sva, dva;

#ifdef __powerpc64__
	sva = PHYS_TO_DMAP(VM_PAGE_TO_PHYS(sm));
	dva = PHYS_TO_DMAP(VM_PAGE_TO_PHYS(dm));
	memcpy((caddr_t)dva, (caddr_t)sva, PAGE_SIZE);
#else
	sva = copy_page_src_va;
	dva = copy_page_dst_va;

	mtx_lock(&copy_page_mutex);
	mmu_booke_kenter(mmu, sva, VM_PAGE_TO_PHYS(sm));
	mmu_booke_kenter(mmu, dva, VM_PAGE_TO_PHYS(dm));

	memcpy((caddr_t)dva, (caddr_t)sva, PAGE_SIZE);

	mmu_booke_kremove(mmu, dva);
	mmu_booke_kremove(mmu, sva);
	mtx_unlock(&copy_page_mutex);
#endif
}