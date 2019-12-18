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
union ccb {int /*<<< orphan*/  csio; } ;
struct cd_softc {int flags; } ;
struct cam_periph {scalar_t__ softc; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  CAM_RETRY_SELTO ; 
 int CD_FLAG_DISC_LOCKED ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int PR_ALLOW ; 
 int PR_PREVENT ; 
 int SF_NO_PRINT ; 
 int SF_RETRY_UA ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 union ccb* cam_periph_getccb (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cd_retry_count ; 
 int /*<<< orphan*/  cderror ; 
 int cdrunccb (union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_prevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 

__attribute__((used)) static void
cdprevent(struct cam_periph *periph, int action)
{
	union	ccb *ccb;
	struct	cd_softc *softc;
	int	error;

	CAM_DEBUG(periph->path, CAM_DEBUG_TRACE, ("entering cdprevent\n"));

	softc = (struct cd_softc *)periph->softc;

	if (((action == PR_ALLOW)
	  && (softc->flags & CD_FLAG_DISC_LOCKED) == 0)
	 || ((action == PR_PREVENT)
	  && (softc->flags & CD_FLAG_DISC_LOCKED) != 0)) {
		return;
	}

	ccb = cam_periph_getccb(periph, CAM_PRIORITY_NORMAL);

	scsi_prevent(&ccb->csio,
		     /*retries*/ cd_retry_count,
		     /*cbfcnp*/NULL,
		     MSG_SIMPLE_Q_TAG,
		     action,
		     SSD_FULL_SIZE,
		     /* timeout */60000);

	error = cdrunccb(ccb, cderror, /*cam_flags*/CAM_RETRY_SELTO,
			/*sense_flags*/SF_RETRY_UA|SF_NO_PRINT);

	xpt_release_ccb(ccb);

	if (error == 0) {
		if (action == PR_ALLOW)
			softc->flags &= ~CD_FLAG_DISC_LOCKED;
		else
			softc->flags |= CD_FLAG_DISC_LOCKED;
	}
}