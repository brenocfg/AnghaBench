#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct bio* ccb_bp; int /*<<< orphan*/  ccb_state; } ;
union ccb {TYPE_2__ ccb_h; int /*<<< orphan*/  csio; } ;
struct pt_softc {int /*<<< orphan*/  bio_queue; int /*<<< orphan*/  pending_ccbs; int /*<<< orphan*/  io_timeout; int /*<<< orphan*/  device_stats; } ;
struct cam_periph {int /*<<< orphan*/  path; scalar_t__ softc; } ;
struct bio {scalar_t__ bio_cmd; int /*<<< orphan*/  bio_data; int /*<<< orphan*/  bio_bcount; } ;
struct TYPE_3__ {int /*<<< orphan*/  le; } ;

/* Variables and functions */
 scalar_t__ BIO_READ ; 
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int /*<<< orphan*/  PT_CCB_BUFFER_IO_UA ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 struct bio* bioq_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bioq_remove (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  devstat_start_transaction_bio (int /*<<< orphan*/ ,struct bio*) ; 
 TYPE_1__ periph_links ; 
 int /*<<< orphan*/  ptdone ; 
 int /*<<< orphan*/  scsi_send_receive (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_schedule (struct cam_periph*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ptstart(struct cam_periph *periph, union ccb *start_ccb)
{
	struct pt_softc *softc;
	struct bio *bp;

	softc = (struct pt_softc *)periph->softc;

	CAM_DEBUG(periph->path, CAM_DEBUG_TRACE, ("ptstart\n"));

	/*
	 * See if there is a buf with work for us to do..
	 */
	bp = bioq_first(&softc->bio_queue);
	if (bp == NULL) {
		xpt_release_ccb(start_ccb);
	} else {
		bioq_remove(&softc->bio_queue, bp);

		devstat_start_transaction_bio(softc->device_stats, bp);

		scsi_send_receive(&start_ccb->csio,
				  /*retries*/4,
				  ptdone,
				  MSG_SIMPLE_Q_TAG,
				  bp->bio_cmd == BIO_READ,
				  /*byte2*/0,
				  bp->bio_bcount,
				  bp->bio_data,
				  /*sense_len*/SSD_FULL_SIZE,
				  /*timeout*/softc->io_timeout);

		start_ccb->ccb_h.ccb_state = PT_CCB_BUFFER_IO_UA;

		/*
		 * Block out any asynchronous callbacks
		 * while we touch the pending ccb list.
		 */
		LIST_INSERT_HEAD(&softc->pending_ccbs, &start_ccb->ccb_h,
				 periph_links.le);

		start_ccb->ccb_h.ccb_bp = bp;
		bp = bioq_first(&softc->bio_queue);

		xpt_action(start_ccb);
		
		if (bp != NULL) {
			/* Have more work to do, so ensure we stay scheduled */
			xpt_schedule(periph, CAM_PRIORITY_NORMAL);
		}
	}
}