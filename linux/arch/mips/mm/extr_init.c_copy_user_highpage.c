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
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  Page_dcache_dirty (struct page*) ; 
 int /*<<< orphan*/  copy_page (void*,void*) ; 
 scalar_t__ cpu_has_dc_aliases ; 
 int /*<<< orphan*/  cpu_has_ic_fills_f_dc ; 
 int /*<<< orphan*/  flush_data_cache_page (unsigned long) ; 
 void* kmap_atomic (struct page*) ; 
 void* kmap_coherent (struct page*,unsigned long) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  kunmap_coherent () ; 
 scalar_t__ page_mapcount (struct page*) ; 
 scalar_t__ pages_do_alias (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  smp_wmb () ; 

void copy_user_highpage(struct page *to, struct page *from,
	unsigned long vaddr, struct vm_area_struct *vma)
{
	void *vfrom, *vto;

	vto = kmap_atomic(to);
	if (cpu_has_dc_aliases &&
	    page_mapcount(from) && !Page_dcache_dirty(from)) {
		vfrom = kmap_coherent(from, vaddr);
		copy_page(vto, vfrom);
		kunmap_coherent();
	} else {
		vfrom = kmap_atomic(from);
		copy_page(vto, vfrom);
		kunmap_atomic(vfrom);
	}
	if ((!cpu_has_ic_fills_f_dc) ||
	    pages_do_alias((unsigned long)vto, vaddr & PAGE_MASK))
		flush_data_cache_page((unsigned long)vto);
	kunmap_atomic(vto);
	/* Make sure this page is cleared on other CPU's too before using it */
	smp_wmb();
}