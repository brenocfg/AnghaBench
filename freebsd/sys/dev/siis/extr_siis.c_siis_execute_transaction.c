#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ func_code; int flags; int timeout; } ;
struct TYPE_5__ {int flags; int control; } ;
struct TYPE_6__ {TYPE_1__ cmd; } ;
union ccb {TYPE_4__ ccb_h; TYPE_2__ ataio; } ;
typedef  int u_int64_t ;
typedef  int /*<<< orphan*/  timeout_t ;
struct siis_slot {int slot; int /*<<< orphan*/  timeout; int /*<<< orphan*/  state; union ccb* ccb; int /*<<< orphan*/  dev; } ;
struct siis_cmd {int /*<<< orphan*/  control; int /*<<< orphan*/  protocol_override; scalar_t__ transfer_count; } ;
struct TYPE_7__ {int work; int work_bus; int /*<<< orphan*/  work_map; int /*<<< orphan*/  work_tag; } ;
struct siis_channel {int rslots; int /*<<< orphan*/  r_mem; TYPE_3__ dma; int /*<<< orphan*/  sim; int /*<<< orphan*/  recoverycmd; int /*<<< orphan*/  dev; int /*<<< orphan*/  mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_A_RESET ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int CAM_ATAIO_CONTROL ; 
 int CAM_ATAIO_FPDMA ; 
 int CAM_DIR_IN ; 
 int CAM_DIR_MASK ; 
 int CAM_DIR_OUT ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int SBT_1MS ; 
 int SIIS_CT_OFFSET ; 
 int SIIS_CT_SIZE ; 
 int /*<<< orphan*/  SIIS_ERR_INVALID ; 
 int /*<<< orphan*/  SIIS_PRB_PACKET_READ ; 
 int /*<<< orphan*/  SIIS_PRB_PACKET_WRITE ; 
 int /*<<< orphan*/  SIIS_PRB_PROTOCOL_OVERRIDE ; 
 int /*<<< orphan*/  SIIS_PRB_PROTO_NCQ ; 
 int /*<<< orphan*/  SIIS_PRB_PROTO_READ ; 
 int /*<<< orphan*/  SIIS_PRB_PROTO_WRITE ; 
 int /*<<< orphan*/  SIIS_PRB_SOFT_RESET ; 
 int /*<<< orphan*/  SIIS_P_CACTH (int) ; 
 int /*<<< orphan*/  SIIS_P_CACTL (int) ; 
 int /*<<< orphan*/  SIIS_SLOT_RUNNING ; 
 scalar_t__ XPT_ATA_IO ; 
 scalar_t__ XPT_SCSI_IO ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct siis_slot*,int /*<<< orphan*/ ) ; 
 struct siis_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siis_end_transaction (struct siis_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siis_portinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siis_setup_fis (int /*<<< orphan*/ ,struct siis_cmd*,union ccb*,int) ; 
 scalar_t__ siis_timeout ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
siis_execute_transaction(struct siis_slot *slot)
{
	device_t dev = slot->dev;
	struct siis_channel *ch = device_get_softc(dev);
	struct siis_cmd *ctp;
	union ccb *ccb = slot->ccb;
	u_int64_t prb_bus;

	mtx_assert(&ch->mtx, MA_OWNED);
	/* Get a piece of the workspace for this request */
	ctp = (struct siis_cmd *)
		(ch->dma.work + SIIS_CT_OFFSET + (SIIS_CT_SIZE * slot->slot));
	ctp->control = 0;
	ctp->protocol_override = 0;
	ctp->transfer_count = 0;
	/* Special handling for Soft Reset command. */
	if (ccb->ccb_h.func_code == XPT_ATA_IO) {
		if (ccb->ataio.cmd.flags & CAM_ATAIO_CONTROL) {
			ctp->control |= htole16(SIIS_PRB_SOFT_RESET);
		} else {
			ctp->control |= htole16(SIIS_PRB_PROTOCOL_OVERRIDE);
			if (ccb->ataio.cmd.flags & CAM_ATAIO_FPDMA) {
				ctp->protocol_override |=
				    htole16(SIIS_PRB_PROTO_NCQ);
			}
			if ((ccb->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_IN) {
				ctp->protocol_override |=
				    htole16(SIIS_PRB_PROTO_READ);
			} else
			if ((ccb->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_OUT) {
				ctp->protocol_override |=
				    htole16(SIIS_PRB_PROTO_WRITE);
			}
		}
	} else if (ccb->ccb_h.func_code == XPT_SCSI_IO) {
		if ((ccb->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_IN)
			ctp->control |= htole16(SIIS_PRB_PACKET_READ);
		else
		if ((ccb->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_OUT)
			ctp->control |= htole16(SIIS_PRB_PACKET_WRITE);
	}
	/* Special handling for Soft Reset command. */
	if ((ccb->ccb_h.func_code == XPT_ATA_IO) &&
	    (ccb->ataio.cmd.flags & CAM_ATAIO_CONTROL) &&
	    (ccb->ataio.cmd.control & ATA_A_RESET)) {
		/* Kick controller into sane state */
		siis_portinit(dev);
	}
	/* Setup the FIS for this request */
	if (!siis_setup_fis(dev, ctp, ccb, slot->slot)) {
		device_printf(ch->dev, "Setting up SATA FIS failed\n");
		if (!ch->recoverycmd)
			xpt_freeze_simq(ch->sim, 1);
		siis_end_transaction(slot, SIIS_ERR_INVALID);
		return;
	}
	bus_dmamap_sync(ch->dma.work_tag, ch->dma.work_map,
	    BUS_DMASYNC_PREWRITE);
	/* Issue command to the controller. */
	slot->state = SIIS_SLOT_RUNNING;
	ch->rslots |= (1 << slot->slot);
	prb_bus = ch->dma.work_bus +
	      SIIS_CT_OFFSET + (SIIS_CT_SIZE * slot->slot);
	ATA_OUTL(ch->r_mem, SIIS_P_CACTL(slot->slot), prb_bus);
	ATA_OUTL(ch->r_mem, SIIS_P_CACTH(slot->slot), prb_bus >> 32);
	/* Start command execution timeout */
	callout_reset_sbt(&slot->timeout, SBT_1MS * ccb->ccb_h.timeout, 0,
	    (timeout_t*)siis_timeout, slot, 0);
	return;
}