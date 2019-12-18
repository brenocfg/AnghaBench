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
struct vm_area_struct {int vm_flags; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int VM_SPARC_ADI ; 
 int /*<<< orphan*/  hstate_vma (struct vm_area_struct*) ; 
 unsigned int huge_page_shift (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hugepage_shift_to_tte (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pte_mkmcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mknotmcd (int /*<<< orphan*/ ) ; 

pte_t arch_make_huge_pte(pte_t entry, struct vm_area_struct *vma,
			 struct page *page, int writeable)
{
	unsigned int shift = huge_page_shift(hstate_vma(vma));
	pte_t pte;

	pte = hugepage_shift_to_tte(entry, shift);

#ifdef CONFIG_SPARC64
	/* If this vma has ADI enabled on it, turn on TTE.mcd
	 */
	if (vma->vm_flags & VM_SPARC_ADI)
		return pte_mkmcd(pte);
	else
		return pte_mknotmcd(pte);
#else
	return pte;
#endif
}