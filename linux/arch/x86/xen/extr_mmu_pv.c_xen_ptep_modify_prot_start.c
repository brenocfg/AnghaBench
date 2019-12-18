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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  trace_xen_mmu_ptep_modify_prot_start (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

pte_t xen_ptep_modify_prot_start(struct vm_area_struct *vma,
				 unsigned long addr, pte_t *ptep)
{
	/* Just return the pte as-is.  We preserve the bits on commit */
	trace_xen_mmu_ptep_modify_prot_start(vma->vm_mm, addr, ptep, *ptep);
	return *ptep;
}