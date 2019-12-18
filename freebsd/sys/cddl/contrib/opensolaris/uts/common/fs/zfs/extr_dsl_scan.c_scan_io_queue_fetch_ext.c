#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  range_seg_t ;
struct TYPE_6__ {scalar_t__ scn_clearing; scalar_t__ scn_checkpointing; int /*<<< orphan*/  scn_is_sorted; } ;
typedef  TYPE_2__ dsl_scan_t ;
struct TYPE_7__ {int /*<<< orphan*/  q_exts_by_size; int /*<<< orphan*/  q_exts_by_addr; TYPE_1__* q_vd; TYPE_2__* q_scn; } ;
typedef  TYPE_3__ dsl_scan_io_queue_t ;
struct TYPE_5__ {int /*<<< orphan*/  vdev_scan_io_queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* avl_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* range_tree_first (int /*<<< orphan*/ ) ; 
 int zfs_scan_issue_strategy ; 

__attribute__((used)) static const range_seg_t *
scan_io_queue_fetch_ext(dsl_scan_io_queue_t *queue)
{
	dsl_scan_t *scn = queue->q_scn;

	ASSERT(MUTEX_HELD(&queue->q_vd->vdev_scan_io_queue_lock));
	ASSERT(scn->scn_is_sorted);

	/* handle tunable overrides */
	if (scn->scn_checkpointing || scn->scn_clearing) {
		if (zfs_scan_issue_strategy == 1) {
			return (range_tree_first(queue->q_exts_by_addr));
		} else if (zfs_scan_issue_strategy == 2) {
			return (avl_first(&queue->q_exts_by_size));
		}
	}

	/*
	 * During normal clearing, we want to issue our largest segments
	 * first, keeping IO as sequential as possible, and leaving the
	 * smaller extents for later with the hope that they might eventually
	 * grow to larger sequential segments. However, when the scan is
	 * checkpointing, no new extents will be added to the sorting queue,
	 * so the way we are sorted now is as good as it will ever get.
	 * In this case, we instead switch to issuing extents in LBA order.
	 */
	if (scn->scn_checkpointing) {
		return (range_tree_first(queue->q_exts_by_addr));
	} else if (scn->scn_clearing) {
		return (avl_first(&queue->q_exts_by_size));
	} else {
		return (NULL);
	}
}