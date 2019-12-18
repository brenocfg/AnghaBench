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
struct ata_request {int /*<<< orphan*/  flags; int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unload ) (struct ata_request*) ;} ;
struct ata_channel {scalar_t__ state; int /*<<< orphan*/  state_mtx; int /*<<< orphan*/  dev; int /*<<< orphan*/ * running; TYPE_1__ dma; } ;

/* Variables and functions */
 scalar_t__ ATA_ACTIVE ; 
 int /*<<< orphan*/  ATA_DEBUG_RQ (struct ata_request*,char*) ; 
 scalar_t__ ATA_IDLE ; 
 int /*<<< orphan*/  ATA_R_TIMEOUT ; 
 int /*<<< orphan*/  ata_cam_end_transaction (int /*<<< orphan*/ ,struct ata_request*) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ata_request*) ; 

void
ata_timeout(struct ata_request *request)
{
	struct ata_channel *ch;

	ch = device_get_softc(request->parent);
	//request->flags |= ATA_R_DEBUG;
	ATA_DEBUG_RQ(request, "timeout");

	/*
	 * If we have an ATA_ACTIVE request running, we flag the request
	 * ATA_R_TIMEOUT so ata_cam_end_transaction() will handle it correctly.
	 * Also, NULL out the running request so we wont loose the race with
	 * an eventual interrupt arriving late.
	 */
	if (ch->state == ATA_ACTIVE) {
		request->flags |= ATA_R_TIMEOUT;
		if (ch->dma.unload)
			ch->dma.unload(request);
		ch->running = NULL;
		ch->state = ATA_IDLE;
		ata_cam_end_transaction(ch->dev, request);
	}
	mtx_unlock(&ch->state_mtx);
}