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
typedef  int /*<<< orphan*/  vm_page_t ;

/* Variables and functions */
 int CPUID_CLFSH ; 
 int PAGE_SIZE ; 
 int PMAP_CLFLUSH_THRESHOLD ; 
 int cpu_feature ; 
 int /*<<< orphan*/  pmap_flush_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_invalidate_cache () ; 

void
pmap_invalidate_cache_pages(vm_page_t *pages, int count)
{
	int i;

	if (count >= PMAP_CLFLUSH_THRESHOLD / PAGE_SIZE ||
	    (cpu_feature & CPUID_CLFSH) == 0) {
		pmap_invalidate_cache();
	} else {
		for (i = 0; i < count; i++)
			pmap_flush_page(pages[i]);
	}
}