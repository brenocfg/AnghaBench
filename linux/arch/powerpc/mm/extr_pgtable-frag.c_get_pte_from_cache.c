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
struct mm_struct {int /*<<< orphan*/  page_table_lock; int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int PTE_FRAG_NR ; 
 int PTE_FRAG_SIZE ; 
 void* pte_frag_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_frag_set (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static pte_t *get_pte_from_cache(struct mm_struct *mm)
{
	void *pte_frag, *ret;

	if (PTE_FRAG_NR == 1)
		return NULL;

	spin_lock(&mm->page_table_lock);
	ret = pte_frag_get(&mm->context);
	if (ret) {
		pte_frag = ret + PTE_FRAG_SIZE;
		/*
		 * If we have taken up all the fragments mark PTE page NULL
		 */
		if (((unsigned long)pte_frag & ~PAGE_MASK) == 0)
			pte_frag = NULL;
		pte_frag_set(&mm->context, pte_frag);
	}
	spin_unlock(&mm->page_table_lock);
	return (pte_t *)ret;
}