#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ off_t ;
struct TYPE_3__ {scalar_t__ ds_len; scalar_t__ ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 uintptr_t PAGE_SHIFT ; 
 uintptr_t round_page (scalar_t__) ; 
 uintptr_t trunc_page (scalar_t__) ; 

__attribute__((used)) static void
g_disk_seg_limit(bus_dma_segment_t *seg, off_t *poffset,
    off_t *plength, int *ppages)
{
	uintptr_t seg_page_base;
	uintptr_t seg_page_end;
	off_t offset;
	off_t length;
	int seg_pages;

	offset = *poffset;
	length = *plength;

	if (length > seg->ds_len - offset)
		length = seg->ds_len - offset;

	seg_page_base = trunc_page(seg->ds_addr + offset);
	seg_page_end  = round_page(seg->ds_addr + offset + length);
	seg_pages = (seg_page_end - seg_page_base) >> PAGE_SHIFT;

	if (seg_pages > *ppages) {
		seg_pages = *ppages;
		length = (seg_page_base + (seg_pages << PAGE_SHIFT)) -
		    (seg->ds_addr + offset);
	}

	*poffset = 0;
	*plength -= length;
	*ppages -= seg_pages;
}