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
 scalar_t__ COPYPAGE_MINICACHE ; 
 int /*<<< orphan*/  PG_dcache_clean ; 
 int /*<<< orphan*/  __flush_dcache_page (int /*<<< orphan*/ ,struct page*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  mc_copy_user_page (void*,void*) ; 
 int /*<<< orphan*/  minicache_lock ; 
 int /*<<< orphan*/  minicache_pgprot ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_mapping_file (struct page*) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_top_pte (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void xscale_mc_copy_user_highpage(struct page *to, struct page *from,
	unsigned long vaddr, struct vm_area_struct *vma)
{
	void *kto = kmap_atomic(to);

	if (!test_and_set_bit(PG_dcache_clean, &from->flags))
		__flush_dcache_page(page_mapping_file(from), from);

	raw_spin_lock(&minicache_lock);

	set_top_pte(COPYPAGE_MINICACHE, mk_pte(from, minicache_pgprot));

	mc_copy_user_page((void *)COPYPAGE_MINICACHE, kto);

	raw_spin_unlock(&minicache_lock);

	kunmap_atomic(kto);
}