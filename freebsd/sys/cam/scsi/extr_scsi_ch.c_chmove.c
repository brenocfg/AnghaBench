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
typedef  int u_int16_t ;
struct changer_move {size_t cm_fromtype; size_t cm_totype; int cm_fromunit; int cm_tounit; int cm_flags; } ;
struct ch_softc {int* sc_counts; int* sc_movemask; int* sc_firsts; int /*<<< orphan*/  device_stats; int /*<<< orphan*/  sc_picker; } ;
struct cam_periph {scalar_t__ softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  CAM_RETRY_SELTO ; 
 size_t CHET_DT ; 
 int /*<<< orphan*/  CH_TIMEOUT_MOVE_MEDIUM ; 
 int CM_INVERT ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int /*<<< orphan*/  SF_RETRY_UA ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 union ccb* cam_periph_getccb (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int cam_periph_runccb (union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chdone ; 
 int /*<<< orphan*/  cherror ; 
 int /*<<< orphan*/  scsi_move_medium (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 

__attribute__((used)) static int
chmove(struct cam_periph *periph, struct changer_move *cm)
{
	struct ch_softc *softc;
	u_int16_t fromelem, toelem;
	union ccb *ccb;
	int error;

	error = 0;
	softc = (struct ch_softc *)periph->softc;

	/*
	 * Check arguments.
	 */
	if ((cm->cm_fromtype > CHET_DT) || (cm->cm_totype > CHET_DT))
		return (EINVAL);
	if ((cm->cm_fromunit > (softc->sc_counts[cm->cm_fromtype] - 1)) ||
	    (cm->cm_tounit > (softc->sc_counts[cm->cm_totype] - 1)))
		return (ENODEV);

	/*
	 * Check the request against the changer's capabilities.
	 */
	if ((softc->sc_movemask[cm->cm_fromtype] & (1 << cm->cm_totype)) == 0)
		return (ENODEV);

	/*
	 * Calculate the source and destination elements.
	 */
	fromelem = softc->sc_firsts[cm->cm_fromtype] + cm->cm_fromunit;
	toelem = softc->sc_firsts[cm->cm_totype] + cm->cm_tounit;

	ccb = cam_periph_getccb(periph, CAM_PRIORITY_NORMAL);

	scsi_move_medium(&ccb->csio,
			 /* retries */ 1,
			 /* cbfcnp */ chdone,
			 /* tag_action */ MSG_SIMPLE_Q_TAG,
			 /* tea */ softc->sc_picker,
			 /* src */ fromelem,
			 /* dst */ toelem,
			 /* invert */ (cm->cm_flags & CM_INVERT) ? TRUE : FALSE,
			 /* sense_len */ SSD_FULL_SIZE,
			 /* timeout */ CH_TIMEOUT_MOVE_MEDIUM);

	error = cam_periph_runccb(ccb, cherror, /*cam_flags*/CAM_RETRY_SELTO,
				  /*sense_flags*/ SF_RETRY_UA,
				  softc->device_stats);

	xpt_release_ccb(ccb);

	return(error);
}