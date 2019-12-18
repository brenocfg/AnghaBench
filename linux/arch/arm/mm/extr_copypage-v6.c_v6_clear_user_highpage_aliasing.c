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

/* Variables and functions */
 unsigned long CACHE_COLOUR (unsigned long) ; 
 unsigned long COPYPAGE_V6_TO ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  clear_page (void*) ; 
 int /*<<< orphan*/  discard_old_kernel_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_top_pte (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v6_lock ; 

__attribute__((used)) static void v6_clear_user_highpage_aliasing(struct page *page, unsigned long vaddr)
{
	unsigned long to = COPYPAGE_V6_TO + (CACHE_COLOUR(vaddr) << PAGE_SHIFT);

	/* FIXME: not highmem safe */
	discard_old_kernel_data(page_address(page));

	/*
	 * Now clear the page using the same cache colour as
	 * the pages ultimate destination.
	 */
	raw_spin_lock(&v6_lock);

	set_top_pte(to, mk_pte(page, PAGE_KERNEL));
	clear_page((void *)to);

	raw_spin_unlock(&v6_lock);
}