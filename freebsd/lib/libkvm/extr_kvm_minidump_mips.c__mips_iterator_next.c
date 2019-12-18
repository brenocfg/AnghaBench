#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_prot_t ;
typedef  scalar_t__ u_long ;
struct TYPE_4__ {scalar_t__ kernbase; } ;
struct vmstate {int pte_size; TYPE_1__ hdr; } ;
struct mips_iter {int pteindex; int nptes; TYPE_2__* kd; } ;
typedef  int mips64_pte_t ;
typedef  int mips32_pte_t ;
struct TYPE_5__ {struct vmstate* vmst; } ;

/* Variables and functions */
 int MIPS32_PTE_RO ; 
 scalar_t__ MIPS32_PTE_TO_PA (int) ; 
 int MIPS64_PTE_RO ; 
 scalar_t__ MIPS64_PTE_TO_PA (int) ; 
 int MIPS_PAGE_SHIFT ; 
 int MIPS_PTE_V ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int _mips32_pte_get (TYPE_2__*,int) ; 
 int _mips64_pte_get (TYPE_2__*,int) ; 

__attribute__((used)) static int
_mips_iterator_next(struct mips_iter *it, u_long *pa, u_long *va, u_long *dva,
    vm_prot_t *prot)
{
	struct vmstate *vm = it->kd->vmst;
	int found = 0;
	mips64_pte_t pte64;
	mips32_pte_t pte32;

	/*
	 * mips/mips/pmap.c: init_pte_prot / pmap_protect indicate that all
	 * pages are R|X at least.
	 */
	*prot = VM_PROT_READ | VM_PROT_EXECUTE;
	*pa = 0;
	*va = 0;
	*dva = 0;
	for (;it->pteindex < it->nptes && found == 0; it->pteindex++) {
		if (vm->pte_size == 64) {
			pte64 = _mips64_pte_get(it->kd, it->pteindex);
			if ((pte64 & MIPS_PTE_V) == 0)
				continue;
			if ((pte64 & MIPS64_PTE_RO) == 0)
				*prot |= VM_PROT_WRITE;
			*pa = MIPS64_PTE_TO_PA(pte64);
		} else {
			pte32 = _mips32_pte_get(it->kd, it->pteindex);
			if ((pte32 & MIPS_PTE_V) == 0)
				continue;
			if ((pte32 & MIPS32_PTE_RO) == 0)
				*prot |= VM_PROT_WRITE;
			*pa = MIPS32_PTE_TO_PA(pte32);
		}
		*va = vm->hdr.kernbase + (it->pteindex << MIPS_PAGE_SHIFT);
		found = 1;
		/* advance pteindex regardless */
	}

	return found;
}