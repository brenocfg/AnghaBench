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
struct host_vm_change {scalar_t__ force; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned long STUB_END ; 
 unsigned long STUB_START ; 
 int UM_PROT_EXEC ; 
 int UM_PROT_READ ; 
 int UM_PROT_WRITE ; 
 int add_mmap (unsigned long,int,scalar_t__,int,struct host_vm_change*) ; 
 int add_mprotect (unsigned long,scalar_t__,int,struct host_vm_change*) ; 
 int add_munmap (unsigned long,scalar_t__,struct host_vm_change*) ; 
 int /*<<< orphan*/  pte_dirty (int /*<<< orphan*/ ) ; 
 int pte_exec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkuptodate (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_newpage (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_newprot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 int pte_read (int /*<<< orphan*/ ) ; 
 int pte_val (int /*<<< orphan*/ ) ; 
 int pte_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_young (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int update_pte_range(pmd_t *pmd, unsigned long addr,
				   unsigned long end,
				   struct host_vm_change *hvc)
{
	pte_t *pte;
	int r, w, x, prot, ret = 0;

	pte = pte_offset_kernel(pmd, addr);
	do {
		if ((addr >= STUB_START) && (addr < STUB_END))
			continue;

		r = pte_read(*pte);
		w = pte_write(*pte);
		x = pte_exec(*pte);
		if (!pte_young(*pte)) {
			r = 0;
			w = 0;
		} else if (!pte_dirty(*pte))
			w = 0;

		prot = ((r ? UM_PROT_READ : 0) | (w ? UM_PROT_WRITE : 0) |
			(x ? UM_PROT_EXEC : 0));
		if (hvc->force || pte_newpage(*pte)) {
			if (pte_present(*pte)) {
				if (pte_newpage(*pte))
					ret = add_mmap(addr, pte_val(*pte) & PAGE_MASK,
						       PAGE_SIZE, prot, hvc);
			} else
				ret = add_munmap(addr, PAGE_SIZE, hvc);
		} else if (pte_newprot(*pte))
			ret = add_mprotect(addr, PAGE_SIZE, prot, hvc);
		*pte = pte_mkuptodate(*pte);
	} while (pte++, addr += PAGE_SIZE, ((addr < end) && !ret));
	return ret;
}