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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int PTRS_PER_PUD ; 
 int __pud_offset (unsigned long) ; 
 scalar_t__ kvm_mips_flush_gva_pmd (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pmd_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pud_present (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool kvm_mips_flush_gva_pud(pud_t *pud, unsigned long start_gva,
				   unsigned long end_gva)
{
	pmd_t *pmd;
	unsigned long end = ~0ul;
	int i_min = __pud_offset(start_gva);
	int i_max = __pud_offset(end_gva);
	bool safe_to_remove = (i_min == 0 && i_max == PTRS_PER_PUD - 1);
	int i;

	for (i = i_min; i <= i_max; ++i, start_gva = 0) {
		if (!pud_present(pud[i]))
			continue;

		pmd = pmd_offset(pud + i, 0);
		if (i == i_max)
			end = end_gva;

		if (kvm_mips_flush_gva_pmd(pmd, start_gva, end)) {
			pud_clear(pud + i);
			pmd_free(NULL, pmd);
		} else {
			safe_to_remove = false;
		}
	}
	return safe_to_remove;
}