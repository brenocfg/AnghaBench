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
 int /*<<< orphan*/  cache_wbinv_range (unsigned long,unsigned long) ; 
 scalar_t__ kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 

void flush_icache_user_range(struct vm_area_struct *vma, struct page *page,
			     unsigned long vaddr, int len)
{
	unsigned long kaddr;

	kaddr = (unsigned long) kmap_atomic(page) + (vaddr & ~PAGE_MASK);

	cache_wbinv_range(kaddr, kaddr + len);

	kunmap_atomic((void *)kaddr);
}