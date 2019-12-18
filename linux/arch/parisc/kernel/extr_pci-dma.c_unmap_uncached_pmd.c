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
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 unsigned long PGDIR_MASK ; 
 unsigned long PGDIR_SIZE ; 
 unsigned long PMD_MASK ; 
 unsigned long PMD_SIZE ; 
 int /*<<< orphan*/  pgd_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ pgd_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unmap_uncached_pte (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 

__attribute__((used)) static inline void unmap_uncached_pmd(pgd_t * dir, unsigned long vaddr,
		unsigned long size)
{
	pmd_t * pmd;
	unsigned long end;
	unsigned long orig_vaddr = vaddr;

	if (pgd_none(*dir))
		return;
	if (pgd_bad(*dir)) {
		pgd_ERROR(*dir);
		pgd_clear(dir);
		return;
	}
	pmd = pmd_offset(dir, vaddr);
	vaddr &= ~PGDIR_MASK;
	end = vaddr + size;
	if (end > PGDIR_SIZE)
		end = PGDIR_SIZE;
	do {
		unmap_uncached_pte(pmd, orig_vaddr, end - vaddr);
		vaddr = (vaddr + PMD_SIZE) & PMD_MASK;
		orig_vaddr += PMD_SIZE;
		pmd++;
	} while (vaddr < end);
}