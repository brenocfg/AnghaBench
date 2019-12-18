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
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct ata_request {int flags; int status; scalar_t__ result; union ccb* ccb; } ;
struct ata_channel {scalar_t__ requestsense; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_R_TIMEOUT ; 
 int ATA_S_ERROR ; 
 int /*<<< orphan*/  CAM_AUTOSENSE_FAIL ; 
 int /*<<< orphan*/  CAM_AUTOSNS_VALID ; 
 int /*<<< orphan*/  CAM_STATUS_MASK ; 
 int /*<<< orphan*/  ata_reinit (int /*<<< orphan*/ ) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
ata_cam_process_sense(device_t dev, struct ata_request *request)
{
	struct ata_channel *ch = device_get_softc(dev);
	union ccb *ccb = request->ccb;
	int fatalerr = 0;

	ch->requestsense = 0;

	if (request->flags & ATA_R_TIMEOUT)
		fatalerr = 1;
	if ((request->flags & ATA_R_TIMEOUT) == 0 &&
	    (request->status & ATA_S_ERROR) == 0 &&
	    request->result == 0) {
		ccb->ccb_h.status |= CAM_AUTOSNS_VALID;
	} else {
		ccb->ccb_h.status &= ~CAM_STATUS_MASK;
		ccb->ccb_h.status |= CAM_AUTOSENSE_FAIL;
	}

	xpt_done(ccb);
	/* Do error recovery if needed. */
	if (fatalerr)
		ata_reinit(dev);
}