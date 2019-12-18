#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_6__* vdev_scan_io_queue; } ;
typedef  TYPE_3__ vdev_t ;
typedef  size_t uint64_t ;
struct TYPE_11__ {TYPE_2__* spa_root_vdev; } ;
typedef  TYPE_4__ spa_t ;
struct TYPE_12__ {size_t scn_avg_seg_size_this_txg; size_t scn_avg_zio_size_this_txg; size_t scn_segs_this_txg; size_t scn_zios_this_txg; TYPE_1__* scn_dp; } ;
typedef  TYPE_5__ dsl_scan_t ;
struct TYPE_13__ {scalar_t__ q_zios_this_txg; scalar_t__ q_segs_this_txg; scalar_t__ q_total_zio_size_this_txg; scalar_t__ q_total_seg_size_this_txg; } ;
typedef  TYPE_6__ dsl_scan_io_queue_t ;
struct TYPE_9__ {size_t vdev_children; TYPE_3__** vdev_child; } ;
struct TYPE_8__ {TYPE_4__* dp_spa; } ;

/* Variables and functions */

__attribute__((used)) static void
dsl_scan_update_stats(dsl_scan_t *scn)
{
	spa_t *spa = scn->scn_dp->dp_spa;
	uint64_t i;
	uint64_t seg_size_total = 0, zio_size_total = 0;
	uint64_t seg_count_total = 0, zio_count_total = 0;

	for (i = 0; i < spa->spa_root_vdev->vdev_children; i++) {
		vdev_t *vd = spa->spa_root_vdev->vdev_child[i];
		dsl_scan_io_queue_t *queue = vd->vdev_scan_io_queue;

		if (queue == NULL)
			continue;

		seg_size_total += queue->q_total_seg_size_this_txg;
		zio_size_total += queue->q_total_zio_size_this_txg;
		seg_count_total += queue->q_segs_this_txg;
		zio_count_total += queue->q_zios_this_txg;
	}

	if (seg_count_total == 0 || zio_count_total == 0) {
		scn->scn_avg_seg_size_this_txg = 0;
		scn->scn_avg_zio_size_this_txg = 0;
		scn->scn_segs_this_txg = 0;
		scn->scn_zios_this_txg = 0;
		return;
	}

	scn->scn_avg_seg_size_this_txg = seg_size_total / seg_count_total;
	scn->scn_avg_zio_size_this_txg = zio_size_total / zio_count_total;
	scn->scn_segs_this_txg = seg_count_total;
	scn->scn_zios_this_txg = zio_count_total;
}