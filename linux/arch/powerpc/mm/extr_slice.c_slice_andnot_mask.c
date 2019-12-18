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
struct slice_mask {int low_slices; int /*<<< orphan*/  high_slices; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLICE_NUM_HIGH ; 
 int /*<<< orphan*/  bitmap_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void slice_andnot_mask(struct slice_mask *dst,
					const struct slice_mask *src1,
					const struct slice_mask *src2)
{
	dst->low_slices = src1->low_slices & ~src2->low_slices;
	if (!SLICE_NUM_HIGH)
		return;
	bitmap_andnot(dst->high_slices, src1->high_slices, src2->high_slices, SLICE_NUM_HIGH);
}