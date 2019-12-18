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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ PHYS_TO_DMAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (void*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ hw_direct_map ; 
 int /*<<< orphan*/  moea64_scratchpage_mtx ; 
 scalar_t__* moea64_scratchpage_va ; 
 int /*<<< orphan*/  moea64_set_scratchpage_pa (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
moea64_copy_page(mmu_t mmu, vm_page_t msrc, vm_page_t mdst)
{
	vm_offset_t	dst;
	vm_offset_t	src;

	dst = VM_PAGE_TO_PHYS(mdst);
	src = VM_PAGE_TO_PHYS(msrc);

	if (hw_direct_map) {
		bcopy((void *)PHYS_TO_DMAP(src), (void *)PHYS_TO_DMAP(dst),
		    PAGE_SIZE);
	} else {
		mtx_lock(&moea64_scratchpage_mtx);

		moea64_set_scratchpage_pa(mmu, 0, src);
		moea64_set_scratchpage_pa(mmu, 1, dst);

		bcopy((void *)moea64_scratchpage_va[0], 
		    (void *)moea64_scratchpage_va[1], PAGE_SIZE);

		mtx_unlock(&moea64_scratchpage_mtx);
	}
}