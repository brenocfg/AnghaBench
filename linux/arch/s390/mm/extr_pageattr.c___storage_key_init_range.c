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
 scalar_t__ MACHINE_HAS_EDAT1 ; 
 int /*<<< orphan*/  PAGE_DEFAULT_KEY ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  page_set_storage_key (unsigned long,int /*<<< orphan*/ ,int) ; 
 unsigned long sske_frame (unsigned long,int /*<<< orphan*/ ) ; 

void __storage_key_init_range(unsigned long start, unsigned long end)
{
	unsigned long boundary, size;

	while (start < end) {
		if (MACHINE_HAS_EDAT1) {
			/* set storage keys for a 1MB frame */
			size = 1UL << 20;
			boundary = (start + size) & ~(size - 1);
			if (boundary <= end) {
				do {
					start = sske_frame(start, PAGE_DEFAULT_KEY);
				} while (start < boundary);
				continue;
			}
		}
		page_set_storage_key(start, PAGE_DEFAULT_KEY, 1);
		start += PAGE_SIZE;
	}
}