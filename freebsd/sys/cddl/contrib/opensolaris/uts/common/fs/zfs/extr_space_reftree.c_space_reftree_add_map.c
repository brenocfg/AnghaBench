#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  rt_root; } ;
typedef  TYPE_1__ range_tree_t ;
struct TYPE_8__ {int /*<<< orphan*/  rs_end; int /*<<< orphan*/  rs_start; } ;
typedef  TYPE_2__ range_seg_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 TYPE_2__* AVL_NEXT (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* avl_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  space_reftree_add_seg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
space_reftree_add_map(avl_tree_t *t, range_tree_t *rt, int64_t refcnt)
{
	range_seg_t *rs;

	for (rs = avl_first(&rt->rt_root); rs; rs = AVL_NEXT(&rt->rt_root, rs))
		space_reftree_add_seg(t, rs->rs_start, rs->rs_end, refcnt);
}