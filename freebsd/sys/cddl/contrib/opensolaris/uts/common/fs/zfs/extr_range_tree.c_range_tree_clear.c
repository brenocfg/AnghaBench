#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  range_tree_t ;
struct TYPE_3__ {int /*<<< orphan*/  rs_end; int /*<<< orphan*/  rs_start; } ;
typedef  TYPE_1__ range_seg_t ;

/* Variables and functions */
 scalar_t__ MAX (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ MIN (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* range_tree_find_impl (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  range_tree_remove (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

void
range_tree_clear(range_tree_t *rt, uint64_t start, uint64_t size)
{
	range_seg_t *rs;

	if (size == 0)
		return;

	while ((rs = range_tree_find_impl(rt, start, size)) != NULL) {
		uint64_t free_start = MAX(rs->rs_start, start);
		uint64_t free_end = MIN(rs->rs_end, start + size);
		range_tree_remove(rt, free_start, free_end - free_start);
	}
}