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
struct ch_softc {int /*<<< orphan*/  device_stats; } ;
struct cam_periph {scalar_t__ softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  CAM_RETRY_SELTO ; 
 unsigned int CH_TIMEOUT_INITIALIZE_ELEMENT_STATUS ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int /*<<< orphan*/  SF_RETRY_UA ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 union ccb* cam_periph_getccb (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int cam_periph_runccb (union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chdone ; 
 int /*<<< orphan*/  cherror ; 
 int /*<<< orphan*/  scsi_initialize_element_status (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 

__attribute__((used)) static int
chielem(struct cam_periph *periph,
	unsigned int timeout)
{
	union ccb *ccb;
	struct ch_softc *softc;
	int error;

	if (!timeout) {
		timeout = CH_TIMEOUT_INITIALIZE_ELEMENT_STATUS;
	} else {
		timeout *= 1000;
	}

	error = 0;
	softc = (struct ch_softc *)periph->softc;

	ccb = cam_periph_getccb(periph, CAM_PRIORITY_NORMAL);

	scsi_initialize_element_status(&ccb->csio,
				      /* retries */ 1,
				      /* cbfcnp */ chdone,
				      /* tag_action */ MSG_SIMPLE_Q_TAG,
				      /* sense_len */ SSD_FULL_SIZE,
				      /* timeout */ timeout);

	error = cam_periph_runccb(ccb, cherror, /*cam_flags*/ CAM_RETRY_SELTO,
				  /*sense_flags*/ SF_RETRY_UA,
				  softc->device_stats);

	xpt_release_ccb(ccb);

	return(error);
}