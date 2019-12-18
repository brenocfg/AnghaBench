#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
struct TYPE_12__ {scalar_t__ spa_scrub_inflight; scalar_t__ spa_last_io; int /*<<< orphan*/  spa_scrub_lock; int /*<<< orphan*/  spa_scrub_io_cv; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  kmutex_t ;
struct TYPE_13__ {scalar_t__ scn_maxinflight_bytes; int /*<<< orphan*/  scn_zio_root; } ;
typedef  TYPE_3__ dsl_scan_t ;
struct TYPE_14__ {scalar_t__ q_inflight_bytes; scalar_t__ q_maxinflight_bytes; int /*<<< orphan*/  q_zio_cv; TYPE_1__* q_vd; } ;
typedef  TYPE_4__ dsl_scan_io_queue_t ;
struct TYPE_15__ {TYPE_3__* dp_scan; int /*<<< orphan*/  dp_blkstats; TYPE_2__* dp_spa; } ;
typedef  TYPE_5__ dsl_pool_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  abd_t ;
struct TYPE_11__ {int /*<<< orphan*/  vdev_scan_io_queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t BP_GET_PSIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  MAX (int,int /*<<< orphan*/ ) ; 
 int ZIO_FLAG_RESILVER ; 
 int ZIO_FLAG_SCRUB ; 
 int /*<<< orphan*/  ZIO_PRIORITY_SCRUB ; 
 int /*<<< orphan*/ * abd_alloc_for_io (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_block (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ddi_get_lbolt64 () ; 
 int /*<<< orphan*/  delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_scan_scrub_done ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 unsigned int zfs_resilver_delay ; 
 scalar_t__ zfs_scan_idle ; 
 unsigned int zfs_scrub_delay ; 
 int /*<<< orphan*/  zio_nowait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_read (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
scan_exec_io(dsl_pool_t *dp, const blkptr_t *bp, int zio_flags,
    const zbookmark_phys_t *zb, dsl_scan_io_queue_t *queue)
{
	spa_t *spa = dp->dp_spa;
	dsl_scan_t *scn = dp->dp_scan;
	size_t size = BP_GET_PSIZE(bp);
	abd_t *data = abd_alloc_for_io(size, B_FALSE);
	unsigned int scan_delay = 0;

	if (queue == NULL) {
		mutex_enter(&spa->spa_scrub_lock);
		while (spa->spa_scrub_inflight >= scn->scn_maxinflight_bytes)
			cv_wait(&spa->spa_scrub_io_cv, &spa->spa_scrub_lock);
		spa->spa_scrub_inflight += BP_GET_PSIZE(bp);
		mutex_exit(&spa->spa_scrub_lock);
	} else {
		kmutex_t *q_lock = &queue->q_vd->vdev_scan_io_queue_lock;

		mutex_enter(q_lock);
		while (queue->q_inflight_bytes >= queue->q_maxinflight_bytes)
			cv_wait(&queue->q_zio_cv, q_lock);
		queue->q_inflight_bytes += BP_GET_PSIZE(bp);
		mutex_exit(q_lock);
	}

	if (zio_flags & ZIO_FLAG_RESILVER)
		scan_delay = zfs_resilver_delay;
	else {
		ASSERT(zio_flags & ZIO_FLAG_SCRUB);
		scan_delay = zfs_scrub_delay;
	}

	if (scan_delay && (ddi_get_lbolt64() - spa->spa_last_io <= zfs_scan_idle))
		delay(MAX((int)scan_delay, 0));
	
	count_block(dp->dp_scan, dp->dp_blkstats, bp);
	zio_nowait(zio_read(dp->dp_scan->scn_zio_root, spa, bp, data, size,
	    dsl_scan_scrub_done, queue, ZIO_PRIORITY_SCRUB, zio_flags, zb));
}