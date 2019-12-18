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
struct disk {scalar_t__ d_drv1; } ;
struct cd_softc {int flags; TYPE_2__* disk; } ;
struct cam_periph {int /*<<< orphan*/  path; scalar_t__ softc; } ;
struct TYPE_4__ {TYPE_1__* d_devstat; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int,char*) ; 
 int CAM_DEBUG_PERIPH ; 
 int CAM_DEBUG_TRACE ; 
 int CD_FLAG_DISC_REMOVABLE ; 
 int CD_FLAG_VALID_MEDIA ; 
 int CD_FLAG_VALID_TOC ; 
 int /*<<< orphan*/  DEVSTAT_BS_UNAVAILABLE ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  PR_ALLOW ; 
 scalar_t__ cam_periph_hold (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_lock (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_release (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_release_locked (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_unhold (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_unlock (struct cam_periph*) ; 
 int /*<<< orphan*/  cdprevent (struct cam_periph*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cdclose(struct disk *dp)
{
	struct 	cam_periph *periph;
	struct	cd_softc *softc;

	periph = (struct cam_periph *)dp->d_drv1;
	softc = (struct cd_softc *)periph->softc;

	cam_periph_lock(periph);
	if (cam_periph_hold(periph, PRIBIO) != 0) {
		cam_periph_unlock(periph);
		cam_periph_release(periph);
		return (0);
	}

	CAM_DEBUG(periph->path, CAM_DEBUG_TRACE | CAM_DEBUG_PERIPH,
	    ("cdclose\n"));

	if ((softc->flags & CD_FLAG_DISC_REMOVABLE) != 0)
		cdprevent(periph, PR_ALLOW);

	/*
	 * Since we're closing this CD, mark the blocksize as unavailable.
	 * It will be marked as available when the CD is opened again.
	 */
	softc->disk->d_devstat->flags |= DEVSTAT_BS_UNAVAILABLE;

	/*
	 * We'll check the media and toc again at the next open().
	 */
	softc->flags &= ~(CD_FLAG_VALID_MEDIA|CD_FLAG_VALID_TOC);

	cam_periph_unhold(periph);
	cam_periph_release_locked(periph);
	cam_periph_unlock(periph);

	return (0);
}