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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  ms_weight; TYPE_2__* ms_group; } ;
typedef  TYPE_1__ metaslab_t ;
struct TYPE_8__ {int /*<<< orphan*/  mg_metaslab_tree; int /*<<< orphan*/  mg_lock; } ;
typedef  TYPE_2__ metaslab_group_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  avl_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
metaslab_group_sort_impl(metaslab_group_t *mg, metaslab_t *msp, uint64_t weight)
{
	ASSERT(MUTEX_HELD(&mg->mg_lock));
	ASSERT(msp->ms_group == mg);
	avl_remove(&mg->mg_metaslab_tree, msp);
	msp->ms_weight = weight;
	avl_add(&mg->mg_metaslab_tree, msp);

}