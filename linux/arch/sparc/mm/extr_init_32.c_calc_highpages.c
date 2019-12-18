#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long num_bytes; unsigned long base_addr; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 unsigned long max_low_pfn ; 
 TYPE_1__* sp_banks ; 

unsigned long calc_highpages(void)
{
	int i;
	int nr = 0;

	for (i = 0; sp_banks[i].num_bytes != 0; i++) {
		unsigned long start_pfn = sp_banks[i].base_addr >> PAGE_SHIFT;
		unsigned long end_pfn = (sp_banks[i].base_addr + sp_banks[i].num_bytes) >> PAGE_SHIFT;

		if (end_pfn <= max_low_pfn)
			continue;

		if (start_pfn < max_low_pfn)
			start_pfn = max_low_pfn;

		nr += end_pfn - start_pfn;
	}

	return nr;
}