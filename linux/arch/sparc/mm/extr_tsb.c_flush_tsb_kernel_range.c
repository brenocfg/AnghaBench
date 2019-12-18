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
struct tsb {unsigned long tag; } ;

/* Variables and functions */
 int KERNEL_TSB_NENTRIES ; 
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned long TSB_TAG_INVALID_BIT ; 
 void flush_tsb_kernel_range_scan (unsigned long,unsigned long) ; 
 struct tsb* swapper_tsb ; 
 scalar_t__ tag_compare (unsigned long,unsigned long) ; 
 unsigned long tsb_hash (unsigned long,int,int) ; 

void flush_tsb_kernel_range(unsigned long start, unsigned long end)
{
	unsigned long v;

	if ((end - start) >> PAGE_SHIFT >= 2 * KERNEL_TSB_NENTRIES)
		return flush_tsb_kernel_range_scan(start, end);

	for (v = start; v < end; v += PAGE_SIZE) {
		unsigned long hash = tsb_hash(v, PAGE_SHIFT,
					      KERNEL_TSB_NENTRIES);
		struct tsb *ent = &swapper_tsb[hash];

		if (tag_compare(ent->tag, v))
			ent->tag = (1UL << TSB_TAG_INVALID_BIT);
	}
}