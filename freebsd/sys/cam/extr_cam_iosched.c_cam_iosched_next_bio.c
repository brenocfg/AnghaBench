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
struct TYPE_2__ {int /*<<< orphan*/  pending; int /*<<< orphan*/  total; int /*<<< orphan*/  queued; int /*<<< orphan*/  state_flags; } ;
struct cam_iosched_softc {TYPE_1__ read_stats; int /*<<< orphan*/  bio_queue; } ;
struct bio {scalar_t__ bio_cmd; } ;

/* Variables and functions */
 scalar_t__ BIO_READ ; 
 int /*<<< orphan*/  IOP_RATE_LIMITED ; 
 struct bio* bioq_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bioq_remove (int /*<<< orphan*/ *,struct bio*) ; 
 struct bio* cam_iosched_get_trim (struct cam_iosched_softc*) ; 
 struct bio* cam_iosched_get_write (struct cam_iosched_softc*) ; 
 scalar_t__ cam_iosched_limiter_iop (TYPE_1__*,struct bio*) ; 
 scalar_t__ do_dynamic_iosched ; 
 int iosched_debug ; 
 int /*<<< orphan*/  printf (char*,struct bio*,...) ; 

struct bio *
cam_iosched_next_bio(struct cam_iosched_softc *isc)
{
	struct bio *bp;

	/*
	 * See if we have a trim that can be scheduled. We can only send one
	 * at a time down, so this takes that into account.
	 *
	 * XXX newer TRIM commands are queueable. Revisit this when we
	 * implement them.
	 */
	if ((bp = cam_iosched_get_trim(isc)) != NULL)
		return bp;

#ifdef CAM_IOSCHED_DYNAMIC
	/*
	 * See if we have any pending writes, and room in the queue for them,
	 * and if so, those are next.
	 */
	if (do_dynamic_iosched) {
		if ((bp = cam_iosched_get_write(isc)) != NULL)
			return bp;
	}
#endif

	/*
	 * next, see if there's other, normal I/O waiting. If so return that.
	 */
	if ((bp = bioq_first(&isc->bio_queue)) == NULL)
		return NULL;

#ifdef CAM_IOSCHED_DYNAMIC
	/*
	 * For the dynamic scheduler, bio_queue is only for reads, so enforce
	 * the limits here. Enforce only for reads.
	 */
	if (do_dynamic_iosched) {
		if (bp->bio_cmd == BIO_READ &&
		    cam_iosched_limiter_iop(&isc->read_stats, bp) != 0) {
			isc->read_stats.state_flags |= IOP_RATE_LIMITED;
			return NULL;
		}
	}
	isc->read_stats.state_flags &= ~IOP_RATE_LIMITED;
#endif
	bioq_remove(&isc->bio_queue, bp);
#ifdef CAM_IOSCHED_DYNAMIC
	if (do_dynamic_iosched) {
		if (bp->bio_cmd == BIO_READ) {
			isc->read_stats.queued--;
			isc->read_stats.total++;
			isc->read_stats.pending++;
		} else
			printf("Found bio_cmd = %#x\n", bp->bio_cmd);
	}
	if (iosched_debug > 9)
		printf("HWQ : %p %#x\n", bp, bp->bio_cmd);
#endif
	return bp;
}