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
 int /*<<< orphan*/  huge_ptep_get (int /*<<< orphan*/ *) ; 
 scalar_t__ pte_dirty (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_write (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_young (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __cont_access_flags_changed(pte_t *ptep, pte_t pte, int ncontig)
{
	int i;

	if (pte_write(pte) != pte_write(huge_ptep_get(ptep)))
		return 1;

	for (i = 0; i < ncontig; i++) {
		pte_t orig_pte = huge_ptep_get(ptep + i);

		if (pte_dirty(pte) != pte_dirty(orig_pte))
			return 1;

		if (pte_young(pte) != pte_young(orig_pte))
			return 1;
	}

	return 0;
}