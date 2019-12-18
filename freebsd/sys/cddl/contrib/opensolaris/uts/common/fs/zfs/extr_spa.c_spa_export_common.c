#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int spa_state; scalar_t__ spa_inject_ref; scalar_t__ spa_config; int /*<<< orphan*/ * spa_root_vdev; scalar_t__ spa_final_txg; int /*<<< orphan*/  spa_dsl_pool; scalar_t__ spa_sync_on; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  EROFS ; 
 int /*<<< orphan*/  ESC_ZFS_POOL_DESTROY ; 
 int /*<<< orphan*/  EXDEV ; 
 int /*<<< orphan*/  FTAG ; 
 int FWRITE ; 
 int POOL_STATE_EXPORTED ; 
 int POOL_STATE_UNINITIALIZED ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_ALL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ TXG_DEFER_SIZE ; 
 int /*<<< orphan*/  VDEV_INITIALIZE_ACTIVE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_dup (scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_async_resume (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_async_suspend (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_deactivate (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_event_notify (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_evicting_os_wait (TYPE_1__*) ; 
 scalar_t__ spa_has_active_shared_spare (TYPE_1__*) ; 
 scalar_t__ spa_last_synced_txg (TYPE_1__*) ; 
 TYPE_1__* spa_lookup (char*) ; 
 int spa_mode_global ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  spa_open_ref (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_refcount_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_unload (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_write_cachefile (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_config_dirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_initialize_stop_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spa_export_common(char *pool, int new_state, nvlist_t **oldconfig,
    boolean_t force, boolean_t hardforce)
{
	spa_t *spa;

	if (oldconfig)
		*oldconfig = NULL;

	if (!(spa_mode_global & FWRITE))
		return (SET_ERROR(EROFS));

	mutex_enter(&spa_namespace_lock);
	if ((spa = spa_lookup(pool)) == NULL) {
		mutex_exit(&spa_namespace_lock);
		return (SET_ERROR(ENOENT));
	}

	/*
	 * Put a hold on the pool, drop the namespace lock, stop async tasks,
	 * reacquire the namespace lock, and see if we can export.
	 */
	spa_open_ref(spa, FTAG);
	mutex_exit(&spa_namespace_lock);
	spa_async_suspend(spa);
	mutex_enter(&spa_namespace_lock);
	spa_close(spa, FTAG);

	/*
	 * The pool will be in core if it's openable,
	 * in which case we can modify its state.
	 */
	if (spa->spa_state != POOL_STATE_UNINITIALIZED && spa->spa_sync_on) {

		/*
		 * Objsets may be open only because they're dirty, so we
		 * have to force it to sync before checking spa_refcnt.
		 */
		txg_wait_synced(spa->spa_dsl_pool, 0);
		spa_evicting_os_wait(spa);

		/*
		 * A pool cannot be exported or destroyed if there are active
		 * references.  If we are resetting a pool, allow references by
		 * fault injection handlers.
		 */
		if (!spa_refcount_zero(spa) ||
		    (spa->spa_inject_ref != 0 &&
		    new_state != POOL_STATE_UNINITIALIZED)) {
			spa_async_resume(spa);
			mutex_exit(&spa_namespace_lock);
			return (SET_ERROR(EBUSY));
		}

		/*
		 * A pool cannot be exported if it has an active shared spare.
		 * This is to prevent other pools stealing the active spare
		 * from an exported pool. At user's own will, such pool can
		 * be forcedly exported.
		 */
		if (!force && new_state == POOL_STATE_EXPORTED &&
		    spa_has_active_shared_spare(spa)) {
			spa_async_resume(spa);
			mutex_exit(&spa_namespace_lock);
			return (SET_ERROR(EXDEV));
		}

		/*
		 * We're about to export or destroy this pool. Make sure
		 * we stop all initializtion activity here before we
		 * set the spa_final_txg. This will ensure that all
		 * dirty data resulting from the initialization is
		 * committed to disk before we unload the pool.
		 */
		if (spa->spa_root_vdev != NULL) {
			vdev_initialize_stop_all(spa->spa_root_vdev,
			    VDEV_INITIALIZE_ACTIVE);
		}

		/*
		 * We want this to be reflected on every label,
		 * so mark them all dirty.  spa_unload() will do the
		 * final sync that pushes these changes out.
		 */
		if (new_state != POOL_STATE_UNINITIALIZED && !hardforce) {
			spa_config_enter(spa, SCL_ALL, FTAG, RW_WRITER);
			spa->spa_state = new_state;
			spa->spa_final_txg = spa_last_synced_txg(spa) +
			    TXG_DEFER_SIZE + 1;
			vdev_config_dirty(spa->spa_root_vdev);
			spa_config_exit(spa, SCL_ALL, FTAG);
		}
	}

	spa_event_notify(spa, NULL, NULL, ESC_ZFS_POOL_DESTROY);

	if (spa->spa_state != POOL_STATE_UNINITIALIZED) {
		spa_unload(spa);
		spa_deactivate(spa);
	}

	if (oldconfig && spa->spa_config)
		VERIFY(nvlist_dup(spa->spa_config, oldconfig, 0) == 0);

	if (new_state != POOL_STATE_UNINITIALIZED) {
		if (!hardforce)
			spa_write_cachefile(spa, B_TRUE, B_TRUE);
		spa_remove(spa);
	}
	mutex_exit(&spa_namespace_lock);

	return (0);
}