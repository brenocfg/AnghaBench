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
struct mem_vector {unsigned long start; unsigned long size; } ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONFIG_PHYSICAL_ALIGN ; 
 int /*<<< orphan*/  CONFIG_X86_32 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned long KERNEL_IMAGE_SIZE ; 
 scalar_t__ MAX_SLOT_AREA ; 
 int /*<<< orphan*/  mem_avoid_overlap (struct mem_vector*,struct mem_vector*) ; 
 int /*<<< orphan*/  mem_limit ; 
 unsigned long min (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_gb_huge_pages (struct mem_vector*,unsigned long) ; 
 scalar_t__ slot_area_index ; 

__attribute__((used)) static void __process_mem_region(struct mem_vector *entry,
				 unsigned long minimum,
				 unsigned long image_size)
{
	struct mem_vector region, overlap;
	unsigned long start_orig, end;
	struct mem_vector cur_entry;

	/* On 32-bit, ignore entries entirely above our maximum. */
	if (IS_ENABLED(CONFIG_X86_32) && entry->start >= KERNEL_IMAGE_SIZE)
		return;

	/* Ignore entries entirely below our minimum. */
	if (entry->start + entry->size < minimum)
		return;

	/* Ignore entries above memory limit */
	end = min(entry->size + entry->start, mem_limit);
	if (entry->start >= end)
		return;
	cur_entry.start = entry->start;
	cur_entry.size = end - entry->start;

	region.start = cur_entry.start;
	region.size = cur_entry.size;

	/* Give up if slot area array is full. */
	while (slot_area_index < MAX_SLOT_AREA) {
		start_orig = region.start;

		/* Potentially raise address to minimum location. */
		if (region.start < minimum)
			region.start = minimum;

		/* Potentially raise address to meet alignment needs. */
		region.start = ALIGN(region.start, CONFIG_PHYSICAL_ALIGN);

		/* Did we raise the address above the passed in memory entry? */
		if (region.start > cur_entry.start + cur_entry.size)
			return;

		/* Reduce size by any delta from the original address. */
		region.size -= region.start - start_orig;

		/* On 32-bit, reduce region size to fit within max size. */
		if (IS_ENABLED(CONFIG_X86_32) &&
		    region.start + region.size > KERNEL_IMAGE_SIZE)
			region.size = KERNEL_IMAGE_SIZE - region.start;

		/* Return if region can't contain decompressed kernel */
		if (region.size < image_size)
			return;

		/* If nothing overlaps, store the region and return. */
		if (!mem_avoid_overlap(&region, &overlap)) {
			process_gb_huge_pages(&region, image_size);
			return;
		}

		/* Store beginning of region if holds at least image_size. */
		if (overlap.start > region.start + image_size) {
			struct mem_vector beginning;

			beginning.start = region.start;
			beginning.size = overlap.start - region.start;
			process_gb_huge_pages(&beginning, image_size);
		}

		/* Return if overlap extends to or past end of region. */
		if (overlap.start + overlap.size >= region.start + region.size)
			return;

		/* Clip off the overlapping region and start over. */
		region.size -= overlap.start - region.start + overlap.size;
		region.start = overlap.start + overlap.size;
	}
}