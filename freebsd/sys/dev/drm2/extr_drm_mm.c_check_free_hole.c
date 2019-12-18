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

__attribute__((used)) static int check_free_hole(unsigned long start, unsigned long end,
			   unsigned long size, unsigned alignment)
{
	if (end - start < size)
		return 0;

	if (alignment) {
		unsigned tmp = start % alignment;
		if (tmp)
			start += alignment - tmp;
	}

	return end >= start + size;
}