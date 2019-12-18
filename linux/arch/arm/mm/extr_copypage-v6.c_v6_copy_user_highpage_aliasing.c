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
 unsigned int CACHE_COLOUR (unsigned long) ; 
 unsigned int COPYPAGE_V6_FROM ; 
 unsigned int COPYPAGE_V6_TO ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  PG_dcache_clean ; 
 int /*<<< orphan*/  __flush_dcache_page (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  copy_page (void*,void*) ; 
 int /*<<< orphan*/  discard_old_kernel_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  page_mapping_file (struct page*) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_top_pte (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v6_lock ; 

__attribute__((used)) static void v6_copy_user_highpage_aliasing(struct page *to,
	struct page *from, unsigned long vaddr, struct vm_area_struct *vma)
{
	unsigned int offset = CACHE_COLOUR(vaddr);
	unsigned long kfrom, kto;

	if (!test_and_set_bit(PG_dcache_clean, &from->flags))
		__flush_dcache_page(page_mapping_file(from), from);

	/* FIXME: not highmem safe */
	discard_old_kernel_data(page_address(to));

	/*
	 * Now copy the page using the same cache colour as the
	 * pages ultimate destination.
	 */
	raw_spin_lock(&v6_lock);

	kfrom = COPYPAGE_V6_FROM + (offset << PAGE_SHIFT);
	kto   = COPYPAGE_V6_TO + (offset << PAGE_SHIFT);

	set_top_pte(kfrom, mk_pte(from, PAGE_KERNEL));
	set_top_pte(kto, mk_pte(to, PAGE_KERNEL));

	copy_page((void *)kto, (void *)kfrom);

	raw_spin_unlock(&v6_lock);
}