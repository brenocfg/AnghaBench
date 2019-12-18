#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int RB_NOSYNC ; 
 int /*<<< orphan*/  SYNCER_SHUTTING_DOWN ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kproc_shutdown (void*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rushjob ; 
 int /*<<< orphan*/  sync_mtx ; 
 int /*<<< orphan*/  sync_wakeup ; 
 int /*<<< orphan*/  syncer_state ; 

__attribute__((used)) static void
syncer_shutdown(void *arg, int howto)
{

	if (howto & RB_NOSYNC)
		return;
	mtx_lock(&sync_mtx);
	syncer_state = SYNCER_SHUTTING_DOWN;
	rushjob = 0;
	mtx_unlock(&sync_mtx);
	cv_broadcast(&sync_wakeup);
	kproc_shutdown(arg, howto);
}