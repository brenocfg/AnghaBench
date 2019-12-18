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
 void radix__ptep_modify_prot_commit (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ radix_enabled () ; 
 int /*<<< orphan*/  set_pte_at (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ptep_modify_prot_commit(struct vm_area_struct *vma, unsigned long addr,
			     pte_t *ptep, pte_t old_pte, pte_t pte)
{
	if (radix_enabled())
		return radix__ptep_modify_prot_commit(vma, addr,
						      ptep, old_pte, pte);
	set_pte_at(vma->vm_mm, addr, ptep, pte);
}