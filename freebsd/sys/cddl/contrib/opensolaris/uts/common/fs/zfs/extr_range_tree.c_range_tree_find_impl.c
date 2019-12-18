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
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  rt_root; } ;
typedef  TYPE_1__ range_tree_t ;
struct TYPE_8__ {scalar_t__ rs_end; scalar_t__ rs_start; } ;
typedef  TYPE_2__ range_seg_t ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY (int) ; 
 TYPE_2__* avl_find (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static range_seg_t *
range_tree_find_impl(range_tree_t *rt, uint64_t start, uint64_t size)
{
	range_seg_t rsearch;
	uint64_t end = start + size;

	VERIFY(size != 0);

	rsearch.rs_start = start;
	rsearch.rs_end = end;
	return (avl_find(&rt->rt_root, &rsearch, NULL));
}