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
typedef  unsigned long long uint64_t ;
struct TYPE_5__ {unsigned long long rs_end; unsigned long long rs_start; } ;
typedef  TYPE_1__ range_seg_t ;
struct TYPE_6__ {int /*<<< orphan*/  ms_allocatable_by_size; } ;
typedef  TYPE_2__ metaslab_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 TYPE_1__* avl_last (int /*<<< orphan*/ *) ; 

uint64_t
metaslab_block_maxsize(metaslab_t *msp)
{
	avl_tree_t *t = &msp->ms_allocatable_by_size;
	range_seg_t *rs;

	if (t == NULL || (rs = avl_last(t)) == NULL)
		return (0ULL);

	return (rs->rs_end - rs->rs_start);
}