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
struct resource {int flags; int start; int end; } ;

/* Variables and functions */
 int IORESOURCE_SYSTEM_RAM ; 
 unsigned int IORES_MAP_SYSTEM_RAM ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PageReserved (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_to_page (unsigned long) ; 
 scalar_t__ pfn_valid (unsigned long) ; 

__attribute__((used)) static unsigned int __ioremap_check_ram(struct resource *res)
{
	unsigned long start_pfn, stop_pfn;
	unsigned long i;

	if ((res->flags & IORESOURCE_SYSTEM_RAM) != IORESOURCE_SYSTEM_RAM)
		return 0;

	start_pfn = (res->start + PAGE_SIZE - 1) >> PAGE_SHIFT;
	stop_pfn = (res->end + 1) >> PAGE_SHIFT;
	if (stop_pfn > start_pfn) {
		for (i = 0; i < (stop_pfn - start_pfn); ++i)
			if (pfn_valid(start_pfn + i) &&
			    !PageReserved(pfn_to_page(start_pfn + i)))
				return IORES_MAP_SYSTEM_RAM;
	}

	return 0;
}