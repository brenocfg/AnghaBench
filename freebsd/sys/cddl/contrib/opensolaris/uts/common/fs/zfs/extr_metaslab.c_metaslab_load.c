#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ms_load_cv; scalar_t__ ms_loading; scalar_t__ ms_loaded; int /*<<< orphan*/  ms_lock; } ;
typedef  TYPE_1__ metaslab_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int metaslab_load_impl (TYPE_1__*) ; 
 int /*<<< orphan*/  metaslab_load_wait (TYPE_1__*) ; 

int
metaslab_load(metaslab_t *msp)
{
	ASSERT(MUTEX_HELD(&msp->ms_lock));

	/*
	 * There may be another thread loading the same metaslab, if that's
	 * the case just wait until the other thread is done and return.
	 */
	metaslab_load_wait(msp);
	if (msp->ms_loaded)
		return (0);
	VERIFY(!msp->ms_loading);

	msp->ms_loading = B_TRUE;
	int error = metaslab_load_impl(msp);
	msp->ms_loading = B_FALSE;
	cv_broadcast(&msp->ms_load_cv);

	return (error);
}