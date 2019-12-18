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
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __cpuc_flush_dcache_area (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __flush_icache_all () ; 
 scalar_t__ cache_is_vipt_nonaliasing () ; 
 scalar_t__ cache_is_vivt () ; 
 int /*<<< orphan*/  flush_cache_page (struct vm_area_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  flush_pfn_alias (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 unsigned long page_to_pfn (struct page*) ; 

void __flush_anon_page(struct vm_area_struct *vma, struct page *page, unsigned long vmaddr)
{
	unsigned long pfn;

	/* VIPT non-aliasing caches need do nothing */
	if (cache_is_vipt_nonaliasing())
		return;

	/*
	 * Write back and invalidate userspace mapping.
	 */
	pfn = page_to_pfn(page);
	if (cache_is_vivt()) {
		flush_cache_page(vma, vmaddr, pfn);
	} else {
		/*
		 * For aliasing VIPT, we can flush an alias of the
		 * userspace address only.
		 */
		flush_pfn_alias(pfn, vmaddr);
		__flush_icache_all();
	}

	/*
	 * Invalidate kernel mapping.  No data should be contained
	 * in this mapping of the page.  FIXME: this is overkill
	 * since we actually ask for a write-back and invalidate.
	 */
	__cpuc_flush_dcache_area(page_address(page), PAGE_SIZE);
}