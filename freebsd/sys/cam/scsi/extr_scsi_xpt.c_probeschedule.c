#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int flags; } ;
struct TYPE_9__ {scalar_t__ target_lun; TYPE_2__* path; } ;
union ccb {TYPE_4__ crcn; TYPE_3__ ccb_h; } ;
struct ccb_pathinq {int hba_inquiry; int hba_misc; } ;
struct cam_periph {int /*<<< orphan*/  path; scalar_t__ softc; } ;
struct TYPE_11__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  request_ccbs; } ;
typedef  TYPE_5__ probe_softc ;
struct TYPE_8__ {TYPE_1__* device; } ;
struct TYPE_7__ {int flags; } ;

/* Variables and functions */
 int CAM_DEV_UNCONFIGURED ; 
 int CAM_EXPECT_INQ_CHANGE ; 
 int /*<<< orphan*/  CAM_PRIORITY_XPT ; 
 int PIM_EXTLUNS ; 
 int PIM_NOBUSRESET ; 
 int PI_SDTR_ABLE ; 
 int PI_WIDE_16 ; 
 int PI_WIDE_32 ; 
 int /*<<< orphan*/  PROBE_EXTLUN ; 
 int /*<<< orphan*/  PROBE_INQUIRY ; 
 int /*<<< orphan*/  PROBE_NO_ANNOUNCE ; 
 int /*<<< orphan*/  PROBE_SET_ACTION (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROBE_TUR ; 
 scalar_t__ TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proberequestdefaultnegotiation (struct cam_periph*) ; 
 int /*<<< orphan*/  xpt_path_inq (struct ccb_pathinq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_schedule (struct cam_periph*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
probeschedule(struct cam_periph *periph)
{
	struct ccb_pathinq cpi;
	union ccb *ccb;
	probe_softc *softc;

	softc = (probe_softc *)periph->softc;
	ccb = (union ccb *)TAILQ_FIRST(&softc->request_ccbs);

	xpt_path_inq(&cpi, periph->path);

	/*
	 * If a device has gone away and another device, or the same one,
	 * is back in the same place, it should have a unit attention
	 * condition pending.  It will not report the unit attention in
	 * response to an inquiry, which may leave invalid transfer
	 * negotiations in effect.  The TUR will reveal the unit attention
	 * condition.  Only send the TUR for lun 0, since some devices
	 * will get confused by commands other than inquiry to non-existent
	 * luns.  If you think a device has gone away start your scan from
	 * lun 0.  This will insure that any bogus transfer settings are
	 * invalidated.
	 *
	 * If we haven't seen the device before and the controller supports
	 * some kind of transfer negotiation, negotiate with the first
	 * sent command if no bus reset was performed at startup.  This
	 * ensures that the device is not confused by transfer negotiation
	 * settings left over by loader or BIOS action.
	 */
	if (((ccb->ccb_h.path->device->flags & CAM_DEV_UNCONFIGURED) == 0)
	 && (ccb->ccb_h.target_lun == 0)) {
		PROBE_SET_ACTION(softc, PROBE_TUR);
	} else if ((cpi.hba_inquiry & (PI_WIDE_32|PI_WIDE_16|PI_SDTR_ABLE)) != 0
	      && (cpi.hba_misc & PIM_NOBUSRESET) != 0) {
		proberequestdefaultnegotiation(periph);
		PROBE_SET_ACTION(softc, PROBE_INQUIRY);
	} else {
		PROBE_SET_ACTION(softc, PROBE_INQUIRY);
	}

	if (ccb->crcn.flags & CAM_EXPECT_INQ_CHANGE)
		softc->flags |= PROBE_NO_ANNOUNCE;
	else
		softc->flags &= ~PROBE_NO_ANNOUNCE;

	if (cpi.hba_misc & PIM_EXTLUNS)
		softc->flags |= PROBE_EXTLUN;
	else
		softc->flags &= ~PROBE_EXTLUN;

	xpt_schedule(periph, CAM_PRIORITY_XPT);
}