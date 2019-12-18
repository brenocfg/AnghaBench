#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vm_unmapped_area_info {unsigned long length; int align_mask; unsigned long align_offset; int /*<<< orphan*/  high_limit; int /*<<< orphan*/  low_limit; scalar_t__ flags; } ;
struct vm_area_struct {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_legacy_base; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 unsigned long COLOR_ALIGN (unsigned long,int,unsigned long) ; 
 unsigned long EINVAL ; 
 unsigned long ENOMEM ; 
 int GET_LAST_MMAP (struct file*) ; 
 unsigned long MAP_FIXED ; 
 unsigned long MAP_SHARED ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 int PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  SET_LAST_MMAP (struct file*,unsigned long) ; 
 int SHM_COLOUR ; 
 unsigned long TASK_SIZE ; 
 TYPE_1__* current ; 
 struct vm_area_struct* find_vma_prev (struct mm_struct*,unsigned long,struct vm_area_struct**) ; 
 int /*<<< orphan*/  mmap_upper_limit (int /*<<< orphan*/ *) ; 
 unsigned long shared_align_offset (int,unsigned long) ; 
 unsigned long vm_end_gap (struct vm_area_struct*) ; 
 unsigned long vm_start_gap (struct vm_area_struct*) ; 
 unsigned long vm_unmapped_area (struct vm_unmapped_area_info*) ; 

unsigned long arch_get_unmapped_area(struct file *filp, unsigned long addr,
		unsigned long len, unsigned long pgoff, unsigned long flags)
{
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma, *prev;
	unsigned long task_size = TASK_SIZE;
	int do_color_align, last_mmap;
	struct vm_unmapped_area_info info;

	if (len > task_size)
		return -ENOMEM;

	do_color_align = 0;
	if (filp || (flags & MAP_SHARED))
		do_color_align = 1;
	last_mmap = GET_LAST_MMAP(filp);

	if (flags & MAP_FIXED) {
		if ((flags & MAP_SHARED) && last_mmap &&
		    (addr - shared_align_offset(last_mmap, pgoff))
				& (SHM_COLOUR - 1))
			return -EINVAL;
		goto found_addr;
	}

	if (addr) {
		if (do_color_align && last_mmap)
			addr = COLOR_ALIGN(addr, last_mmap, pgoff);
		else
			addr = PAGE_ALIGN(addr);

		vma = find_vma_prev(mm, addr, &prev);
		if (task_size - len >= addr &&
		    (!vma || addr + len <= vm_start_gap(vma)) &&
		    (!prev || addr >= vm_end_gap(prev)))
			goto found_addr;
	}

	info.flags = 0;
	info.length = len;
	info.low_limit = mm->mmap_legacy_base;
	info.high_limit = mmap_upper_limit(NULL);
	info.align_mask = last_mmap ? (PAGE_MASK & (SHM_COLOUR - 1)) : 0;
	info.align_offset = shared_align_offset(last_mmap, pgoff);
	addr = vm_unmapped_area(&info);

found_addr:
	if (do_color_align && !last_mmap && !(addr & ~PAGE_MASK))
		SET_LAST_MMAP(filp, addr - (pgoff << PAGE_SHIFT));

	return addr;
}