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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/ * __alloc_for_ptecache (struct mm_struct*,int) ; 
 int /*<<< orphan*/ * get_pte_from_cache (struct mm_struct*) ; 

pte_t *pte_fragment_alloc(struct mm_struct *mm, int kernel)
{
	pte_t *pte;

	pte = get_pte_from_cache(mm);
	if (pte)
		return pte;

	return __alloc_for_ptecache(mm, kernel);
}