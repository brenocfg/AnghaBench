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
struct TYPE_13__ {int /*<<< orphan*/  io_size; TYPE_2__* io_vd; void* io_offset; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_14__ {scalar_t__ vdev_notrim; TYPE_4__* vdev_trimmap; } ;
typedef  TYPE_2__ vdev_t ;
typedef  void* uint64_t ;
struct TYPE_15__ {void* ts_end; void* ts_start; } ;
typedef  TYPE_3__ trim_seg_t ;
struct TYPE_16__ {int /*<<< orphan*/  tm_lock; int /*<<< orphan*/  tm_inflight_writes; int /*<<< orphan*/  tm_queued_frees; int /*<<< orphan*/  tm_pending_writes; int /*<<< orphan*/  tm_inflight_frees; } ;
typedef  TYPE_4__ trim_map_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 void* TRIM_ZIO_END (TYPE_2__*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avl_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_3__* avl_find (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_insert_tail (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trim_map_segment_remove (TYPE_4__*,TYPE_3__*,void*,void*) ; 
 int /*<<< orphan*/  zfs_trim_enabled ; 

boolean_t
trim_map_write_start(zio_t *zio)
{
	vdev_t *vd = zio->io_vd;
	trim_map_t *tm = vd->vdev_trimmap;
	trim_seg_t tsearch, *ts;
	boolean_t left_over, right_over;
	uint64_t start, end;

	if (!zfs_trim_enabled || vd->vdev_notrim || tm == NULL)
		return (B_TRUE);

	start = zio->io_offset;
	end = TRIM_ZIO_END(zio->io_vd, start, zio->io_size);
	tsearch.ts_start = start;
	tsearch.ts_end = end;

	mutex_enter(&tm->tm_lock);

	/*
	 * Checking for colliding in-flight frees.
	 */
	ts = avl_find(&tm->tm_inflight_frees, &tsearch, NULL);
	if (ts != NULL) {
		list_insert_tail(&tm->tm_pending_writes, zio);
		mutex_exit(&tm->tm_lock);
		return (B_FALSE);
	}

	/*
	 * Loop until all overlapping segments are removed.
	 */
	while ((ts = avl_find(&tm->tm_queued_frees, &tsearch, NULL)) != NULL) {
		trim_map_segment_remove(tm, ts, start, end);
	}

	avl_add(&tm->tm_inflight_writes, zio);

	mutex_exit(&tm->tm_lock);

	return (B_TRUE);
}