#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int recovery_slot; int status; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct siis_channel {int /*<<< orphan*/  numhslots; TYPE_3__** hold; scalar_t__ recoverycmd; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {int status; } ;
struct TYPE_6__ {TYPE_2__ ccb_h; } ;

/* Variables and functions */
 int CAM_AUTOSENSE_FAIL ; 
 int CAM_AUTOSNS_VALID ; 
 int CAM_REQ_CMP ; 
 int CAM_STATUS_MASK ; 
 struct siis_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (TYPE_3__*) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 

__attribute__((used)) static void
siis_process_request_sense(device_t dev, union ccb *ccb)
{
	struct siis_channel *ch = device_get_softc(dev);
	int i;

	ch->recoverycmd = 0;

	i = ccb->ccb_h.recovery_slot;
	if ((ccb->ccb_h.status & CAM_STATUS_MASK) == CAM_REQ_CMP) {
		ch->hold[i]->ccb_h.status |= CAM_AUTOSNS_VALID;
	} else {
		ch->hold[i]->ccb_h.status &= ~CAM_STATUS_MASK;
		ch->hold[i]->ccb_h.status |= CAM_AUTOSENSE_FAIL;
	}
	xpt_done(ch->hold[i]);
	ch->hold[i] = NULL;
	ch->numhslots--;
	xpt_free_ccb(ccb);
}