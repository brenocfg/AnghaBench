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
struct nda_softc {int /*<<< orphan*/  cam_iosched; int /*<<< orphan*/  deletes; } ;
struct cam_periph {int flags; int /*<<< orphan*/  path; scalar_t__ softc; } ;
struct bio {scalar_t__ bio_cmd; TYPE_1__* bio_disk; } ;
struct TYPE_2__ {scalar_t__ d_drv1; } ;

/* Variables and functions */
 scalar_t__ BIO_DELETE ; 
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 int CAM_PERIPH_INVALID ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  biofinish (struct bio*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_iosched_queue_work (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  cam_periph_lock (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_unlock (struct cam_periph*) ; 
 int /*<<< orphan*/  ndaschedule (struct cam_periph*) ; 

__attribute__((used)) static void
ndastrategy(struct bio *bp)
{
	struct cam_periph *periph;
	struct nda_softc *softc;
	
	periph = (struct cam_periph *)bp->bio_disk->d_drv1;
	softc = (struct nda_softc *)periph->softc;

	cam_periph_lock(periph);

	CAM_DEBUG(periph->path, CAM_DEBUG_TRACE, ("ndastrategy(%p)\n", bp));

	/*
	 * If the device has been made invalid, error out
	 */
	if ((periph->flags & CAM_PERIPH_INVALID) != 0) {
		cam_periph_unlock(periph);
		biofinish(bp, NULL, ENXIO);
		return;
	}
	
	if (bp->bio_cmd == BIO_DELETE)
		softc->deletes++;

	/*
	 * Place it in the queue of disk activities for this disk
	 */
	cam_iosched_queue_work(softc->cam_iosched, bp);

	/*
	 * Schedule ourselves for performing the work.
	 */
	ndaschedule(periph);
	cam_periph_unlock(periph);

	return;
}