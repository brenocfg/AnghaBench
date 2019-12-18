#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_11__ {size_t target_id; scalar_t__ func_code; int flags; int timeout; } ;
struct TYPE_12__ {int /*<<< orphan*/  cdb_bytes; int /*<<< orphan*/  cdb_ptr; } ;
struct TYPE_14__ {int /*<<< orphan*/  cdb_len; TYPE_1__ cdb_io; int /*<<< orphan*/  dxfer_len; int /*<<< orphan*/  data_ptr; } ;
struct TYPE_19__ {scalar_t__ command; int flags; int device; scalar_t__ lba_low; scalar_t__ lba_mid; scalar_t__ lba_high; scalar_t__ lba_low_exp; scalar_t__ lba_mid_exp; scalar_t__ lba_high_exp; scalar_t__ sector_count; scalar_t__ sector_count_exp; scalar_t__ features; scalar_t__ features_exp; } ;
struct TYPE_20__ {TYPE_8__ cmd; int /*<<< orphan*/  dxfer_len; int /*<<< orphan*/  data_ptr; } ;
union ccb {TYPE_10__ ccb_h; TYPE_3__ csio; TYPE_9__ ataio; } ;
typedef  int uint64_t ;
typedef  int uint16_t ;
struct TYPE_13__ {int /*<<< orphan*/  ccb; } ;
struct TYPE_17__ {scalar_t__ command; int feature; int count; int lba; } ;
struct TYPE_18__ {TYPE_2__ atapi; TYPE_6__ ata; } ;
struct ata_request {size_t unit; int timeout; int /*<<< orphan*/  flags; union ccb* ccb; int /*<<< orphan*/  callout; scalar_t__ retries; int /*<<< orphan*/  bytecount; void* transfersize; TYPE_7__ u; int /*<<< orphan*/  data; int /*<<< orphan*/  parent; int /*<<< orphan*/ * dev; } ;
struct TYPE_16__ {scalar_t__ (* begin_transaction ) (struct ata_request*) ;} ;
struct ata_channel {int /*<<< orphan*/  state; struct ata_request* running; TYPE_5__ hw; int /*<<< orphan*/  state_mtx; TYPE_4__* curr; struct ata_request request; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_15__ {int bytecount; int atapi; scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_ACTIVE ; 
 scalar_t__ ATA_DMA ; 
 int /*<<< orphan*/  ATA_IDLE ; 
 scalar_t__ ATA_OP_FINISHED ; 
 scalar_t__ ATA_READ_MUL ; 
 scalar_t__ ATA_READ_MUL48 ; 
 int /*<<< orphan*/  ATA_R_48BIT ; 
 int /*<<< orphan*/  ATA_R_ATAPI ; 
 int /*<<< orphan*/  ATA_R_ATAPI16 ; 
 int /*<<< orphan*/  ATA_R_DATA_IN_CCB ; 
 int /*<<< orphan*/  ATA_R_DMA ; 
 int /*<<< orphan*/  ATA_R_NEEDRESULT ; 
 int /*<<< orphan*/  ATA_R_READ ; 
 int /*<<< orphan*/  ATA_R_WRITE ; 
 scalar_t__ ATA_WRITE_MUL ; 
 scalar_t__ ATA_WRITE_MUL48 ; 
 int /*<<< orphan*/  CALLOUT_RETURNUNLOCKED ; 
 int CAM_ATAIO_48BIT ; 
 int CAM_ATAIO_DMA ; 
 int CAM_ATAIO_NEEDRESULT ; 
 int CAM_CDB_POINTER ; 
 int CAM_DIR_IN ; 
 int CAM_DIR_MASK ; 
 int CAM_DIR_NONE ; 
 int CAM_DIR_OUT ; 
 scalar_t__ XPT_ATA_IO ; 
 int /*<<< orphan*/  ata_cam_end_transaction (int /*<<< orphan*/ ,struct ata_request*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct ata_request*,int) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 void* min (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct ata_request*) ; 

__attribute__((used)) static void
ata_cam_begin_transaction(device_t dev, union ccb *ccb)
{
	struct ata_channel *ch = device_get_softc(dev);
	struct ata_request *request;

	request = &ch->request;
	bzero(request, sizeof(*request));

	/* setup request */
	request->dev = NULL;
	request->parent = dev;
	request->unit = ccb->ccb_h.target_id;
	if (ccb->ccb_h.func_code == XPT_ATA_IO) {
		request->data = ccb->ataio.data_ptr;
		request->bytecount = ccb->ataio.dxfer_len;
		request->u.ata.command = ccb->ataio.cmd.command;
		request->u.ata.feature = ((uint16_t)ccb->ataio.cmd.features_exp << 8) |
					  (uint16_t)ccb->ataio.cmd.features;
		request->u.ata.count = ((uint16_t)ccb->ataio.cmd.sector_count_exp << 8) |
					(uint16_t)ccb->ataio.cmd.sector_count;
		if (ccb->ataio.cmd.flags & CAM_ATAIO_48BIT) {
			request->flags |= ATA_R_48BIT;
			request->u.ata.lba =
				     ((uint64_t)ccb->ataio.cmd.lba_high_exp << 40) |
				     ((uint64_t)ccb->ataio.cmd.lba_mid_exp << 32) |
				     ((uint64_t)ccb->ataio.cmd.lba_low_exp << 24);
		} else {
			request->u.ata.lba =
				     ((uint64_t)(ccb->ataio.cmd.device & 0x0f) << 24);
		}
		request->u.ata.lba |= ((uint64_t)ccb->ataio.cmd.lba_high << 16) |
				      ((uint64_t)ccb->ataio.cmd.lba_mid << 8) |
				       (uint64_t)ccb->ataio.cmd.lba_low;
		if (ccb->ataio.cmd.flags & CAM_ATAIO_NEEDRESULT)
			request->flags |= ATA_R_NEEDRESULT;
		if ((ccb->ccb_h.flags & CAM_DIR_MASK) != CAM_DIR_NONE &&
		    ccb->ataio.cmd.flags & CAM_ATAIO_DMA)
			request->flags |= ATA_R_DMA;
		if ((ccb->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_IN)
			request->flags |= ATA_R_READ;
		if ((ccb->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_OUT)
			request->flags |= ATA_R_WRITE;
		if (ccb->ataio.cmd.command == ATA_READ_MUL ||
		    ccb->ataio.cmd.command == ATA_READ_MUL48 ||
		    ccb->ataio.cmd.command == ATA_WRITE_MUL ||
		    ccb->ataio.cmd.command == ATA_WRITE_MUL48) {
			request->transfersize = min(request->bytecount,
			    ch->curr[ccb->ccb_h.target_id].bytecount);
		} else
			request->transfersize = min(request->bytecount, 512);
	} else {
		request->data = ccb->csio.data_ptr;
		request->bytecount = ccb->csio.dxfer_len;
		bcopy((ccb->ccb_h.flags & CAM_CDB_POINTER) ?
		    ccb->csio.cdb_io.cdb_ptr : ccb->csio.cdb_io.cdb_bytes,
		    request->u.atapi.ccb, ccb->csio.cdb_len);
		request->flags |= ATA_R_ATAPI;
		if (ch->curr[ccb->ccb_h.target_id].atapi == 16)
			request->flags |= ATA_R_ATAPI16;
		if ((ccb->ccb_h.flags & CAM_DIR_MASK) != CAM_DIR_NONE &&
		    ch->curr[ccb->ccb_h.target_id].mode >= ATA_DMA)
			request->flags |= ATA_R_DMA;
		if ((ccb->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_IN)
			request->flags |= ATA_R_READ;
		if ((ccb->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_OUT)
			request->flags |= ATA_R_WRITE;
		request->transfersize = min(request->bytecount,
		    ch->curr[ccb->ccb_h.target_id].bytecount);
	}
	request->retries = 0;
	request->timeout = (ccb->ccb_h.timeout + 999) / 1000;
	callout_init_mtx(&request->callout, &ch->state_mtx, CALLOUT_RETURNUNLOCKED);
	request->ccb = ccb;
	request->flags |= ATA_R_DATA_IN_CCB;

	ch->running = request;
	ch->state = ATA_ACTIVE;
	if (ch->hw.begin_transaction(request) == ATA_OP_FINISHED) {
	    ch->running = NULL;
	    ch->state = ATA_IDLE;
	    ata_cam_end_transaction(dev, request);
	    return;
	}
}