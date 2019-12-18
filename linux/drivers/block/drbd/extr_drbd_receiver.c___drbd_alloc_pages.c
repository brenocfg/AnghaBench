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
struct drbd_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_TRY ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_pp_lock ; 
 int /*<<< orphan*/  drbd_pp_pool ; 
 unsigned int drbd_pp_vacant ; 
 int /*<<< orphan*/  page_chain_add (int /*<<< orphan*/ *,struct page*,struct page*) ; 
 struct page* page_chain_del (int /*<<< orphan*/ *,unsigned int) ; 
 struct page* page_chain_tail (struct page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_page_private (struct page*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct page *__drbd_alloc_pages(struct drbd_device *device,
				       unsigned int number)
{
	struct page *page = NULL;
	struct page *tmp = NULL;
	unsigned int i = 0;

	/* Yes, testing drbd_pp_vacant outside the lock is racy.
	 * So what. It saves a spin_lock. */
	if (drbd_pp_vacant >= number) {
		spin_lock(&drbd_pp_lock);
		page = page_chain_del(&drbd_pp_pool, number);
		if (page)
			drbd_pp_vacant -= number;
		spin_unlock(&drbd_pp_lock);
		if (page)
			return page;
	}

	/* GFP_TRY, because we must not cause arbitrary write-out: in a DRBD
	 * "criss-cross" setup, that might cause write-out on some other DRBD,
	 * which in turn might block on the other node at this very place.  */
	for (i = 0; i < number; i++) {
		tmp = alloc_page(GFP_TRY);
		if (!tmp)
			break;
		set_page_private(tmp, (unsigned long)page);
		page = tmp;
	}

	if (i == number)
		return page;

	/* Not enough pages immediately available this time.
	 * No need to jump around here, drbd_alloc_pages will retry this
	 * function "soon". */
	if (page) {
		tmp = page_chain_tail(page, NULL);
		spin_lock(&drbd_pp_lock);
		page_chain_add(&drbd_pp_pool, page, tmp);
		drbd_pp_vacant += i;
		spin_unlock(&drbd_pp_lock);
	}
	return NULL;
}