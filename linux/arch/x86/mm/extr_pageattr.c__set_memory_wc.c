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

/* Variables and functions */
 int /*<<< orphan*/  _PAGE_CACHE_MASK ; 
 int /*<<< orphan*/  _PAGE_CACHE_MODE_UC_MINUS ; 
 int /*<<< orphan*/  _PAGE_CACHE_MODE_WC ; 
 int /*<<< orphan*/  __pgprot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cachemode2pgprot (int /*<<< orphan*/ ) ; 
 int change_page_attr_set (unsigned long*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int change_page_attr_set_clr (unsigned long*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int _set_memory_wc(unsigned long addr, int numpages)
{
	int ret;

	ret = change_page_attr_set(&addr, numpages,
				   cachemode2pgprot(_PAGE_CACHE_MODE_UC_MINUS),
				   0);
	if (!ret) {
		ret = change_page_attr_set_clr(&addr, numpages,
					       cachemode2pgprot(_PAGE_CACHE_MODE_WC),
					       __pgprot(_PAGE_CACHE_MASK),
					       0, 0, NULL);
	}
	return ret;
}