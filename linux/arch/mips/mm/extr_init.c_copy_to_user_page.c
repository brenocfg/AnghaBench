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
struct vm_area_struct {int vm_flags; } ;
struct page {int dummy; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  Page_dcache_dirty (struct page*) ; 
 int /*<<< orphan*/  SetPageDcacheDirty (struct page*) ; 
 int VM_EXEC ; 
 scalar_t__ cpu_has_dc_aliases ; 
 int /*<<< orphan*/  flush_cache_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 void* kmap_coherent (struct page*,unsigned long) ; 
 int /*<<< orphan*/  kunmap_coherent () ; 
 int /*<<< orphan*/  memcpy (void*,void const*,unsigned long) ; 
 scalar_t__ page_mapcount (struct page*) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 

void copy_to_user_page(struct vm_area_struct *vma,
	struct page *page, unsigned long vaddr, void *dst, const void *src,
	unsigned long len)
{
	if (cpu_has_dc_aliases &&
	    page_mapcount(page) && !Page_dcache_dirty(page)) {
		void *vto = kmap_coherent(page, vaddr) + (vaddr & ~PAGE_MASK);
		memcpy(vto, src, len);
		kunmap_coherent();
	} else {
		memcpy(dst, src, len);
		if (cpu_has_dc_aliases)
			SetPageDcacheDirty(page);
	}
	if (vma->vm_flags & VM_EXEC)
		flush_cache_page(vma, vaddr, page_to_pfn(page));
}