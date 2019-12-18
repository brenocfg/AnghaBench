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
struct changer_position {size_t cp_type; int cp_unit; int cp_flags; } ;
struct ch_softc {int* sc_counts; int* sc_firsts; int /*<<< orphan*/  device_stats; int /*<<< orphan*/  sc_picker; } ;
struct cam_periph {scalar_t__ softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  CAM_RETRY_SELTO ; 
 size_t CHET_DT ; 
 int /*<<< orphan*/  CH_TIMEOUT_POSITION_TO_ELEMENT ; 
 int CP_INVERT ; 
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
 int /*<<< orphan*/  scsi_position_to_element (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 

__attribute__((used)) static int
chposition(struct cam_periph *periph, struct changer_position *cp)
{
	struct ch_softc *softc;
	u_int16_t dst;
	union ccb *ccb;
	int error;

	error = 0;
	softc = (struct ch_softc *)periph->softc;

	/*
	 * Check arguments.
	 */
	if (cp->cp_type > CHET_DT)
		return (EINVAL);
	if (cp->cp_unit > (softc->sc_counts[cp->cp_type] - 1))
		return (ENODEV);

	/*
	 * Calculate the destination element.
	 */
	dst = softc->sc_firsts[cp->cp_type] + cp->cp_unit;

	ccb = cam_periph_getccb(periph, CAM_PRIORITY_NORMAL);

	scsi_position_to_element(&ccb->csio,
				 /* retries */ 1,
				 /* cbfcnp */ chdone,
				 /* tag_action */ MSG_SIMPLE_Q_TAG,
				 /* tea */ softc->sc_picker,
				 /* dst */ dst,
				 /* invert */ (cp->cp_flags & CP_INVERT) ?
					      TRUE : FALSE,
				 /* sense_len */ SSD_FULL_SIZE,
				 /* timeout */ CH_TIMEOUT_POSITION_TO_ELEMENT);

	error = cam_periph_runccb(ccb, cherror, /*cam_flags*/ CAM_RETRY_SELTO,
				  /*sense_flags*/ SF_RETRY_UA,
				  softc->device_stats);

	xpt_release_ccb(ccb);

	return(error);
}