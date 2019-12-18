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
struct pt_softc {int flags; int /*<<< orphan*/  bio_queue; } ;
struct cam_periph {scalar_t__ softc; } ;
struct bio {int /*<<< orphan*/  bio_bcount; int /*<<< orphan*/  bio_resid; TYPE_1__* bio_dev; } ;
struct TYPE_2__ {scalar_t__ si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int PT_FLAG_DEVICE_INVALID ; 
 int /*<<< orphan*/  biofinish (struct bio*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bioq_insert_tail (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  cam_periph_lock (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_unlock (struct cam_periph*) ; 
 int /*<<< orphan*/  xpt_schedule (struct cam_periph*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ptstrategy(struct bio *bp)
{
	struct cam_periph *periph;
	struct pt_softc *softc;
	
	periph = (struct cam_periph *)bp->bio_dev->si_drv1;
	bp->bio_resid = bp->bio_bcount;
	if (periph == NULL) {
		biofinish(bp, NULL, ENXIO);
		return;
	}
	cam_periph_lock(periph);
	softc = (struct pt_softc *)periph->softc;

	/*
	 * If the device has been made invalid, error out
	 */
	if ((softc->flags & PT_FLAG_DEVICE_INVALID)) {
		cam_periph_unlock(periph);
		biofinish(bp, NULL, ENXIO);
		return;
	}
	
	/*
	 * Place it in the queue of disk activities for this disk
	 */
	bioq_insert_tail(&softc->bio_queue, bp);

	/*
	 * Schedule ourselves for performing the work.
	 */
	xpt_schedule(periph, CAM_PRIORITY_NORMAL);
	cam_periph_unlock(periph);

	return;
}