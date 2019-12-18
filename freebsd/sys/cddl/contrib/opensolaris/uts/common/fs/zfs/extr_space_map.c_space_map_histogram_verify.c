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
struct TYPE_5__ {int sm_shift; } ;
typedef  TYPE_1__ space_map_t ;
struct TYPE_6__ {scalar_t__* rt_histogram; } ;
typedef  TYPE_2__ range_tree_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 

boolean_t
space_map_histogram_verify(space_map_t *sm, range_tree_t *rt)
{
	/*
	 * Verify that the in-core range tree does not have any
	 * ranges smaller than our sm_shift size.
	 */
	for (int i = 0; i < sm->sm_shift; i++) {
		if (rt->rt_histogram[i] != 0)
			return (B_FALSE);
	}
	return (B_TRUE);
}