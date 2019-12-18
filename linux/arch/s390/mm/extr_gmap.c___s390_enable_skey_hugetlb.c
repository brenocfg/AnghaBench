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
struct page {int /*<<< orphan*/  flags; } ;
struct mm_walk {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 unsigned long HPAGE_MASK ; 
 unsigned long HPAGE_SIZE ; 
 int /*<<< orphan*/  PG_arch_1 ; 
 unsigned long _SEGMENT_ENTRY_INVALID ; 
 unsigned long _SEGMENT_ENTRY_WRITE ; 
 int /*<<< orphan*/  __storage_key_init_range (unsigned long,unsigned long) ; 
 struct page* pmd_page (int /*<<< orphan*/ ) ; 
 unsigned long pmd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __s390_enable_skey_hugetlb(pte_t *pte, unsigned long addr,
				      unsigned long hmask, unsigned long next,
				      struct mm_walk *walk)
{
	pmd_t *pmd = (pmd_t *)pte;
	unsigned long start, end;
	struct page *page = pmd_page(*pmd);

	/*
	 * The write check makes sure we do not set a key on shared
	 * memory. This is needed as the walker does not differentiate
	 * between actual guest memory and the process executable or
	 * shared libraries.
	 */
	if (pmd_val(*pmd) & _SEGMENT_ENTRY_INVALID ||
	    !(pmd_val(*pmd) & _SEGMENT_ENTRY_WRITE))
		return 0;

	start = pmd_val(*pmd) & HPAGE_MASK;
	end = start + HPAGE_SIZE - 1;
	__storage_key_init_range(start, end);
	set_bit(PG_arch_1, &page->flags);
	return 0;
}