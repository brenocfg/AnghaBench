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
struct vm_area_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  book3e_hugetlb_preload (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ is_vm_hugetlb_page (struct vm_area_struct*) ; 

void update_mmu_cache(struct vm_area_struct *vma, unsigned long address, pte_t *ptep)
{
	if (is_vm_hugetlb_page(vma))
		book3e_hugetlb_preload(vma, address, *ptep);
}