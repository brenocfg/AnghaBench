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
typedef  enum page_cache_mode { ____Placeholder_page_cache_mode } page_cache_mode ;

/* Variables and functions */
 int /*<<< orphan*/  PFN_PHYS (unsigned long) ; 
 int _PAGE_CACHE_MODE_UC ; 
 int _PAGE_CACHE_MODE_UC_MINUS ; 
 int _PAGE_CACHE_MODE_WC ; 
 int lookup_memtype (int /*<<< orphan*/ ) ; 

bool pat_pfn_immune_to_uc_mtrr(unsigned long pfn)
{
	enum page_cache_mode cm = lookup_memtype(PFN_PHYS(pfn));

	return cm == _PAGE_CACHE_MODE_UC ||
	       cm == _PAGE_CACHE_MODE_UC_MINUS ||
	       cm == _PAGE_CACHE_MODE_WC;
}