#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int target_id; int flags; scalar_t__ func_code; int timeout; } ;
struct TYPE_8__ {int flags; int control; scalar_t__ command; } ;
struct TYPE_9__ {TYPE_3__ cmd; } ;
union ccb {TYPE_5__ ccb_h; TYPE_4__ ataio; } ;
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  timeout_t ;
struct TYPE_6__ {int nsegs; } ;
struct ahci_slot {int slot; int /*<<< orphan*/  timeout; int /*<<< orphan*/  state; TYPE_1__ dma; union ccb* ccb; struct ahci_channel* ch; } ;
struct ahci_cmd_tab {int dummy; } ;
struct ahci_cmd_list {int /*<<< orphan*/  cmd_table_phys; void* cmd_flags; scalar_t__ bytecount; void* prd_length; } ;
struct TYPE_7__ {int* rfis; int /*<<< orphan*/  rfis_map; int /*<<< orphan*/  rfis_tag; int /*<<< orphan*/  work_map; int /*<<< orphan*/  work_tag; scalar_t__ work_bus; scalar_t__ work; } ;
struct ahci_channel {int rslots; int quirks; int eslots; int /*<<< orphan*/  r_mem; int /*<<< orphan*/  dev; TYPE_2__ dma; scalar_t__ fbs_enabled; } ;
typedef  enum ahci_err_type { ____Placeholder_ahci_err_type } ahci_err_type ;

