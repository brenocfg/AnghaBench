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
 int PAGE_SIZE ; 
 int /*<<< orphan*/  _PAGE_CACHE_MODE_WC ; 
 scalar_t__ __pa (unsigned long) ; 
 int _set_memory_wc (unsigned long,int) ; 
 int /*<<< orphan*/  free_memtype (scalar_t__,scalar_t__) ; 
 int reserve_memtype (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int set_memory_wc(unsigned long addr, int numpages)
{
	int ret;

	ret = reserve_memtype(__pa(addr), __pa(addr) + numpages * PAGE_SIZE,
		_PAGE_CACHE_MODE_WC, NULL);
	if (ret)
		return ret;

	ret = _set_memory_wc(addr, numpages);
	if (ret)
		free_memtype(__pa(addr), __pa(addr) + numpages * PAGE_SIZE);

	return ret;
}