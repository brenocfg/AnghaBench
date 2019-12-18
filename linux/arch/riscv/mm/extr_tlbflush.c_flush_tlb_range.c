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
 int /*<<< orphan*/  __sbi_tlb_flush_range (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  mm_cpumask (int /*<<< orphan*/ ) ; 

void flush_tlb_range(struct vm_area_struct *vma, unsigned long start,
		     unsigned long end)
{
	__sbi_tlb_flush_range(mm_cpumask(vma->vm_mm), start, end - start);
}