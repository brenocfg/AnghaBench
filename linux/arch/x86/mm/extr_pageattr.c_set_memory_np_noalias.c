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
 int CPA_NO_CHECK_ALIAS ; 
 int /*<<< orphan*/  _PAGE_PRESENT ; 
 int /*<<< orphan*/  __pgprot (int /*<<< orphan*/ ) ; 
 int change_page_attr_set_clr (unsigned long*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int set_memory_np_noalias(unsigned long addr, int numpages)
{
	int cpa_flags = CPA_NO_CHECK_ALIAS;

	return change_page_attr_set_clr(&addr, numpages, __pgprot(0),
					__pgprot(_PAGE_PRESENT), 0,
					cpa_flags, NULL);
}