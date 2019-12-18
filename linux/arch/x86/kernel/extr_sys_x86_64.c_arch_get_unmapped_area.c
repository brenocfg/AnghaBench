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
struct vm_unmapped_area_info {unsigned long length; unsigned long low_limit; unsigned long high_limit; unsigned long align_offset; scalar_t__ align_mask; scalar_t__ flags; } ;
struct vm_area_struct {int dummy; } ;
struct mm_struct {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 unsigned long ENOMEM ; 
 scalar_t__ IS_ERR_VALUE (unsigned long) ; 
 unsigned long MAP_FIXED ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_SHIFT ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  find_start_end (unsigned long,unsigned long,unsigned long*,unsigned long*) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 scalar_t__ get_align_bits () ; 
 scalar_t__ get_align_mask () ; 
 unsigned long mpx_unmapped_area_check (unsigned long,unsigned long,unsigned long) ; 
 unsigned long vm_start_gap (struct vm_area_struct*) ; 
 unsigned long vm_unmapped_area (struct vm_unmapped_area_info*) ; 

unsigned long
arch_get_unmapped_area(struct file *filp, unsigned long addr,
		unsigned long len, unsigned long pgoff, unsigned long flags)
{
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma;
	struct vm_unmapped_area_info info;
	unsigned long begin, end;

	addr = mpx_unmapped_area_check(addr, len, flags);
	if (IS_ERR_VALUE(addr))
		return addr;

	if (flags & MAP_FIXED)
		return addr;

	find_start_end(addr, flags, &begin, &end);

	if (len > end)
		return -ENOMEM;

	if (addr) {
		addr = PAGE_ALIGN(addr);
		vma = find_vma(mm, addr);
		if (end - len >= addr &&
		    (!vma || addr + len <= vm_start_gap(vma)))
			return addr;
	}

	info.flags = 0;
	info.length = len;
	info.low_limit = begin;
	info.high_limit = end;
	info.align_mask = 0;
	info.align_offset = pgoff << PAGE_SHIFT;
	if (filp) {
		info.align_mask = get_align_mask();
		info.align_offset += get_align_bits();
	}
	return vm_unmapped_area(&info);
}