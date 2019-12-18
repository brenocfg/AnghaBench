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
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  cache_wbinv_range (unsigned long,scalar_t__) ; 
 scalar_t__ kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 

void flush_icache_page(struct vm_area_struct *vma, struct page *page)
{
	unsigned long start;

	start = (unsigned long) kmap_atomic(page);

	cache_wbinv_range(start, start + PAGE_SIZE);

	kunmap_atomic((void *)start);
}