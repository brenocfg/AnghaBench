#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  queued; int /*<<< orphan*/  in; } ;
struct TYPE_5__ {int /*<<< orphan*/  queued; int /*<<< orphan*/  in; } ;
struct TYPE_4__ {int /*<<< orphan*/  queued; int /*<<< orphan*/  in; } ;
struct cam_iosched_softc {scalar_t__ trim_ticks; scalar_t__ queued_trims; TYPE_3__ write_stats; TYPE_2__ read_stats; int /*<<< orphan*/  bio_queue; int /*<<< orphan*/  write_queue; TYPE_1__ trim_stats; void* last_trim_tick; int /*<<< orphan*/  trim_queue; } ;
struct bio {scalar_t__ bio_cmd; } ;

/* Variables and functions */
 scalar_t__ BIO_DELETE ; 
 scalar_t__ BIO_FLUSH ; 
 scalar_t__ BIO_READ ; 
 scalar_t__ BIO_WRITE ; 
 int /*<<< orphan*/  bioq_disksort (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  bioq_insert_tail (int /*<<< orphan*/ *,struct bio*) ; 
 scalar_t__ cam_iosched_sort_queue (struct cam_iosched_softc*) ; 
 scalar_t__ do_dynamic_iosched ; 
 int iosched_debug ; 
 int /*<<< orphan*/  printf (char*,struct bio*,scalar_t__) ; 
 void* ticks ; 

void
cam_iosched_queue_work(struct cam_iosched_softc *isc, struct bio *bp)
{

	/*
	 * If we get a BIO_FLUSH, and we're doing delayed BIO_DELETEs then we
	 * set the last tick time to one less than the current ticks minus the
	 * delay to force the BIO_DELETEs to be presented to the client driver.
	 */
	if (bp->bio_cmd == BIO_FLUSH && isc->trim_ticks > 0)
		isc->last_trim_tick = ticks - isc->trim_ticks - 1;

	/*
	 * Put all trims on the trim queue. Otherwise put the work on the bio
	 * queue.
	 */
	if (bp->bio_cmd == BIO_DELETE) {
		bioq_insert_tail(&isc->trim_queue, bp);
		if (isc->queued_trims == 0)
			isc->last_trim_tick = ticks;
		isc->queued_trims++;
#ifdef CAM_IOSCHED_DYNAMIC
		isc->trim_stats.in++;
		isc->trim_stats.queued++;
#endif
	}
#ifdef CAM_IOSCHED_DYNAMIC
	else if (do_dynamic_iosched && (bp->bio_cmd != BIO_READ)) {
		if (cam_iosched_sort_queue(isc))
			bioq_disksort(&isc->write_queue, bp);
		else
			bioq_insert_tail(&isc->write_queue, bp);
		if (iosched_debug > 9)
			printf("Qw  : %p %#x\n", bp, bp->bio_cmd);
		if (bp->bio_cmd == BIO_WRITE) {
			isc->write_stats.in++;
			isc->write_stats.queued++;
		}
	}
#endif
	else {
		if (cam_iosched_sort_queue(isc))
			bioq_disksort(&isc->bio_queue, bp);
		else
			bioq_insert_tail(&isc->bio_queue, bp);
#ifdef CAM_IOSCHED_DYNAMIC
		if (iosched_debug > 9)
			printf("Qr  : %p %#x\n", bp, bp->bio_cmd);
		if (bp->bio_cmd == BIO_READ) {
			isc->read_stats.in++;
			isc->read_stats.queued++;
		} else if (bp->bio_cmd == BIO_WRITE) {
			isc->write_stats.in++;
			isc->write_stats.queued++;
		}
#endif
	}
}