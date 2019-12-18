#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  periph_data; } ;
struct TYPE_7__ {TYPE_2__ qos; } ;
union ccb {TYPE_3__ ccb_h; } ;
struct TYPE_5__ {int /*<<< orphan*/  pending; int /*<<< orphan*/  out; int /*<<< orphan*/  errs; } ;
struct TYPE_8__ {int /*<<< orphan*/  pending; int /*<<< orphan*/  out; int /*<<< orphan*/  errs; } ;
struct cam_iosched_softc {scalar_t__ max_lat; int /*<<< orphan*/  latarg; int /*<<< orphan*/  (* latfcn ) (int /*<<< orphan*/ ,scalar_t__,struct bio*) ;TYPE_1__ trim_stats; TYPE_4__ read_stats; TYPE_4__ write_stats; } ;
struct bio {int bio_cmd; int bio_flags; int /*<<< orphan*/  bio_bcount; } ;
typedef  scalar_t__ sbintime_t ;

/* Variables and functions */
 int BIO_DELETE ; 
 int BIO_ERROR ; 
 int BIO_FLUSH ; 
 int BIO_READ ; 
 int BIO_WRITE ; 
 int /*<<< orphan*/  cam_iosched_io_metric_update (struct cam_iosched_softc*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int cam_iosched_limiter_iodone (TYPE_4__*,struct bio*) ; 
 scalar_t__ cam_iosched_sbintime_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_dynamic_iosched ; 
 int iosched_debug ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,struct bio*) ; 

int
cam_iosched_bio_complete(struct cam_iosched_softc *isc, struct bio *bp,
    union ccb *done_ccb)
{
	int retval = 0;
#ifdef CAM_IOSCHED_DYNAMIC
	if (!do_dynamic_iosched)
		return retval;

	if (iosched_debug > 10)
		printf("done: %p %#x\n", bp, bp->bio_cmd);
	if (bp->bio_cmd == BIO_WRITE) {
		retval = cam_iosched_limiter_iodone(&isc->write_stats, bp);
		if ((bp->bio_flags & BIO_ERROR) != 0)
			isc->write_stats.errs++;
		isc->write_stats.out++;
		isc->write_stats.pending--;
	} else if (bp->bio_cmd == BIO_READ) {
		retval = cam_iosched_limiter_iodone(&isc->read_stats, bp);
		if ((bp->bio_flags & BIO_ERROR) != 0)
			isc->read_stats.errs++;
		isc->read_stats.out++;
		isc->read_stats.pending--;
	} else if (bp->bio_cmd == BIO_DELETE) {
		if ((bp->bio_flags & BIO_ERROR) != 0)
			isc->trim_stats.errs++;
		isc->trim_stats.out++;
		isc->trim_stats.pending--;
	} else if (bp->bio_cmd != BIO_FLUSH) {
		if (iosched_debug)
			printf("Completing command with bio_cmd == %#x\n", bp->bio_cmd);
	}

	if (!(bp->bio_flags & BIO_ERROR) && done_ccb != NULL) {
		sbintime_t sim_latency;
		
		sim_latency = cam_iosched_sbintime_t(done_ccb->ccb_h.qos.periph_data);
		
		cam_iosched_io_metric_update(isc, sim_latency,
		    bp->bio_cmd, bp->bio_bcount);
		/*
		 * Debugging code: allow callbacks to the periph driver when latency max
		 * is exceeded. This can be useful for triggering external debugging actions.
		 */
		if (isc->latfcn && isc->max_lat != 0 && sim_latency > isc->max_lat)
			isc->latfcn(isc->latarg, sim_latency, bp);
	}
		
#endif
	return retval;
}