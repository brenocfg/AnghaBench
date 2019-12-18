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
struct cpa_data {unsigned long* vaddr; int numpages; int /*<<< orphan*/  flags; int /*<<< orphan*/  mask_clr; int /*<<< orphan*/  mask_set; int /*<<< orphan*/ * pgd; } ;

/* Variables and functions */
 int _PAGE_PRESENT ; 
 int _PAGE_RW ; 
 int __change_page_attr_set_clr (struct cpa_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pgprot (int) ; 
 scalar_t__ page_address (struct page*) ; 

__attribute__((used)) static int __set_pages_np(struct page *page, int numpages)
{
	unsigned long tempaddr = (unsigned long) page_address(page);
	struct cpa_data cpa = { .vaddr = &tempaddr,
				.pgd = NULL,
				.numpages = numpages,
				.mask_set = __pgprot(0),
				.mask_clr = __pgprot(_PAGE_PRESENT | _PAGE_RW),
				.flags = 0};

	/*
	 * No alias checking needed for setting not present flag. otherwise,
	 * we may need to break large pages for 64-bit kernel text
	 * mappings (this adds to complexity if we want to do this from
	 * atomic context especially). Let's keep it simple!
	 */
	return __change_page_attr_set_clr(&cpa, 0);
}