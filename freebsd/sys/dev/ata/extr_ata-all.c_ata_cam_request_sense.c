#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t target_id; int timeout; } ;
struct TYPE_9__ {int /*<<< orphan*/  sense_len; int /*<<< orphan*/  sense_data; } ;
union ccb {TYPE_5__ ccb_h; TYPE_3__ csio; } ;
struct TYPE_7__ {int /*<<< orphan*/ * ccb; } ;
struct TYPE_8__ {TYPE_1__ atapi; } ;
struct ata_request {size_t unit; int timeout; union ccb* ccb; int /*<<< orphan*/  callout; scalar_t__ retries; int /*<<< orphan*/  bytecount; int /*<<< orphan*/  transfersize; int /*<<< orphan*/  flags; TYPE_2__ u; void* data; int /*<<< orphan*/  parent; int /*<<< orphan*/ * dev; } ;
struct TYPE_12__ {scalar_t__ (* begin_transaction ) (struct ata_request*) ;} ;
struct ata_channel {int requestsense; int /*<<< orphan*/  state; struct ata_request* running; TYPE_6__ hw; int /*<<< orphan*/  state_mtx; TYPE_4__* curr; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_10__ {int atapi; scalar_t__ mode; int /*<<< orphan*/  bytecount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATAPI_REQUEST_SENSE ; 
 int /*<<< orphan*/  ATA_ACTIVE ; 
 scalar_t__ ATA_DMA ; 
 int /*<<< orphan*/  ATA_IDLE ; 
 scalar_t__ ATA_OP_FINISHED ; 
 int /*<<< orphan*/  ATA_R_ATAPI ; 
 int /*<<< orphan*/  ATA_R_ATAPI16 ; 
 int /*<<< orphan*/  ATA_R_DMA ; 
 int /*<<< orphan*/  ATA_R_READ ; 
 int /*<<< orphan*/  CALLOUT_RETURNUNLOCKED ; 
 int /*<<< orphan*/  ata_cam_end_transaction (int /*<<< orphan*/ ,struct ata_request*) ; 
 int /*<<< orphan*/  bzero (struct ata_request*,int) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct ata_request*) ; 

__attribute__((used)) static void
ata_cam_request_sense(device_t dev, struct ata_request *request)
{
	struct ata_channel *ch = device_get_softc(dev);
	union ccb *ccb = request->ccb;

	ch->requestsense = 1;

	bzero(request, sizeof(*request));
	request->dev = NULL;
	request->parent = dev;
	request->unit = ccb->ccb_h.target_id;
	request->data = (void *)&ccb->csio.sense_data;
	request->bytecount = ccb->csio.sense_len;
	request->u.atapi.ccb[0] = ATAPI_REQUEST_SENSE;
	request->u.atapi.ccb[4] = ccb->csio.sense_len;
	request->flags |= ATA_R_ATAPI;
	if (ch->curr[ccb->ccb_h.target_id].atapi == 16)
		request->flags |= ATA_R_ATAPI16;
	if (ch->curr[ccb->ccb_h.target_id].mode >= ATA_DMA)
		request->flags |= ATA_R_DMA;
	request->flags |= ATA_R_READ;
	request->transfersize = min(request->bytecount,
	    ch->curr[ccb->ccb_h.target_id].bytecount);
	request->retries = 0;
	request->timeout = (ccb->ccb_h.timeout + 999) / 1000;
	callout_init_mtx(&request->callout, &ch->state_mtx, CALLOUT_RETURNUNLOCKED);
	request->ccb = ccb;

	ch->running = request;
	ch->state = ATA_ACTIVE;
	if (ch->hw.begin_transaction(request) == ATA_OP_FINISHED) {
		ch->running = NULL;
		ch->state = ATA_IDLE;
		ata_cam_end_transaction(dev, request);
		return;
	}
}