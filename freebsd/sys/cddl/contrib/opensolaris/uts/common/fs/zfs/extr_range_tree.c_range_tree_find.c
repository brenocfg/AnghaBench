#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  range_tree_t ;
struct TYPE_4__ {scalar_t__ rs_start; scalar_t__ rs_end; } ;
typedef  TYPE_1__ range_seg_t ;

/* Variables and functions */
 TYPE_1__* range_tree_find_impl (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

range_seg_t *
range_tree_find(range_tree_t *rt, uint64_t start, uint64_t size)
{
	range_seg_t *rs = range_tree_find_impl(rt, start, size);
	if (rs != NULL && rs->rs_start <= start && rs->rs_end >= start + size)
		return (rs);
	return (NULL);
}