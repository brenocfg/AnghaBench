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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; int /*<<< orphan*/  vm_flags; struct vm_area_struct* vm_next; } ;
struct mm_struct {int /*<<< orphan*/  def_flags; struct vm_area_struct* mmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  FOLL_SPLIT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  VM_HUGEPAGE ; 
 int /*<<< orphan*/  VM_NOHUGEPAGE ; 
 int /*<<< orphan*/  follow_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void thp_split_mm(struct mm_struct *mm)
{
#ifdef CONFIG_TRANSPARENT_HUGEPAGE
	struct vm_area_struct *vma;
	unsigned long addr;

	for (vma = mm->mmap; vma != NULL; vma = vma->vm_next) {
		for (addr = vma->vm_start;
		     addr < vma->vm_end;
		     addr += PAGE_SIZE)
			follow_page(vma, addr, FOLL_SPLIT);
		vma->vm_flags &= ~VM_HUGEPAGE;
		vma->vm_flags |= VM_NOHUGEPAGE;
	}
	mm->def_flags |= VM_NOHUGEPAGE;
#endif
}