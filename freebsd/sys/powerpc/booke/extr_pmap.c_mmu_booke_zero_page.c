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

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PHYS_TO_DMAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 scalar_t__ cacheline_size ; 
 int /*<<< orphan*/  mmu_booke_kenter (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_booke_kremove (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zero_page_mutex ; 
 scalar_t__ zero_page_va ; 

__attribute__((used)) static void
mmu_booke_zero_page(mmu_t mmu, vm_page_t m)
{
	vm_offset_t off, va;

#ifdef __powerpc64__
	va = PHYS_TO_DMAP(VM_PAGE_TO_PHYS(m));

	for (off = 0; off < PAGE_SIZE; off += cacheline_size)
		__asm __volatile("dcbz 0,%0" :: "r"(va + off));
#else
	va = zero_page_va;
	mtx_lock(&zero_page_mutex);

	mmu_booke_kenter(mmu, va, VM_PAGE_TO_PHYS(m));

	for (off = 0; off < PAGE_SIZE; off += cacheline_size)
		__asm __volatile("dcbz 0,%0" :: "r"(va + off));

	mmu_booke_kremove(mmu, va);

	mtx_unlock(&zero_page_mutex);
#endif
}