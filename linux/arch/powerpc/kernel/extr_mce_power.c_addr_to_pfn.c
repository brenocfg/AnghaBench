#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  pgd; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 unsigned int PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 unsigned long ULONG_MAX ; 
 int /*<<< orphan*/ * __find_linux_pte (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  __pte (unsigned long) ; 
 TYPE_1__* current ; 
 struct mm_struct init_mm ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_special (int /*<<< orphan*/ ) ; 
 unsigned long pte_val (int /*<<< orphan*/ ) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

unsigned long addr_to_pfn(struct pt_regs *regs, unsigned long addr)
{
	pte_t *ptep;
	unsigned int shift;
	unsigned long pfn, flags;
	struct mm_struct *mm;

	if (user_mode(regs))
		mm = current->mm;
	else
		mm = &init_mm;

	local_irq_save(flags);
	ptep = __find_linux_pte(mm->pgd, addr, NULL, &shift);

	if (!ptep || pte_special(*ptep)) {
		pfn = ULONG_MAX;
		goto out;
	}

	if (shift <= PAGE_SHIFT)
		pfn = pte_pfn(*ptep);
	else {
		unsigned long rpnmask = (1ul << shift) - PAGE_SIZE;
		pfn = pte_pfn(__pte(pte_val(*ptep) | (addr & rpnmask)));
	}

out:
	local_irq_restore(flags);
	return pfn;
}