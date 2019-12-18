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
struct vm_page {int dummy; } ;
struct ttm_mem_zone {int dummy; } ;
struct ttm_mem_global {struct ttm_mem_zone* zone_kernel; scalar_t__ zone_dma32; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int page_to_pfn (struct vm_page*) ; 
 int /*<<< orphan*/  ttm_mem_global_free_zone (struct ttm_mem_global*,struct ttm_mem_zone*,int /*<<< orphan*/ ) ; 

void ttm_mem_global_free_page(struct ttm_mem_global *glob, struct vm_page *page)
{
	struct ttm_mem_zone *zone = NULL;

	if (glob->zone_dma32 && page_to_pfn(page) > 0x00100000UL)
		zone = glob->zone_kernel;
	ttm_mem_global_free_zone(glob, zone, PAGE_SIZE);
}