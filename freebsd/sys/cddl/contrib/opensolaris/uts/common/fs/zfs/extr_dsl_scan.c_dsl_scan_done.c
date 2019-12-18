#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  spa_root_vdev; void* spa_scrub_active; void* spa_scrub_started; } ;
typedef  TYPE_2__ spa_t ;
struct TYPE_23__ {scalar_t__ scn_queue_obj; int /*<<< orphan*/  scn_end_time; scalar_t__ scn_min_txg; int /*<<< orphan*/  scn_max_txg; int /*<<< orphan*/  scn_state; int /*<<< orphan*/  scn_flags; } ;
struct TYPE_25__ {TYPE_1__ scn_phys; int /*<<< orphan*/ * scn_taskq; void* scn_is_sorted; TYPE_4__* scn_dp; } ;
typedef  TYPE_3__ dsl_scan_t ;
struct TYPE_26__ {int /*<<< orphan*/  dp_meta_objset; TYPE_2__* dp_spa; } ;
typedef  TYPE_4__ dsl_pool_t ;
struct TYPE_27__ {int /*<<< orphan*/  tx_txg; } ;
typedef  TYPE_5__ dmu_tx_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 void* B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  DSF_SCRUB_PAUSED ; 
 scalar_t__ DSL_SCAN_IS_SCRUB_RESILVER (TYPE_3__*) ; 
 int /*<<< orphan*/  DSS_CANCELED ; 
 int /*<<< orphan*/  DSS_FINISHED ; 
 int /*<<< orphan*/  ESC_ZFS_RESILVER_FINISH ; 
 int /*<<< orphan*/  ESC_ZFS_SCRUB_FINISH ; 
 int /*<<< orphan*/  SPA_ASYNC_RESILVER_DONE ; 
 int /*<<< orphan*/  SPA_FEATURE_POOL_CHECKPOINT ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_object_free (int /*<<< orphan*/ ,scalar_t__,TYPE_5__*) ; 
 int /*<<< orphan*/  dsl_scan_is_running (TYPE_3__*) ; 
 scalar_t__ dsl_scan_restarting (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  gethrestime_sec () ; 
 int /*<<< orphan*/  scan_ds_queue_clear (TYPE_3__*) ; 
 int /*<<< orphan*/  scan_io_queues_destroy (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_async_request (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_errlog_rotate (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_event_notify (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_feature_is_active (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_get_errlog_size (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_history_log_internal (TYPE_2__*,char*,TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskq_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_dtl_reassess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,TYPE_5__*) ; 

__attribute__((used)) static void
dsl_scan_done(dsl_scan_t *scn, boolean_t complete, dmu_tx_t *tx)
{
	static const char *old_names[] = {
		"scrub_bookmark",
		"scrub_ddt_bookmark",
		"scrub_ddt_class_max",
		"scrub_queue",
		"scrub_min_txg",
		"scrub_max_txg",
		"scrub_func",
		"scrub_errors",
		NULL
	};

	dsl_pool_t *dp = scn->scn_dp;
	spa_t *spa = dp->dp_spa;
	int i;

	/* Remove any remnants of an old-style scrub. */
	for (i = 0; old_names[i]; i++) {
		(void) zap_remove(dp->dp_meta_objset,
		    DMU_POOL_DIRECTORY_OBJECT, old_names[i], tx);
	}

	if (scn->scn_phys.scn_queue_obj != 0) {
		VERIFY0(dmu_object_free(dp->dp_meta_objset,
		    scn->scn_phys.scn_queue_obj, tx));
		scn->scn_phys.scn_queue_obj = 0;
	}
	scan_ds_queue_clear(scn);

	scn->scn_phys.scn_flags &= ~DSF_SCRUB_PAUSED;

	/*
	 * If we were "restarted" from a stopped state, don't bother
	 * with anything else.
	 */
	if (!dsl_scan_is_running(scn)) {
		ASSERT(!scn->scn_is_sorted);
		return;
	}

	if (scn->scn_is_sorted) {
		scan_io_queues_destroy(scn);
		scn->scn_is_sorted = B_FALSE;

		if (scn->scn_taskq != NULL) {
			taskq_destroy(scn->scn_taskq);
			scn->scn_taskq = NULL;
		}
	}

	scn->scn_phys.scn_state = complete ? DSS_FINISHED : DSS_CANCELED;

	if (dsl_scan_restarting(scn, tx))
		spa_history_log_internal(spa, "scan aborted, restarting", tx,
		    "errors=%llu", spa_get_errlog_size(spa));
	else if (!complete)
		spa_history_log_internal(spa, "scan cancelled", tx,
		    "errors=%llu", spa_get_errlog_size(spa));
	else
		spa_history_log_internal(spa, "scan done", tx,
		    "errors=%llu", spa_get_errlog_size(spa));

	if (DSL_SCAN_IS_SCRUB_RESILVER(scn)) {
		spa->spa_scrub_started = B_FALSE;
		spa->spa_scrub_active = B_FALSE;

		/*
		 * If the scrub/resilver completed, update all DTLs to
		 * reflect this.  Whether it succeeded or not, vacate
		 * all temporary scrub DTLs.
		 *
		 * As the scrub does not currently support traversing
		 * data that have been freed but are part of a checkpoint,
		 * we don't mark the scrub as done in the DTLs as faults
		 * may still exist in those vdevs.
		 */
		if (complete &&
		    !spa_feature_is_active(spa, SPA_FEATURE_POOL_CHECKPOINT)) {
			vdev_dtl_reassess(spa->spa_root_vdev, tx->tx_txg,
			    scn->scn_phys.scn_max_txg, B_TRUE);

			spa_event_notify(spa, NULL, NULL,
			    scn->scn_phys.scn_min_txg ?
			    ESC_ZFS_RESILVER_FINISH : ESC_ZFS_SCRUB_FINISH);
		} else {
			vdev_dtl_reassess(spa->spa_root_vdev, tx->tx_txg,
			    0, B_TRUE);
		}
		spa_errlog_rotate(spa);

		/*
		 * We may have finished replacing a device.
		 * Let the async thread assess this and handle the detach.
		 */
		spa_async_request(spa, SPA_ASYNC_RESILVER_DONE);
	}

	scn->scn_phys.scn_end_time = gethrestime_sec();

	ASSERT(!dsl_scan_is_running(scn));
}