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
 int /*<<< orphan*/  SYNCER_RUNNING ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int first_printf ; 
 int /*<<< orphan*/  kproc_resume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_mtx ; 
 int /*<<< orphan*/  sync_wakeup ; 
 int /*<<< orphan*/  syncer_state ; 
 int /*<<< orphan*/  updateproc ; 

void
syncer_resume(void)
{

	mtx_lock(&sync_mtx);
	first_printf = 1;
	syncer_state = SYNCER_RUNNING;
	mtx_unlock(&sync_mtx);
	cv_broadcast(&sync_wakeup);
	kproc_resume(updateproc);
}