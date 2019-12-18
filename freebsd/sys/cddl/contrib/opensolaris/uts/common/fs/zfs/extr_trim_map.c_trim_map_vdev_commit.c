#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
struct TYPE_14__ {scalar_t__ vdev_isl2cache; TYPE_1__* vdev_ops; TYPE_4__* vdev_trimmap; } ;
typedef  TYPE_2__ vdev_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_15__ {scalar_t__ ts_end; scalar_t__ ts_start; } ;
typedef  TYPE_3__ trim_seg_t ;
struct TYPE_16__ {int tm_pending; int /*<<< orphan*/  tm_lock; int /*<<< orphan*/  tm_inflight_frees; int /*<<< orphan*/  tm_queued_frees; } ;
typedef  TYPE_4__ trim_map_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int int64_t ;
typedef  int hrtime_t ;
struct TYPE_13__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NANOSEC ; 
 int P2ROUNDUP (int,int) ; 
 int /*<<< orphan*/  TRIM_MAP_REM (TYPE_4__*,TYPE_3__*) ; 
 int TRIM_MAP_SEGS (scalar_t__) ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  avl_add (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  avl_remove (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int gethrtime () ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_freeze_txg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_last_synced_txg (int /*<<< orphan*/ *) ; 
 TYPE_3__* trim_map_first (TYPE_4__*,scalar_t__,scalar_t__,int,int) ; 
 int trim_timeout ; 
 scalar_t__ trim_txg_delay ; 
 int trim_vdev_max_pending ; 
 int /*<<< orphan*/  zio_nowait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_trim (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
trim_map_vdev_commit(spa_t *spa, zio_t *zio, vdev_t *vd)
{
	trim_map_t *tm = vd->vdev_trimmap;
	trim_seg_t *ts;
	uint64_t size, offset, txgtarget, txgsafe;
	int64_t hard, soft;
	hrtime_t timelimit;

	ASSERT(vd->vdev_ops->vdev_op_leaf);

	if (tm == NULL)
		return;

	timelimit = gethrtime() - (hrtime_t)trim_timeout * NANOSEC;
	if (vd->vdev_isl2cache) {
		txgsafe = UINT64_MAX;
		txgtarget = UINT64_MAX;
	} else {
		txgsafe = MIN(spa_last_synced_txg(spa), spa_freeze_txg(spa));
		if (txgsafe > trim_txg_delay)
			txgtarget = txgsafe - trim_txg_delay;
		else
			txgtarget = 0;
	}

	mutex_enter(&tm->tm_lock);
	hard = 0;
	if (tm->tm_pending > trim_vdev_max_pending)
		hard = (tm->tm_pending - trim_vdev_max_pending) / 4;
	soft = P2ROUNDUP(hard + tm->tm_pending / trim_timeout + 1, 64);
	/* Loop until we have sent all outstanding free's */
	while (soft > 0 &&
	    (ts = trim_map_first(tm, txgtarget, txgsafe, timelimit, hard > 0))
	    != NULL) {
		TRIM_MAP_REM(tm, ts);
		avl_remove(&tm->tm_queued_frees, ts);
		avl_add(&tm->tm_inflight_frees, ts);
		size = ts->ts_end - ts->ts_start;
		offset = ts->ts_start;
		/*
		 * We drop the lock while we call zio_nowait as the IO
		 * scheduler can result in a different IO being run e.g.
		 * a write which would result in a recursive lock.
		 */
		mutex_exit(&tm->tm_lock);

		zio_nowait(zio_trim(zio, spa, vd, offset, size));

		soft -= TRIM_MAP_SEGS(size);
		hard -= TRIM_MAP_SEGS(size);
		mutex_enter(&tm->tm_lock);
	}
	mutex_exit(&tm->tm_lock);
}