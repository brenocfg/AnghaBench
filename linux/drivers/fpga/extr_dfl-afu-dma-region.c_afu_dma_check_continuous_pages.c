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
struct dfl_afu_dma_region {int length; int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 scalar_t__ page_to_pfn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool afu_dma_check_continuous_pages(struct dfl_afu_dma_region *region)
{
	int npages = region->length >> PAGE_SHIFT;
	int i;

	for (i = 0; i < npages - 1; i++)
		if (page_to_pfn(region->pages[i]) + 1 !=
				page_to_pfn(region->pages[i + 1]))
			return false;

	return true;
}