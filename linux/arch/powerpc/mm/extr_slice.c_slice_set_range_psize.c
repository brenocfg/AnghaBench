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
struct slice_mask {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_enabled () ; 
 int /*<<< orphan*/  slice_convert (struct mm_struct*,struct slice_mask*,unsigned int) ; 
 int /*<<< orphan*/  slice_range_to_mask (unsigned long,unsigned long,struct slice_mask*) ; 

void slice_set_range_psize(struct mm_struct *mm, unsigned long start,
			   unsigned long len, unsigned int psize)
{
	struct slice_mask mask;

	VM_BUG_ON(radix_enabled());

	slice_range_to_mask(start, len, &mask);
	slice_convert(mm, &mask, psize);
}