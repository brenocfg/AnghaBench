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
 scalar_t__ is_vm_hugetlb_page (struct vm_area_struct*) ; 
 int /*<<< orphan*/  mmu_virtual_psize ; 
 void radix__local_flush_hugetlb_page (struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  radix__local_flush_tlb_page_psize (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

void radix__local_flush_tlb_page(struct vm_area_struct *vma, unsigned long vmaddr)
{
#ifdef CONFIG_HUGETLB_PAGE
	/* need the return fix for nohash.c */
	if (is_vm_hugetlb_page(vma))
		return radix__local_flush_hugetlb_page(vma, vmaddr);
#endif
	radix__local_flush_tlb_page_psize(vma->vm_mm, vmaddr, mmu_virtual_psize);
}