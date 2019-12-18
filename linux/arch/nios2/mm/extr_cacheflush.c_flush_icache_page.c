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
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  __flush_dcache (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  __flush_icache (unsigned long,unsigned long) ; 
 scalar_t__ page_address (struct page*) ; 

void flush_icache_page(struct vm_area_struct *vma, struct page *page)
{
	unsigned long start = (unsigned long) page_address(page);
	unsigned long end = start + PAGE_SIZE;

	__flush_dcache(start, end);
	__flush_icache(start, end);
}