/* Variables and functions */
 scalar_t__ AHCI_CL_OFFSET ; 
 int AHCI_CL_SIZE ; 
 int AHCI_CMD_ATAPI ; 
 int AHCI_CMD_CLR_BUSY ; 
 int AHCI_CMD_PREFETCH ; 
 int AHCI_CMD_RESET ; 
 int AHCI_CMD_WRITE ; 
 scalar_t__ AHCI_CT_OFFSET ; 
 int AHCI_CT_SIZE ; 
 int AHCI_ERR_INVALID ; 
 int AHCI_ERR_NONE ; 
 int AHCI_ERR_TFE ; 
 int AHCI_ERR_TIMEOUT ; 
 int /*<<< orphan*/  AHCI_P_CI ; 
 int /*<<< orphan*/  AHCI_P_CMD ; 
 int /*<<< orphan*/  AHCI_P_FBS ; 
 int AHCI_P_FBS_DEV_SHIFT ; 
 int AHCI_P_FBS_EN ; 
 int /*<<< orphan*/  AHCI_P_IS ; 
 int AHCI_P_IX_IPM ; 
 int /*<<< orphan*/  AHCI_P_SACT ; 
 int /*<<< orphan*/  AHCI_P_SERR ; 
 int /*<<< orphan*/  AHCI_P_TFD ; 
 int AHCI_Q_ATI_PMP_BUG ; 
 int AHCI_Q_MRVL_SR_DEL ; 
 int AHCI_Q_NOBSYRES ; 
 int /*<<< orphan*/  AHCI_SLOT_RUNNING ; 
 int ATA_A_RESET ; 
 scalar_t__ ATA_DEVICE_RESET ; 
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ATA_S_BUSY ; 
 int ATA_S_ERROR ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int CAM_ATAIO_CONTROL ; 
 int CAM_ATAIO_FPDMA ; 
 int CAM_DIR_OUT ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int SBT_1MS ; 
 scalar_t__ XPT_ATA_IO ; 
 scalar_t__ XPT_SCSI_IO ; 
 int /*<<< orphan*/  ahci_clo (struct ahci_channel*) ; 
 int /*<<< orphan*/  ahci_end_transaction (struct ahci_slot*,int) ; 
 int ahci_setup_fis (struct ahci_channel*,struct ahci_cmd_tab*,union ccb*,int) ; 
 int /*<<< orphan*/  ahci_start (struct ahci_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahci_stop (struct ahci_channel*) ; 
 scalar_t__ ahci_timeout ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ahci_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 void* htole16 (int) ; 
 int /*<<< orphan*/  htole64 (scalar_t__) ; 

__attribute__((used)) static void
ahci_execute_transaction(struct ahci_slot *slot)
{
	struct ahci_channel *ch = slot->ch;
	struct ahci_cmd_tab *ctp;
	struct ahci_cmd_list *clp;
	union ccb *ccb = slot->ccb;
	int port = ccb->ccb_h.target_id & 0x0f;
	int fis_size, i, softreset;
	uint8_t *fis = ch->dma.rfis + 0x40;
	uint8_t val;
	uint16_t cmd_flags;

	/* Get a piece of the workspace for this request */
	ctp = (struct ahci_cmd_tab *)
		(ch->dma.work + AHCI_CT_OFFSET + (AHCI_CT_SIZE * slot->slot));
	/* Setup the FIS for this request */
	if (!(fis_size = ahci_setup_fis(ch, ctp, ccb, slot->slot))) {
		device_printf(ch->dev, "Setting up SATA FIS failed\n");
		ahci_end_transaction(slot, AHCI_ERR_INVALID);
		return;
	}
	/* Setup the command list entry */
	clp = (struct ahci_cmd_list *)
	    (ch->dma.work + AHCI_CL_OFFSET + (AHCI_CL_SIZE * slot->slot));
	cmd_flags =
		    (ccb->ccb_h.flags & CAM_DIR_OUT ? AHCI_CMD_WRITE : 0) |
		    (ccb->ccb_h.func_code == XPT_SCSI_IO ?
		     (AHCI_CMD_ATAPI | AHCI_CMD_PREFETCH) : 0) |
		    (fis_size / sizeof(u_int32_t)) |
		    (port << 12);
	clp->prd_length = htole16(slot->dma.nsegs);
	/* Special handling for Soft Reset command. */
	if ((ccb->ccb_h.func_code == XPT_ATA_IO) &&
	    (ccb->ataio.cmd.flags & CAM_ATAIO_CONTROL)) {
		if (ccb->ataio.cmd.control & ATA_A_RESET) {
			softreset = 1;
			/* Kick controller into sane state */
			ahci_stop(ch);
			ahci_clo(ch);
			ahci_start(ch, 0);
			cmd_flags |= AHCI_CMD_RESET | AHCI_CMD_CLR_BUSY;
		} else {
			softreset = 2;
			/* Prepare FIS receive area for check. */
			for (i = 0; i < 20; i++)
				fis[i] = 0xff;
		}
	} else
		softreset = 0;
	clp->bytecount = 0;
	clp->cmd_flags = htole16(cmd_flags);
	clp->cmd_table_phys = htole64(ch->dma.work_bus + AHCI_CT_OFFSET +
				  (AHCI_CT_SIZE * slot->slot));
	bus_dmamap_sync(ch->dma.work_tag, ch->dma.work_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
	bus_dmamap_sync(ch->dma.rfis_tag, ch->dma.rfis_map,
	    BUS_DMASYNC_PREREAD);
	/* Set ACTIVE bit for NCQ commands. */
	if ((ccb->ccb_h.func_code == XPT_ATA_IO) &&
	    (ccb->ataio.cmd.flags & CAM_ATAIO_FPDMA)) {
		ATA_OUTL(ch->r_mem, AHCI_P_SACT, 1 << slot->slot);
	}
	/* If FBS is enabled, set PMP port. */
	if (ch->fbs_enabled) {
		ATA_OUTL(ch->r_mem, AHCI_P_FBS, AHCI_P_FBS_EN |
		    (port << AHCI_P_FBS_DEV_SHIFT));
	}
	/* Issue command to the controller. */
	slot->state = AHCI_SLOT_RUNNING;
	ch->rslots |= (1 << slot->slot);
	ATA_OUTL(ch->r_mem, AHCI_P_CI, (1 << slot->slot));
	/* Device reset commands doesn't interrupt. Poll them. */
	if (ccb->ccb_h.func_code == XPT_ATA_IO &&
	    (ccb->ataio.cmd.command == ATA_DEVICE_RESET || softreset)) {
		int count, timeout = ccb->ccb_h.timeout * 100;
		enum ahci_err_type et = AHCI_ERR_NONE;

		for (count = 0; count < timeout; count++) {
			DELAY(10);
			if (!(ATA_INL(ch->r_mem, AHCI_P_CI) & (1 << slot->slot)))
				break;
			if ((ATA_INL(ch->r_mem, AHCI_P_TFD) & ATA_S_ERROR) &&
			    softreset != 1) {
#if 0
				device_printf(ch->dev,
				    "Poll error on slot %d, TFD: %04x\n",
				    slot->slot, ATA_INL(ch->r_mem, AHCI_P_TFD));
#endif
				et = AHCI_ERR_TFE;
				break;
			}
			/* Workaround for ATI SB600/SB700 chipsets. */
			if (ccb->ccb_h.target_id == 15 &&
			    (ch->quirks & AHCI_Q_ATI_PMP_BUG) &&
			    (ATA_INL(ch->r_mem, AHCI_P_IS) & AHCI_P_IX_IPM)) {
				et = AHCI_ERR_TIMEOUT;
				break;
			}
		}

		/*
		 * Some Marvell controllers require additional time
		 * after soft reset to work properly. Setup delay
		 * to 50ms after soft reset.
		 */
		if (ch->quirks & AHCI_Q_MRVL_SR_DEL)
			DELAY(50000);

		/*
		 * Marvell HBAs with non-RAID firmware do not wait for
		 * readiness after soft reset, so we have to wait here.
		 * Marvell RAIDs do not have this problem, but instead
		 * sometimes forget to update FIS receive area, breaking
		 * this wait.
		 */
		if ((ch->quirks & AHCI_Q_NOBSYRES) == 0 &&
		    (ch->quirks & AHCI_Q_ATI_PMP_BUG) == 0 &&
		    softreset == 2 && et == AHCI_ERR_NONE) {
			for ( ; count < timeout; count++) {
				bus_dmamap_sync(ch->dma.rfis_tag,
				    ch->dma.rfis_map, BUS_DMASYNC_POSTREAD);
				val = fis[2];
				bus_dmamap_sync(ch->dma.rfis_tag,
				    ch->dma.rfis_map, BUS_DMASYNC_PREREAD);
				if ((val & ATA_S_BUSY) == 0)
					break;
				DELAY(10);
			}
		}

		if (timeout && (count >= timeout)) {
			device_printf(ch->dev, "Poll timeout on slot %d port %d\n",
			    slot->slot, port);
			device_printf(ch->dev, "is %08x cs %08x ss %08x "
			    "rs %08x tfd %02x serr %08x cmd %08x\n",
			    ATA_INL(ch->r_mem, AHCI_P_IS),
			    ATA_INL(ch->r_mem, AHCI_P_CI),
			    ATA_INL(ch->r_mem, AHCI_P_SACT), ch->rslots,
			    ATA_INL(ch->r_mem, AHCI_P_TFD),
			    ATA_INL(ch->r_mem, AHCI_P_SERR),
			    ATA_INL(ch->r_mem, AHCI_P_CMD));
			et = AHCI_ERR_TIMEOUT;
		}

		/* Kick controller into sane state and enable FBS. */
		if (softreset == 2)
			ch->eslots |= (1 << slot->slot);
		ahci_end_transaction(slot, et);
		return;
	}
	/* Start command execution timeout */
	callout_reset_sbt(&slot->timeout, SBT_1MS * ccb->ccb_h.timeout / 2,
	    0, (timeout_t*)ahci_timeout, slot, 0);
	return;
}