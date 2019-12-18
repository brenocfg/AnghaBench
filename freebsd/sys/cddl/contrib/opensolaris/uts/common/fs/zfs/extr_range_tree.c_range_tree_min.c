#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  rt_root; } ;
typedef  TYPE_1__ range_tree_t ;
struct TYPE_6__ {int /*<<< orphan*/  rs_start; } ;
typedef  TYPE_2__ range_seg_t ;

/* Variables and functions */
 TYPE_2__* avl_first (int /*<<< orphan*/ *) ; 

uint64_t
range_tree_min(range_tree_t *rt)
{
	range_seg_t *rs = avl_first(&rt->rt_root);
	return (rs != NULL ? rs->rs_start : 0);
}