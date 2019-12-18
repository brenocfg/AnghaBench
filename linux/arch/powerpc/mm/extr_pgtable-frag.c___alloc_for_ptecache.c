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
struct page {int /*<<< orphan*/  pt_frag_refcount; } ;
struct mm_struct {int /*<<< orphan*/  page_table_lock; int /*<<< orphan*/  context; } ;
typedef  void pte_t ;

/* Variables and functions */
 int PGALLOC_GFP ; 
 int PTE_FRAG_NR ; 
 int PTE_FRAG_SIZE ; 
 int __GFP_ACCOUNT ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ likely (int) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  pgtable_pte_page_ctor (struct page*) ; 
 int /*<<< orphan*/  pte_frag_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_frag_set (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static pte_t *__alloc_for_ptecache(struct mm_struct *mm, int kernel)
{
	void *ret = NULL;
	struct page *page;

	if (!kernel) {
		page = alloc_page(PGALLOC_GFP | __GFP_ACCOUNT);
		if (!page)
			return NULL;
		if (!pgtable_pte_page_ctor(page)) {
			__free_page(page);
			return NULL;
		}
	} else {
		page = alloc_page(PGALLOC_GFP);
		if (!page)
			return NULL;
	}

	atomic_set(&page->pt_frag_refcount, 1);

	ret = page_address(page);
	/*
	 * if we support only one fragment just return the
	 * allocated page.
	 */
	if (PTE_FRAG_NR == 1)
		return ret;
	spin_lock(&mm->page_table_lock);
	/*
	 * If we find pgtable_page set, we return
	 * the allocated page with single fragement
	 * count.
	 */
	if (likely(!pte_frag_get(&mm->context))) {
		atomic_set(&page->pt_frag_refcount, PTE_FRAG_NR);
		pte_frag_set(&mm->context, ret + PTE_FRAG_SIZE);
	}
	spin_unlock(&mm->page_table_lock);

	return (pte_t *)ret;
}