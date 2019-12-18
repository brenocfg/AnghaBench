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
struct drbd_bitmap {unsigned long bm_number_of_pages; struct page** bm_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int GFP_NOIO ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int __GFP_HIGHMEM ; 
 int __GFP_NOWARN ; 
 int __GFP_ZERO ; 
 struct page** __vmalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  bm_free_pages (struct page**,unsigned int) ; 
 int /*<<< orphan*/  bm_store_page_idx (struct page*,unsigned int) ; 
 int /*<<< orphan*/  bm_vk_free (struct page**) ; 
 struct page** kzalloc (unsigned int,int) ; 

__attribute__((used)) static struct page **bm_realloc_pages(struct drbd_bitmap *b, unsigned long want)
{
	struct page **old_pages = b->bm_pages;
	struct page **new_pages, *page;
	unsigned int i, bytes;
	unsigned long have = b->bm_number_of_pages;

	BUG_ON(have == 0 && old_pages != NULL);
	BUG_ON(have != 0 && old_pages == NULL);

	if (have == want)
		return old_pages;

	/* Trying kmalloc first, falling back to vmalloc.
	 * GFP_NOIO, as this is called while drbd IO is "suspended",
	 * and during resize or attach on diskless Primary,
	 * we must not block on IO to ourselves.
	 * Context is receiver thread or dmsetup. */
	bytes = sizeof(struct page *)*want;
	new_pages = kzalloc(bytes, GFP_NOIO | __GFP_NOWARN);
	if (!new_pages) {
		new_pages = __vmalloc(bytes,
				GFP_NOIO | __GFP_ZERO,
				PAGE_KERNEL);
		if (!new_pages)
			return NULL;
	}

	if (want >= have) {
		for (i = 0; i < have; i++)
			new_pages[i] = old_pages[i];
		for (; i < want; i++) {
			page = alloc_page(GFP_NOIO | __GFP_HIGHMEM);
			if (!page) {
				bm_free_pages(new_pages + have, i - have);
				bm_vk_free(new_pages);
				return NULL;
			}
			/* we want to know which page it is
			 * from the endio handlers */
			bm_store_page_idx(page, i);
			new_pages[i] = page;
		}
	} else {
		for (i = 0; i < want; i++)
			new_pages[i] = old_pages[i];
		/* NOT HERE, we are outside the spinlock!
		bm_free_pages(old_pages + want, have - want);
		*/
	}

	return new_pages;
}