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
struct island_bitmap {int /*<<< orphan*/ * bits; } ;

/* Variables and functions */
 size_t island_bitmap_size ; 

__attribute__((used)) static void island_bitmap_or(struct island_bitmap *a, const struct island_bitmap *b)
{
	uint32_t i;

	for (i = 0; i < island_bitmap_size; ++i)
		a->bits[i] |= b->bits[i];
}