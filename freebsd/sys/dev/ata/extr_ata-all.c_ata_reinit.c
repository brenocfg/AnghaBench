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
struct ata_request {int /*<<< orphan*/  result; int /*<<< orphan*/  callout; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unload ) (struct ata_request*) ;} ;
struct ata_channel {scalar_t__ state; int /*<<< orphan*/  sim; int /*<<< orphan*/  path; TYPE_1__ dma; struct ata_request* running; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_BUS_RESET ; 
 scalar_t__ ATA_ACTIVE ; 
 scalar_t__ ATA_IDLE ; 
 int /*<<< orphan*/  ATA_RESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERESTART ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ata_cam_end_transaction (int /*<<< orphan*/ ,struct ata_request*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ata_request*) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ata_reinit(device_t dev)
{
    struct ata_channel *ch = device_get_softc(dev);
    struct ata_request *request;

	xpt_freeze_simq(ch->sim, 1);
	if ((request = ch->running)) {
		ch->running = NULL;
		if (ch->state == ATA_ACTIVE)
		    ch->state = ATA_IDLE;
		callout_stop(&request->callout);
		if (ch->dma.unload)
		    ch->dma.unload(request);
		request->result = ERESTART;
		ata_cam_end_transaction(dev, request);
	}
	/* reset the controller HW, the channel and device(s) */
	ATA_RESET(dev);
	/* Tell the XPT about the event */
	xpt_async(AC_BUS_RESET, ch->path, NULL);
	xpt_release_simq(ch->sim, TRUE);
	return(0);
}