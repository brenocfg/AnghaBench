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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long __fix_to_virt (int) ; 
 int /*<<< orphan*/  local_flush_tlb_kernel_page (unsigned long) ; 
 int /*<<< orphan*/  pmd_off_k (unsigned long) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  set_pte_ext (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_fixmap_pte(int idx, pte_t pte)
{
	unsigned long vaddr = __fix_to_virt(idx);
	pte_t *ptep = pte_offset_kernel(pmd_off_k(vaddr), vaddr);

	set_pte_ext(ptep, pte, 0);
	local_flush_tlb_kernel_page(vaddr);
}