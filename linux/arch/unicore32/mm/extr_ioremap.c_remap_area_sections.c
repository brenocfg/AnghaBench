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
struct mem_type {int prot_sect; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 scalar_t__ PGDIR_SIZE ; 
 unsigned long SZ_4M ; 
 int __pfn_to_phys (unsigned long) ; 
 int /*<<< orphan*/  __pmd (int) ; 
 int /*<<< orphan*/  flush_pmd_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  set_pmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_area_sections (unsigned long,size_t) ; 

__attribute__((used)) static int
remap_area_sections(unsigned long virt, unsigned long pfn,
		    size_t size, const struct mem_type *type)
{
	unsigned long addr = virt, end = virt + size;
	pgd_t *pgd;

	/*
	 * Remove and free any PTE-based mapping, and
	 * sync the current kernel mapping.
	 */
	unmap_area_sections(virt, size);

	pgd = pgd_offset_k(addr);
	do {
		pmd_t *pmd = pmd_offset((pud_t *)pgd, addr);

		set_pmd(pmd, __pmd(__pfn_to_phys(pfn) | type->prot_sect));
		pfn += SZ_4M >> PAGE_SHIFT;
		flush_pmd_entry(pmd);

		addr += PGDIR_SIZE;
		pgd++;
	} while (addr < end);

	return 0;
}