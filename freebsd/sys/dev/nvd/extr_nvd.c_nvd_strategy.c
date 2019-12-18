#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nvd_disk {scalar_t__ ordered_in_flight; scalar_t__ cur_depth; int /*<<< orphan*/  bioqtask; int /*<<< orphan*/  tq; int /*<<< orphan*/  bioqlock; int /*<<< orphan*/  bioq; } ;
struct bio {int bio_flags; TYPE_1__* bio_disk; } ;
struct TYPE_2__ {scalar_t__ d_drv1; } ;

/* Variables and functions */
 int BIO_ORDERED ; 
 scalar_t__ __predict_false (int) ; 
 scalar_t__ __predict_true (int) ; 
 scalar_t__ atomic_fetchadd_int (scalar_t__*,int) ; 
 int /*<<< orphan*/ * bioq_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bioq_insert_tail (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvd_bio_submit (struct nvd_disk*,struct bio*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvd_strategy(struct bio *bp)
{
	struct nvd_disk *ndisk = (struct nvd_disk *)bp->bio_disk->d_drv1;

	/*
	 * bio with BIO_ORDERED flag must be executed after all previous
	 * bios in the queue, and before any successive bios.
	 */
	if (__predict_false(bp->bio_flags & BIO_ORDERED)) {
		if (atomic_fetchadd_int(&ndisk->ordered_in_flight, 1) == 0 &&
		    ndisk->cur_depth == 0 && bioq_first(&ndisk->bioq) == NULL) {
			nvd_bio_submit(ndisk, bp);
			return;
		}
	} else if (__predict_true(ndisk->ordered_in_flight == 0)) {
		nvd_bio_submit(ndisk, bp);
		return;
	}

	/*
	 * There are ordered bios in flight, so we need to submit
	 *  bios through the task queue to enforce ordering.
	 */
	mtx_lock(&ndisk->bioqlock);
	bioq_insert_tail(&ndisk->bioq, bp);
	mtx_unlock(&ndisk->bioqlock);
	taskqueue_enqueue(ndisk->tq, &ndisk->bioqtask);
}