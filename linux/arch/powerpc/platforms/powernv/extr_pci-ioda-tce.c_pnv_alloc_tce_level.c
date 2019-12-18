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
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int GFP_ATOMIC ; 
 scalar_t__ PAGE_SHIFT ; 
 int __GFP_NOWARN ; 
 struct page* alloc_pages_node (int,int,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/ * page_address (struct page*) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 

__attribute__((used)) static __be64 *pnv_alloc_tce_level(int nid, unsigned int shift)
{
	struct page *tce_mem = NULL;
	__be64 *addr;

	tce_mem = alloc_pages_node(nid, GFP_ATOMIC | __GFP_NOWARN,
			shift - PAGE_SHIFT);
	if (!tce_mem) {
		pr_err("Failed to allocate a TCE memory, level shift=%d\n",
				shift);
		return NULL;
	}
	addr = page_address(tce_mem);
	memset(addr, 0, 1UL << shift);

	return addr;
}