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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  __radix__flush_tlb_range (int /*<<< orphan*/ ,unsigned long,unsigned long,int) ; 
 scalar_t__ is_vm_hugetlb_page (struct vm_area_struct*) ; 
 void radix__flush_hugetlb_tlb_range (struct vm_area_struct*,unsigned long,unsigned long) ; 

void radix__flush_tlb_range(struct vm_area_struct *vma, unsigned long start,
		     unsigned long end)

{
#ifdef CONFIG_HUGETLB_PAGE
	if (is_vm_hugetlb_page(vma))
		return radix__flush_hugetlb_tlb_range(vma, start, end);
#endif

	__radix__flush_tlb_range(vma->vm_mm, start, end, false);
}