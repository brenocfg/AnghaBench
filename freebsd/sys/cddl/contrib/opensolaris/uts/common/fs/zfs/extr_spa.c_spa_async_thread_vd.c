#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int sav_count; int /*<<< orphan*/ * sav_vdevs; } ;
struct TYPE_7__ {int sav_count; int /*<<< orphan*/ * sav_vdevs; } ;
struct TYPE_9__ {int spa_async_tasks; int /*<<< orphan*/  spa_async_lock; int /*<<< orphan*/  spa_async_cv; int /*<<< orphan*/ * spa_async_thread_vd; TYPE_2__ spa_spares; TYPE_1__ spa_l2cache; int /*<<< orphan*/  spa_root_vdev; } ;
typedef  TYPE_3__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCL_NONE ; 
 int SPA_ASYNC_REMOVE ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_async_remove (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_vdev_state_enter (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_vdev_state_exit (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_exit () ; 

__attribute__((used)) static void
spa_async_thread_vd(void *arg)
{
	spa_t *spa = arg;
	int tasks;

	mutex_enter(&spa->spa_async_lock);
	tasks = spa->spa_async_tasks;
retry:
	spa->spa_async_tasks &= ~SPA_ASYNC_REMOVE;
	mutex_exit(&spa->spa_async_lock);

	/*
	 * See if any devices need to be marked REMOVED.
	 */
	if (tasks & SPA_ASYNC_REMOVE) {
		spa_vdev_state_enter(spa, SCL_NONE);
		spa_async_remove(spa, spa->spa_root_vdev);
		for (int i = 0; i < spa->spa_l2cache.sav_count; i++)
			spa_async_remove(spa, spa->spa_l2cache.sav_vdevs[i]);
		for (int i = 0; i < spa->spa_spares.sav_count; i++)
			spa_async_remove(spa, spa->spa_spares.sav_vdevs[i]);
		(void) spa_vdev_state_exit(spa, NULL, 0);
	}

	/*
	 * Let the world know that we're done.
	 */
	mutex_enter(&spa->spa_async_lock);
	tasks = spa->spa_async_tasks;
	if ((tasks & SPA_ASYNC_REMOVE) != 0)
		goto retry;
	spa->spa_async_thread_vd = NULL;
	cv_broadcast(&spa->spa_async_cv);
	mutex_exit(&spa->spa_async_lock);
	thread_exit();
}