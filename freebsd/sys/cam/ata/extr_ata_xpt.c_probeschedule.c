#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; } ;
union ccb {TYPE_3__ crcn; } ;
struct cam_periph {TYPE_2__* path; scalar_t__ softc; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  request_ccbs; } ;
typedef  TYPE_4__ probe_softc ;
struct TYPE_7__ {TYPE_1__* device; } ;
struct TYPE_6__ {int flags; scalar_t__ protocol; } ;

/* Variables and functions */
 int CAM_DEV_UNCONFIGURED ; 
 int CAM_EXPECT_INQ_CHANGE ; 
 int /*<<< orphan*/  CAM_PRIORITY_XPT ; 
 int /*<<< orphan*/  PROBE_IDENTIFY ; 
 int /*<<< orphan*/  PROBE_NO_ANNOUNCE ; 
 int /*<<< orphan*/  PROBE_RESET ; 
 int /*<<< orphan*/  PROBE_SET_ACTION (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PROTO_SATAPM ; 
 scalar_t__ PROTO_SEMB ; 
 scalar_t__ TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_schedule (struct cam_periph*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
probeschedule(struct cam_periph *periph)
{
	union ccb *ccb;
	probe_softc *softc;

	softc = (probe_softc *)periph->softc;
	ccb = (union ccb *)TAILQ_FIRST(&softc->request_ccbs);

	if ((periph->path->device->flags & CAM_DEV_UNCONFIGURED) ||
	    periph->path->device->protocol == PROTO_SATAPM ||
	    periph->path->device->protocol == PROTO_SEMB)
		PROBE_SET_ACTION(softc, PROBE_RESET);
	else
		PROBE_SET_ACTION(softc, PROBE_IDENTIFY);

	if (ccb->crcn.flags & CAM_EXPECT_INQ_CHANGE)
		softc->flags |= PROBE_NO_ANNOUNCE;
	else
		softc->flags &= ~PROBE_NO_ANNOUNCE;

	xpt_schedule(periph, CAM_PRIORITY_XPT);
}