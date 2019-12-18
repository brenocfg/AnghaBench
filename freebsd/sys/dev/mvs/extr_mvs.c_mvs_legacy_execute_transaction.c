#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int target_id; scalar_t__ func_code; int flags; int timeout; } ;
struct TYPE_9__ {scalar_t__ cdb_bytes; scalar_t__ cdb_ptr; } ;
struct TYPE_15__ {TYPE_1__ cdb_io; int /*<<< orphan*/  dxfer_len; } ;
struct TYPE_12__ {scalar_t__ command; } ;
struct TYPE_11__ {int status; } ;
struct TYPE_14__ {scalar_t__ data_ptr; int /*<<< orphan*/  dxfer_len; TYPE_4__ cmd; TYPE_3__ res; } ;
union ccb {TYPE_5__ ccb_h; TYPE_7__ csio; TYPE_6__ ataio; } ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  timeout_t ;
struct mvs_slot {int slot; int /*<<< orphan*/  timeout; int /*<<< orphan*/  state; union ccb* ccb; int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {int workrq_bus; } ;
struct mvs_channel {int rslots; int transfersize; int fake_busy; int toslots; int /*<<< orphan*/  r_mem; TYPE_2__ dma; scalar_t__ basic_dma; TYPE_8__* curr; int /*<<< orphan*/  sim; scalar_t__ donecount; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int bus_addr_t ;
struct TYPE_16__ {int bytecount; int atapi; } ;

/* Variables and functions */
 int ATAPI_P_CMDOUT ; 
 int /*<<< orphan*/  ATA_COMMAND ; 
 int /*<<< orphan*/  ATA_CYL_LSB ; 
 int /*<<< orphan*/  ATA_CYL_MSB ; 
 int /*<<< orphan*/  ATA_DATA ; 
 scalar_t__ ATA_DEVICE_RESET ; 
 int /*<<< orphan*/  ATA_FEATURE ; 
 int ATA_F_DMA ; 
 void* ATA_INB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_IREASON ; 
 int ATA_I_CMD ; 
 int ATA_I_IN ; 
 int /*<<< orphan*/  ATA_OUTB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATA_OUTSW_STRM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int ATA_PACKET_CMD ; 
 scalar_t__ ATA_READ_MUL ; 
 scalar_t__ ATA_READ_MUL48 ; 
 int /*<<< orphan*/  ATA_STATUS ; 
 int ATA_S_BUSY ; 
 int ATA_S_DRQ ; 
 scalar_t__ ATA_WRITE_MUL ; 
 scalar_t__ ATA_WRITE_MUL48 ; 
 int CAM_CDB_POINTER ; 
 int CAM_DIR_IN ; 
 int CAM_DIR_MASK ; 
 int CAM_DIR_NONE ; 
 int CAM_DIR_OUT ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DMA_C ; 
 int DMA_C_READ ; 
 int DMA_C_START ; 
 int /*<<< orphan*/  DMA_DTHBA ; 
 int /*<<< orphan*/  DMA_DTLBA ; 
 int MVS_EPRD_OFFSET ; 
 int MVS_EPRD_SIZE ; 
 int /*<<< orphan*/  MVS_ERR_TIMEOUT ; 
 int /*<<< orphan*/  MVS_SLOT_RUNNING ; 
 int /*<<< orphan*/  SATA_SATAICTL ; 
 int SATA_SATAICTL_PMPTX_SHIFT ; 
 int SBT_1MS ; 
 scalar_t__ XPT_ATA_IO ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mvs_slot*,int /*<<< orphan*/ ) ; 
 struct mvs_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 void* min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvs_end_transaction (struct mvs_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_legacy_intr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvs_tfd_write (int /*<<< orphan*/ ,union ccb*) ; 
 scalar_t__ mvs_timeout ; 
 scalar_t__ mvs_wait (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mvs_legacy_execute_transaction(struct mvs_slot *slot)
{
	device_t dev = slot->dev;
	struct mvs_channel *ch = device_get_softc(dev);
	bus_addr_t eprd;
	union ccb *ccb = slot->ccb;
	int port = ccb->ccb_h.target_id & 0x0f;
	int timeout;

	slot->state = MVS_SLOT_RUNNING;
	ch->rslots |= (1 << slot->slot);
	ATA_OUTB(ch->r_mem, SATA_SATAICTL, port << SATA_SATAICTL_PMPTX_SHIFT);
	if (ccb->ccb_h.func_code == XPT_ATA_IO) {
		mvs_tfd_write(dev, ccb);
		/* Device reset doesn't interrupt. */
		if (ccb->ataio.cmd.command == ATA_DEVICE_RESET) {
			int timeout = 1000000;
			do {
			    DELAY(10);
			    ccb->ataio.res.status = ATA_INB(ch->r_mem, ATA_STATUS);
			} while (ccb->ataio.res.status & ATA_S_BUSY && timeout--);
			mvs_legacy_intr(dev, 1);
			return;
		}
		ch->donecount = 0;
		if (ccb->ataio.cmd.command == ATA_READ_MUL ||
		    ccb->ataio.cmd.command == ATA_READ_MUL48 ||
		    ccb->ataio.cmd.command == ATA_WRITE_MUL ||
		    ccb->ataio.cmd.command == ATA_WRITE_MUL48) {
			ch->transfersize = min(ccb->ataio.dxfer_len,
			    ch->curr[port].bytecount);
		} else
			ch->transfersize = min(ccb->ataio.dxfer_len, 512);
		if ((ccb->ccb_h.flags & CAM_DIR_MASK) != CAM_DIR_NONE)
			ch->fake_busy = 1;
		/* If data write command - output the data */
		if ((ccb->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_OUT) {
			if (mvs_wait(dev, ATA_S_DRQ, ATA_S_BUSY, 1000) < 0) {
				device_printf(dev,
				    "timeout waiting for write DRQ\n");
				xpt_freeze_simq(ch->sim, 1);
				ch->toslots |= (1 << slot->slot);
				mvs_end_transaction(slot, MVS_ERR_TIMEOUT);
				return;
			}
			ATA_OUTSW_STRM(ch->r_mem, ATA_DATA,
			   (uint16_t *)(ccb->ataio.data_ptr + ch->donecount),
			   ch->transfersize / 2);
		}
	} else {
		ch->donecount = 0;
		ch->transfersize = min(ccb->csio.dxfer_len,
		    ch->curr[port].bytecount);
		/* Write ATA PACKET command. */
		if (ch->basic_dma) {
			ATA_OUTB(ch->r_mem, ATA_FEATURE, ATA_F_DMA);
			ATA_OUTB(ch->r_mem, ATA_CYL_LSB, 0);
		    	ATA_OUTB(ch->r_mem, ATA_CYL_MSB, 0);
		} else {
			ATA_OUTB(ch->r_mem, ATA_FEATURE, 0);
			ATA_OUTB(ch->r_mem, ATA_CYL_LSB, ch->transfersize);
		    	ATA_OUTB(ch->r_mem, ATA_CYL_MSB, ch->transfersize >> 8);
		}
		ATA_OUTB(ch->r_mem, ATA_COMMAND, ATA_PACKET_CMD);
		ch->fake_busy = 1;
		/* Wait for ready to write ATAPI command block */
		if (mvs_wait(dev, 0, ATA_S_BUSY, 1000) < 0) {
			device_printf(dev, "timeout waiting for ATAPI !BUSY\n");
			xpt_freeze_simq(ch->sim, 1);
			ch->toslots |= (1 << slot->slot);
			mvs_end_transaction(slot, MVS_ERR_TIMEOUT);
			return;
		}
		timeout = 5000;
		while (timeout--) {
		    int reason = ATA_INB(ch->r_mem, ATA_IREASON);
		    int status = ATA_INB(ch->r_mem, ATA_STATUS);

		    if (((reason & (ATA_I_CMD | ATA_I_IN)) |
			 (status & (ATA_S_DRQ | ATA_S_BUSY))) == ATAPI_P_CMDOUT)
			break;
		    DELAY(20);
		}
		if (timeout <= 0) {
			device_printf(dev,
			    "timeout waiting for ATAPI command ready\n");
			xpt_freeze_simq(ch->sim, 1);
			ch->toslots |= (1 << slot->slot);
			mvs_end_transaction(slot, MVS_ERR_TIMEOUT);
			return;
		}
		/* Write ATAPI command. */
		ATA_OUTSW_STRM(ch->r_mem, ATA_DATA,
		   (uint16_t *)((ccb->ccb_h.flags & CAM_CDB_POINTER) ?
		    ccb->csio.cdb_io.cdb_ptr : ccb->csio.cdb_io.cdb_bytes),
		   ch->curr[port].atapi / 2);
		DELAY(10);
		if (ch->basic_dma) {
			/* Start basic DMA. */
			eprd = ch->dma.workrq_bus + MVS_EPRD_OFFSET +
			    (MVS_EPRD_SIZE * slot->slot);
			ATA_OUTL(ch->r_mem, DMA_DTLBA, eprd);
			ATA_OUTL(ch->r_mem, DMA_DTHBA, (eprd >> 16) >> 16);
			ATA_OUTL(ch->r_mem, DMA_C, DMA_C_START |
			    (((ccb->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_IN) ?
			    DMA_C_READ : 0));
		}
	}
	/* Start command execution timeout */
	callout_reset_sbt(&slot->timeout, SBT_1MS * ccb->ccb_h.timeout, 0,
	    (timeout_t*)mvs_timeout, slot, 0);
}