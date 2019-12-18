#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_14__ {int spa_async_tasks; int /*<<< orphan*/  spa_async_lock; int /*<<< orphan*/  spa_async_cv; int /*<<< orphan*/ * spa_async_thread; int /*<<< orphan*/  spa_root_vdev; int /*<<< orphan*/  spa_dsl_pool; int /*<<< orphan*/  spa_sync_on; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_CONFIG ; 
 int /*<<< orphan*/  SCL_NONE ; 
 int SPA_ASYNC_AUTOEXPAND ; 
 int SPA_ASYNC_CONFIG_UPDATE ; 
 int SPA_ASYNC_INITIALIZE_RESTART ; 
 int SPA_ASYNC_PROBE ; 
 int SPA_ASYNC_REMOVE ; 
 int SPA_ASYNC_RESILVER ; 
 int SPA_ASYNC_RESILVER_DONE ; 
 int /*<<< orphan*/  SPA_CONFIG_UPDATE_POOL ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_resilver_restart (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ metaslab_class_get_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_async_autoexpand (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_async_probe (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_update (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_history_log_internal (TYPE_1__*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spa_name (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  spa_normal_class (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_suspended (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_vdev_resilver_done (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_vdev_state_enter (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_vdev_state_exit (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_exit () ; 
 int /*<<< orphan*/  vdev_initialize_restart (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spa_async_thread(void *arg)
{
	spa_t *spa = (spa_t *)arg;
	int tasks;

	ASSERT(spa->spa_sync_on);

	mutex_enter(&spa->spa_async_lock);
	tasks = spa->spa_async_tasks;
	spa->spa_async_tasks &= SPA_ASYNC_REMOVE;
	mutex_exit(&spa->spa_async_lock);

	/*
	 * See if the config needs to be updated.
	 */
	if (tasks & SPA_ASYNC_CONFIG_UPDATE) {
		uint64_t old_space, new_space;

		mutex_enter(&spa_namespace_lock);
		old_space = metaslab_class_get_space(spa_normal_class(spa));
		spa_config_update(spa, SPA_CONFIG_UPDATE_POOL);
		new_space = metaslab_class_get_space(spa_normal_class(spa));
		mutex_exit(&spa_namespace_lock);

		/*
		 * If the pool grew as a result of the config update,
		 * then log an internal history event.
		 */
		if (new_space != old_space) {
			spa_history_log_internal(spa, "vdev online", NULL,
			    "pool '%s' size: %llu(+%llu)",
			    spa_name(spa), new_space, new_space - old_space);
		}
	}

	if ((tasks & SPA_ASYNC_AUTOEXPAND) && !spa_suspended(spa)) {
		spa_config_enter(spa, SCL_CONFIG, FTAG, RW_READER);
		spa_async_autoexpand(spa, spa->spa_root_vdev);
		spa_config_exit(spa, SCL_CONFIG, FTAG);
	}

	/*
	 * See if any devices need to be probed.
	 */
	if (tasks & SPA_ASYNC_PROBE) {
		spa_vdev_state_enter(spa, SCL_NONE);
		spa_async_probe(spa, spa->spa_root_vdev);
		(void) spa_vdev_state_exit(spa, NULL, 0);
	}

	/*
	 * If any devices are done replacing, detach them.
	 */
	if (tasks & SPA_ASYNC_RESILVER_DONE)
		spa_vdev_resilver_done(spa);

	/*
	 * Kick off a resilver.
	 */
	if (tasks & SPA_ASYNC_RESILVER)
		dsl_resilver_restart(spa->spa_dsl_pool, 0);

	if (tasks & SPA_ASYNC_INITIALIZE_RESTART) {
		mutex_enter(&spa_namespace_lock);
		spa_config_enter(spa, SCL_CONFIG, FTAG, RW_READER);
		vdev_initialize_restart(spa->spa_root_vdev);
		spa_config_exit(spa, SCL_CONFIG, FTAG);
		mutex_exit(&spa_namespace_lock);
	}

	/*
	 * Let the world know that we're done.
	 */
	mutex_enter(&spa->spa_async_lock);
	spa->spa_async_thread = NULL;
	cv_broadcast(&spa->spa_async_cv);
	mutex_exit(&spa->spa_async_lock);
	thread_exit();
}