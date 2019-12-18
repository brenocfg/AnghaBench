#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ms_initializing; int /*<<< orphan*/  ms_lock; TYPE_2__* ms_group; } ;
typedef  TYPE_1__ metaslab_t ;
struct TYPE_7__ {int /*<<< orphan*/  mg_ms_initialize_lock; int /*<<< orphan*/  mg_ms_initialize_cv; int /*<<< orphan*/  mg_initialize_updating; } ;
typedef  TYPE_2__ metaslab_group_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_initialize_mg_mark (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_initialize_mg_wait (TYPE_2__*) ; 

__attribute__((used)) static void
vdev_initialize_ms_mark(metaslab_t *msp)
{
	ASSERT(!MUTEX_HELD(&msp->ms_lock));
	metaslab_group_t *mg = msp->ms_group;

	mutex_enter(&mg->mg_ms_initialize_lock);

	/*
	 * To keep an accurate count of how many threads are initializing
	 * a specific metaslab group, we only allow one thread to mark
	 * the metaslab group at a time. This ensures that the value of
	 * ms_initializing will be accurate when we decide to mark a metaslab
	 * group as being initialized. To do this we force all other threads
	 * to wait till the metaslab's mg_initialize_updating flag is no
	 * longer set.
	 */
	vdev_initialize_mg_wait(mg);
	mg->mg_initialize_updating = B_TRUE;
	if (msp->ms_initializing == 0) {
		vdev_initialize_mg_mark(mg);
	}
	mutex_enter(&msp->ms_lock);
	msp->ms_initializing++;
	mutex_exit(&msp->ms_lock);

	mg->mg_initialize_updating = B_FALSE;
	cv_broadcast(&mg->mg_ms_initialize_cv);
	mutex_exit(&mg->mg_ms_initialize_lock);
}