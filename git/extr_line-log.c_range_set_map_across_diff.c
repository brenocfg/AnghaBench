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
struct range_set {int dummy; } ;
struct diff_ranges {int /*<<< orphan*/  parent; int /*<<< orphan*/  target; } ;

/* Variables and functions */
 struct range_set RANGE_SET_INIT ; 
 int /*<<< orphan*/  diff_ranges_filter_touched (struct diff_ranges*,struct diff_ranges*,struct range_set*) ; 
 int /*<<< orphan*/  diff_ranges_init (struct diff_ranges*) ; 
 int /*<<< orphan*/  range_set_difference (struct range_set*,struct range_set*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_set_release (struct range_set*) ; 
 int /*<<< orphan*/  range_set_shift_diff (struct range_set*,struct range_set*,struct diff_ranges*) ; 
 int /*<<< orphan*/  range_set_union (struct range_set*,struct range_set*,int /*<<< orphan*/ *) ; 
 struct diff_ranges* xmalloc (int) ; 

__attribute__((used)) static void range_set_map_across_diff(struct range_set *out,
				      struct range_set *rs,
				      struct diff_ranges *diff,
				      struct diff_ranges **touched_out)
{
	struct diff_ranges *touched = xmalloc(sizeof(*touched));
	struct range_set tmp1 = RANGE_SET_INIT;
	struct range_set tmp2 = RANGE_SET_INIT;

	diff_ranges_init(touched);
	diff_ranges_filter_touched(touched, diff, rs);
	range_set_difference(&tmp1, rs, &touched->target);
	range_set_shift_diff(&tmp2, &tmp1, diff);
	range_set_union(out, &tmp2, &touched->parent);
	range_set_release(&tmp1);
	range_set_release(&tmp2);

	*touched_out = touched;
}