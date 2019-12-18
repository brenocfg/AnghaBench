#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ms_initializing; int /*<<< orphan*/  ms_lock; TYPE_2__* ms_group; } ;
typedef  TYPE_1__ metaslab_t ;
struct TYPE_5__ {int /*<<< orphan*/  mg_ms_initialize_lock; int /*<<< orphan*/  mg_ms_initialize_cv; int /*<<< orphan*/  mg_ms_initializing; } ;
typedef  TYPE_2__ metaslab_group_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vdev_initialize_ms_unmark(metaslab_t *msp)
{
	ASSERT(!MUTEX_HELD(&msp->ms_lock));
	metaslab_group_t *mg = msp->ms_group;
	mutex_enter(&mg->mg_ms_initialize_lock);
	mutex_enter(&msp->ms_lock);
	if (--msp->ms_initializing == 0) {
		mg->mg_ms_initializing--;
		cv_broadcast(&mg->mg_ms_initialize_cv);
	}
	mutex_exit(&msp->ms_lock);
	mutex_exit(&mg->mg_ms_initialize_lock);
}