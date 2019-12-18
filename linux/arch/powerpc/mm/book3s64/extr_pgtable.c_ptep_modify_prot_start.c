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
 int /*<<< orphan*/  _PAGE_INVALID ; 
 int /*<<< orphan*/  _PAGE_PRESENT ; 
 int /*<<< orphan*/  __pte (unsigned long) ; 
 unsigned long pte_update (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

pte_t ptep_modify_prot_start(struct vm_area_struct *vma, unsigned long addr,
			     pte_t *ptep)
{
	unsigned long pte_val;

	/*
	 * Clear the _PAGE_PRESENT so that no hardware parallel update is
	 * possible. Also keep the pte_present true so that we don't take
	 * wrong fault.
	 */
	pte_val = pte_update(vma->vm_mm, addr, ptep, _PAGE_PRESENT, _PAGE_INVALID, 0);

	return __pte(pte_val);

}