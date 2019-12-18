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
struct cd_softc {int flags; int /*<<< orphan*/  bio_queue; } ;
struct cam_periph {scalar_t__ softc; int /*<<< orphan*/  path; } ;
struct bio {TYPE_1__* bio_disk; } ;
struct TYPE_2__ {scalar_t__ d_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int CD_FLAG_INVALID ; 
 int CD_FLAG_VALID_MEDIA ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  biofinish (struct bio*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bioq_disksort (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  cam_periph_lock (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_unlock (struct cam_periph*) ; 
 int /*<<< orphan*/  cdcheckmedia (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_schedule (struct cam_periph*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cdstrategy(struct bio *bp)
{
	struct cam_periph *periph;
	struct cd_softc *softc;

	periph = (struct cam_periph *)bp->bio_disk->d_drv1;
	cam_periph_lock(periph);
	CAM_DEBUG(periph->path, CAM_DEBUG_TRACE,
	    ("cdstrategy(%p)\n", bp));

	softc = (struct cd_softc *)periph->softc;

	/*
	 * If the device has been made invalid, error out
	 */
	if ((softc->flags & CD_FLAG_INVALID)) {
		cam_periph_unlock(periph);
		biofinish(bp, NULL, ENXIO);
		return;
	}

	/*
	 * Place it in the queue of disk activities for this disk
	 */
	bioq_disksort(&softc->bio_queue, bp);

        /*
	 * If we don't know that we have valid media, schedule the media
	 * check first.  The I/O will get executed after the media check.
	 */
	if ((softc->flags & CD_FLAG_VALID_MEDIA) == 0)
		cdcheckmedia(periph, /*do_wait*/ 0);
	else
		xpt_schedule(periph, CAM_PRIORITY_NORMAL);

	cam_periph_unlock(periph);
	return;
}