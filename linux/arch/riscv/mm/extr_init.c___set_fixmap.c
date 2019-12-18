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
typedef  int phys_addr_t ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  enum fixed_addresses { ____Placeholder_fixed_addresses } fixed_addresses ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int FIX_HOLE ; 
 int PAGE_SHIFT ; 
 int __end_of_fixed_addresses ; 
 unsigned long __fix_to_virt (int) ; 
 int /*<<< orphan*/ * fixmap_pte ; 
 int /*<<< orphan*/  init_mm ; 
 int /*<<< orphan*/  local_flush_tlb_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_pte (int,int /*<<< orphan*/ ) ; 
 scalar_t__ pgprot_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_clear (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 
 size_t pte_index (unsigned long) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void __set_fixmap(enum fixed_addresses idx, phys_addr_t phys, pgprot_t prot)
{
	unsigned long addr = __fix_to_virt(idx);
	pte_t *ptep;

	BUG_ON(idx <= FIX_HOLE || idx >= __end_of_fixed_addresses);

	ptep = &fixmap_pte[pte_index(addr)];

	if (pgprot_val(prot)) {
		set_pte(ptep, pfn_pte(phys >> PAGE_SHIFT, prot));
	} else {
		pte_clear(&init_mm, addr, ptep);
		local_flush_tlb_page(addr);
	}
}