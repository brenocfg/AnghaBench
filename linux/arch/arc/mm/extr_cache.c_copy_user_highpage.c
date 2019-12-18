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
struct page {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PG_dc_clean ; 
 int /*<<< orphan*/  __flush_dcache_page (unsigned long,unsigned long) ; 
 scalar_t__ addr_not_cache_congruent (void*,unsigned long) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_page (void*,void*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 scalar_t__ page_mapcount (struct page*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void copy_user_highpage(struct page *to, struct page *from,
	unsigned long u_vaddr, struct vm_area_struct *vma)
{
	void *kfrom = kmap_atomic(from);
	void *kto = kmap_atomic(to);
	int clean_src_k_mappings = 0;

	/*
	 * If SRC page was already mapped in userspace AND it's U-mapping is
	 * not congruent with K-mapping, sync former to physical page so that
	 * K-mapping in memcpy below, sees the right data
	 *
	 * Note that while @u_vaddr refers to DST page's userspace vaddr, it is
	 * equally valid for SRC page as well
	 *
	 * For !VIPT cache, all of this gets compiled out as
	 * addr_not_cache_congruent() is 0
	 */
	if (page_mapcount(from) && addr_not_cache_congruent(kfrom, u_vaddr)) {
		__flush_dcache_page((unsigned long)kfrom, u_vaddr);
		clean_src_k_mappings = 1;
	}

	copy_page(kto, kfrom);

	/*
	 * Mark DST page K-mapping as dirty for a later finalization by
	 * update_mmu_cache(). Although the finalization could have been done
	 * here as well (given that both vaddr/paddr are available).
	 * But update_mmu_cache() already has code to do that for other
	 * non copied user pages (e.g. read faults which wire in pagecache page
	 * directly).
	 */
	clear_bit(PG_dc_clean, &to->flags);

	/*
	 * if SRC was already usermapped and non-congruent to kernel mapping
	 * sync the kernel mapping back to physical page
	 */
	if (clean_src_k_mappings) {
		__flush_dcache_page((unsigned long)kfrom, (unsigned long)kfrom);
		set_bit(PG_dc_clean, &from->flags);
	} else {
		clear_bit(PG_dc_clean, &from->flags);
	}

	kunmap_atomic(kto);
	kunmap_atomic(kfrom);
}