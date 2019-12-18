#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cd_softc {int flags; int /*<<< orphan*/  toc; int /*<<< orphan*/  state; } ;
struct cam_periph {scalar_t__ softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int CD_FLAG_MEDIA_SCAN_ACT ; 
 int CD_FLAG_MEDIA_WAIT ; 
 int CD_FLAG_VALID_MEDIA ; 
 int /*<<< orphan*/  CD_STATE_MEDIA_PREVENT ; 
 int EINVAL ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  cam_periph_mtx (struct cam_periph*) ; 
 int msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_schedule (struct cam_periph*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cdcheckmedia(struct cam_periph *periph, int do_wait)
{
	struct cd_softc *softc;
	int error;

	softc = (struct cd_softc *)periph->softc;
	error = 0;

	if ((do_wait != 0)
	 && ((softc->flags & CD_FLAG_MEDIA_WAIT) == 0)) {
		softc->flags |= CD_FLAG_MEDIA_WAIT;
	}
	if ((softc->flags & CD_FLAG_MEDIA_SCAN_ACT) == 0) {
		softc->state = CD_STATE_MEDIA_PREVENT;
		softc->flags |= CD_FLAG_MEDIA_SCAN_ACT;
		xpt_schedule(periph, CAM_PRIORITY_NORMAL);
	}

	if (do_wait == 0)
		goto bailout;

	error = msleep(&softc->toc, cam_periph_mtx(periph), PRIBIO,"cdmedia",0);

	if (error != 0)
		goto bailout;

	/*
	 * Check to see whether we have a valid size from the media.  We
	 * may or may not have a valid TOC.
	 */
	if ((softc->flags & CD_FLAG_VALID_MEDIA) == 0)
		error = EINVAL;
bailout:

	return (error);
}