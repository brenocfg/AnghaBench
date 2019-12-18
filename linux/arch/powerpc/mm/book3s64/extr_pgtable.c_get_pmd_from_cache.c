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
struct TYPE_2__ {void* pmd_frag; } ;
struct mm_struct {int /*<<< orphan*/  page_table_lock; TYPE_1__ context; } ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int PMD_FRAG_NR ; 
 int PMD_FRAG_SIZE ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static pmd_t *get_pmd_from_cache(struct mm_struct *mm)
{
	void *pmd_frag, *ret;

	if (PMD_FRAG_NR == 1)
		return NULL;

	spin_lock(&mm->page_table_lock);
	ret = mm->context.pmd_frag;
	if (ret) {
		pmd_frag = ret + PMD_FRAG_SIZE;
		/*
		 * If we have taken up all the fragments mark PTE page NULL
		 */
		if (((unsigned long)pmd_frag & ~PAGE_MASK) == 0)
			pmd_frag = NULL;
		mm->context.pmd_frag = pmd_frag;
	}
	spin_unlock(&mm->page_table_lock);
	return (pmd_t *)ret;
}