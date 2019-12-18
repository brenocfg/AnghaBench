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
typedef  size_t uint32_t ;
struct island_bitmap {int* bits; } ;

/* Variables and functions */
 size_t island_bitmap_size ; 

__attribute__((used)) static int island_bitmap_is_subset(struct island_bitmap *self,
		struct island_bitmap *super)
{
	uint32_t i;

	if (self == super)
		return 1;

	for (i = 0; i < island_bitmap_size; ++i) {
		if ((self->bits[i] & super->bits[i]) != self->bits[i])
			return 0;
	}

	return 1;
}