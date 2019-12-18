#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  vdev_scan_io_queue_lock; int /*<<< orphan*/ * vdev_scan_io_queue; } ;
typedef  TYPE_3__ vdev_t ;
typedef  size_t uint64_t ;
struct TYPE_11__ {char* spa_name; TYPE_2__* spa_root_vdev; } ;
typedef  TYPE_4__ spa_t ;
struct TYPE_12__ {scalar_t__ scn_bytes_pending; int /*<<< orphan*/ * scn_taskq; int /*<<< orphan*/  scn_is_sorted; TYPE_1__* scn_dp; } ;
typedef  TYPE_5__ dsl_scan_t ;
struct TYPE_9__ {int vdev_children; TYPE_3__** vdev_child; } ;
struct TYPE_8__ {TYPE_4__* dp_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_CONFIG ; 
 scalar_t__ TASKQID_INVALID ; 
 int /*<<< orphan*/  TASKQ_PREPOPULATE ; 
 int /*<<< orphan*/  TQ_SLEEP ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  kmem_free (char*,scalar_t__) ; 
 char* kmem_zalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minclsyspri ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_io_queues_run_one ; 
 int /*<<< orphan*/  snprintf (char*,scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  spa_config_held (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * taskq_create (char*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ taskq_dispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskq_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
scan_io_queues_run(dsl_scan_t *scn)
{
	spa_t *spa = scn->scn_dp->dp_spa;

	ASSERT(scn->scn_is_sorted);
	ASSERT(spa_config_held(spa, SCL_CONFIG, RW_READER));

	if (scn->scn_bytes_pending == 0)
		return;

	if (scn->scn_taskq == NULL) {
		char *tq_name = kmem_zalloc(ZFS_MAX_DATASET_NAME_LEN + 16,
		    KM_SLEEP);
		int nthreads = spa->spa_root_vdev->vdev_children;

		/*
		 * We need to make this taskq *always* execute as many
		 * threads in parallel as we have top-level vdevs and no
		 * less, otherwise strange serialization of the calls to
		 * scan_io_queues_run_one can occur during spa_sync runs
		 * and that significantly impacts performance.
		 */
		(void) snprintf(tq_name, ZFS_MAX_DATASET_NAME_LEN + 16,
		    "dsl_scan_tq_%s", spa->spa_name);
		scn->scn_taskq = taskq_create(tq_name, nthreads, minclsyspri,
		    nthreads, nthreads, TASKQ_PREPOPULATE);
		kmem_free(tq_name, ZFS_MAX_DATASET_NAME_LEN + 16);
	}

	for (uint64_t i = 0; i < spa->spa_root_vdev->vdev_children; i++) {
		vdev_t *vd = spa->spa_root_vdev->vdev_child[i];

		mutex_enter(&vd->vdev_scan_io_queue_lock);
		if (vd->vdev_scan_io_queue != NULL) {
			VERIFY(taskq_dispatch(scn->scn_taskq,
			    scan_io_queues_run_one, vd->vdev_scan_io_queue,
			    TQ_SLEEP) != TASKQID_INVALID);
		}
		mutex_exit(&vd->vdev_scan_io_queue_lock);
	}

	/*
	 * Wait for the queues to finish issuing thir IOs for this run
	 * before we return. There may still be IOs in flight at this
	 * point.
	 */
	taskq_wait(scn->scn_taskq);
}