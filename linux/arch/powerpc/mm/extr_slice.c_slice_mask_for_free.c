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
struct slice_mask {unsigned int low_slices; int /*<<< orphan*/  high_slices; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 unsigned long GET_HIGH_SLICE_INDEX (unsigned long) ; 
 scalar_t__ SLICE_NUM_HIGH ; 
 unsigned long SLICE_NUM_LOW ; 
 int /*<<< orphan*/  __set_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ slice_addr_is_low (unsigned long) ; 
 int /*<<< orphan*/  slice_high_has_vma (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  slice_low_has_vma (struct mm_struct*,unsigned long) ; 

__attribute__((used)) static void slice_mask_for_free(struct mm_struct *mm, struct slice_mask *ret,
				unsigned long high_limit)
{
	unsigned long i;

	ret->low_slices = 0;
	if (SLICE_NUM_HIGH)
		bitmap_zero(ret->high_slices, SLICE_NUM_HIGH);

	for (i = 0; i < SLICE_NUM_LOW; i++)
		if (!slice_low_has_vma(mm, i))
			ret->low_slices |= 1u << i;

	if (slice_addr_is_low(high_limit - 1))
		return;

	for (i = 0; i < GET_HIGH_SLICE_INDEX(high_limit); i++)
		if (!slice_high_has_vma(mm, i))
			__set_bit(i, ret->high_slices);
}