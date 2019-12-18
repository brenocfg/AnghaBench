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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; int /*<<< orphan*/  vm_file; } ;
struct hstate {int dummy; } ;

/* Variables and functions */
 struct hstate* hstate_file (int /*<<< orphan*/ ) ; 
 int hstate_get_psize (struct hstate*) ; 
 int /*<<< orphan*/  radix__flush_tlb_range_psize (int /*<<< orphan*/ ,unsigned long,unsigned long,int) ; 

void radix__flush_hugetlb_tlb_range(struct vm_area_struct *vma, unsigned long start,
				   unsigned long end)
{
	int psize;
	struct hstate *hstate = hstate_file(vma->vm_file);

	psize = hstate_get_psize(hstate);
	radix__flush_tlb_range_psize(vma->vm_mm, start, end, psize);
}