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

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 

__attribute__((used)) static void copy_to_page(struct page *page, unsigned long vaddr,
			 const void *src, int len)
{
	void *kaddr = kmap_atomic(page);

	memcpy(kaddr + (vaddr & ~PAGE_MASK), src, len);
	kunmap_atomic(kaddr);
}