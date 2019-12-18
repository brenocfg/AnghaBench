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

/* Variables and functions */
 int PTRS_PER_PMD ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  pmd_none (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool try_to_free_pmd_page(pmd_t *pmd)
{
	int i;

	for (i = 0; i < PTRS_PER_PMD; i++)
		if (!pmd_none(pmd[i]))
			return false;

	free_page((unsigned long)pmd);
	return true;
}