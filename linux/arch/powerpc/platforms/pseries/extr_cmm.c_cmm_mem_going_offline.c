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
struct memory_notify {unsigned long nr_pages; int /*<<< orphan*/  start_pfn; } ;
struct cmm_page_array {int index; unsigned long* page; struct cmm_page_array* next; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_NOIO ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int __GFP_NOMEMALLOC ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 scalar_t__ __get_free_page (int) ; 
 int /*<<< orphan*/  __pa (unsigned long) ; 
 int /*<<< orphan*/  cmm_dbg (char*,...) ; 
 int /*<<< orphan*/  cmm_lock ; 
 struct cmm_page_array* cmm_page_list ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  loaned_pages ; 
 int /*<<< orphan*/  memcpy (struct cmm_page_array*,struct cmm_page_array*,int /*<<< orphan*/ ) ; 
 scalar_t__ pfn_to_kaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plpar_page_set_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  totalram_pages_inc () ; 

__attribute__((used)) static int cmm_mem_going_offline(void *arg)
{
	struct memory_notify *marg = arg;
	unsigned long start_page = (unsigned long)pfn_to_kaddr(marg->start_pfn);
	unsigned long end_page = start_page + (marg->nr_pages << PAGE_SHIFT);
	struct cmm_page_array *pa_curr, *pa_last, *npa;
	unsigned long idx;
	unsigned long freed = 0;

	cmm_dbg("Memory going offline, searching 0x%lx (%ld pages).\n",
			start_page, marg->nr_pages);
	spin_lock(&cmm_lock);

	/* Search the page list for pages in the range to be offlined */
	pa_last = pa_curr = cmm_page_list;
	while (pa_curr) {
		for (idx = (pa_curr->index - 1); (idx + 1) > 0; idx--) {
			if ((pa_curr->page[idx] < start_page) ||
			    (pa_curr->page[idx] >= end_page))
				continue;

			plpar_page_set_active(__pa(pa_curr->page[idx]));
			free_page(pa_curr->page[idx]);
			freed++;
			loaned_pages--;
			totalram_pages_inc();
			pa_curr->page[idx] = pa_last->page[--pa_last->index];
			if (pa_last->index == 0) {
				if (pa_curr == pa_last)
					pa_curr = pa_last->next;
				pa_last = pa_last->next;
				free_page((unsigned long)cmm_page_list);
				cmm_page_list = pa_last;
			}
		}
		pa_curr = pa_curr->next;
	}

	/* Search for page list structures in the range to be offlined */
	pa_last = NULL;
	pa_curr = cmm_page_list;
	while (pa_curr) {
		if (((unsigned long)pa_curr >= start_page) &&
				((unsigned long)pa_curr < end_page)) {
			npa = (struct cmm_page_array *)__get_free_page(
					GFP_NOIO | __GFP_NOWARN |
					__GFP_NORETRY | __GFP_NOMEMALLOC);
			if (!npa) {
				spin_unlock(&cmm_lock);
				cmm_dbg("Failed to allocate memory for list "
						"management. Memory hotplug "
						"failed.\n");
				return -ENOMEM;
			}
			memcpy(npa, pa_curr, PAGE_SIZE);
			if (pa_curr == cmm_page_list)
				cmm_page_list = npa;
			if (pa_last)
				pa_last->next = npa;
			free_page((unsigned long) pa_curr);
			freed++;
			pa_curr = npa;
		}

		pa_last = pa_curr;
		pa_curr = pa_curr->next;
	}

	spin_unlock(&cmm_lock);
	cmm_dbg("Released %ld pages in the search range.\n", freed);

	return 0;
}