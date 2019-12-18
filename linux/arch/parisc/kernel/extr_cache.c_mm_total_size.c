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
struct vm_area_struct {scalar_t__ vm_start; scalar_t__ vm_end; struct vm_area_struct* vm_next; } ;
struct mm_struct {struct vm_area_struct* mmap; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long mm_total_size(struct mm_struct *mm)
{
	struct vm_area_struct *vma;
	unsigned long usize = 0;

	for (vma = mm->mmap; vma; vma = vma->vm_next)
		usize += vma->vm_end - vma->vm_start;
	return usize;
}