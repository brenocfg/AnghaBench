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
struct vm_area_struct {int /*<<< orphan*/  vm_start; int /*<<< orphan*/  vm_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PPC_MM_SLICES ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned int get_slice_psize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long mmu_psize_to_shift (unsigned int) ; 
 int /*<<< orphan*/  radix_enabled () ; 
 unsigned long vma_kernel_pagesize (struct vm_area_struct*) ; 

unsigned long vma_mmu_pagesize(struct vm_area_struct *vma)
{
	/* With radix we don't use slice, so derive it from vma*/
	if (IS_ENABLED(CONFIG_PPC_MM_SLICES) && !radix_enabled()) {
		unsigned int psize = get_slice_psize(vma->vm_mm, vma->vm_start);

		return 1UL << mmu_psize_to_shift(psize);
	}
	return vma_kernel_pagesize(vma);
}