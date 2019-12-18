#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mtrr_iter {scalar_t__ index; scalar_t__ end; int fixed; int /*<<< orphan*/  seg; TYPE_1__* mtrr_state; int /*<<< orphan*/ * range; } ;
struct TYPE_2__ {int /*<<< orphan*/  fixed_ranges; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ fixed_mtrr_range_end_addr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ fixed_mtrr_seg_end_range_index (int /*<<< orphan*/ ) ; 
 void mtrr_lookup_var_start (struct mtrr_iter*) ; 

__attribute__((used)) static void mtrr_lookup_fixed_next(struct mtrr_iter *iter)
{
	/* terminate the lookup. */
	if (fixed_mtrr_range_end_addr(iter->seg, iter->index) >= iter->end) {
		iter->fixed = false;
		iter->range = NULL;
		return;
	}

	iter->index++;

	/* have looked up for all fixed MTRRs. */
	if (iter->index >= ARRAY_SIZE(iter->mtrr_state->fixed_ranges))
		return mtrr_lookup_var_start(iter);

	/* switch to next segment. */
	if (iter->index > fixed_mtrr_seg_end_range_index(iter->seg))
		iter->seg++;
}