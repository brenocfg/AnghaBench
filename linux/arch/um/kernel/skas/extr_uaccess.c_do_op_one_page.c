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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 scalar_t__ kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/ * maybe_map (unsigned long,int) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  pagefault_enable () ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 int stub1 (unsigned long,int,void*) ; 

__attribute__((used)) static int do_op_one_page(unsigned long addr, int len, int is_write,
		 int (*op)(unsigned long addr, int len, void *arg), void *arg)
{
	struct page *page;
	pte_t *pte;
	int n;

	pte = maybe_map(addr, is_write);
	if (pte == NULL)
		return -1;

	page = pte_page(*pte);
#ifdef CONFIG_64BIT
	pagefault_disable();
	addr = (unsigned long) page_address(page) +
		(addr & ~PAGE_MASK);
#else
	addr = (unsigned long) kmap_atomic(page) +
		(addr & ~PAGE_MASK);
#endif
	n = (*op)(addr, len, arg);

#ifdef CONFIG_64BIT
	pagefault_enable();
#else
	kunmap_atomic((void *)addr);
#endif

	return n;
}