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
struct page {int dummy; } ;
struct kvmppc_spapr_tce_table {int /*<<< orphan*/  alloc_lock; struct page** pages; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int __GFP_ZERO ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct page *kvm_spapr_get_tce_page(struct kvmppc_spapr_tce_table *stt,
		unsigned long sttpage)
{
	struct page *page = stt->pages[sttpage];

	if (page)
		return page;

	mutex_lock(&stt->alloc_lock);
	page = stt->pages[sttpage];
	if (!page) {
		page = alloc_page(GFP_KERNEL | __GFP_ZERO);
		WARN_ON_ONCE(!page);
		if (page)
			stt->pages[sttpage] = page;
	}
	mutex_unlock(&stt->alloc_lock);

	return page;
}