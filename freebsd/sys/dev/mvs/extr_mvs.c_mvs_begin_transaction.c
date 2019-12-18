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
struct TYPE_14__ {scalar_t__ func_code; size_t target_id; int flags; } ;
struct TYPE_11__ {int* cdb_ptr; int* cdb_bytes; } ;
struct TYPE_12__ {TYPE_3__ cdb_io; } ;
struct TYPE_9__ {int flags; } ;
struct TYPE_10__ {TYPE_1__ cmd; } ;
union ccb {TYPE_6__ ccb_h; TYPE_4__ csio; TYPE_2__ ataio; } ;
typedef  int uint8_t ;
struct TYPE_16__ {int /*<<< orphan*/  data_map; } ;
struct mvs_slot {int tag; int slot; TYPE_8__ dma; int /*<<< orphan*/  state; union ccb* ccb; } ;
struct TYPE_15__ {int /*<<< orphan*/  data_tag; } ;
struct mvs_channel {int pm_level; int oslots; int quirks; int* otagspd; scalar_t__ numrslots; size_t taggedtarget; scalar_t__ numpslots; int aslots; int basic_dma; TYPE_7__ dma; TYPE_5__* curr; int /*<<< orphan*/  numdslots; int /*<<< orphan*/ * numtslotspd; int /*<<< orphan*/  numtslots; int /*<<< orphan*/ * numrslotspd; int /*<<< orphan*/  pm_timer; struct mvs_slot* slot; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_13__ {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ ATA_DMA ; 
 int CAM_ATAIO_CONTROL ; 
 int CAM_ATAIO_DMA ; 
 int CAM_ATAIO_FPDMA ; 
 int CAM_ATAIO_NEEDRESULT ; 
 int CAM_CDB_POINTER ; 
 int CAM_DIR_MASK ; 
 int CAM_DIR_NONE ; 
 int /*<<< orphan*/  MVS_EDMA_NCQ ; 
 int /*<<< orphan*/  MVS_EDMA_OFF ; 
 int /*<<< orphan*/  MVS_EDMA_ON ; 
 int MVS_Q_GENIIE ; 
 int MVS_Q_SOC ; 
 int /*<<< orphan*/  MVS_SLOT_LOADING ; 
 scalar_t__ XPT_ATA_IO ; 
 int /*<<< orphan*/  bus_dmamap_load_ccb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ccb*,int /*<<< orphan*/ ,struct mvs_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 struct mvs_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int ffs (int) ; 
 int /*<<< orphan*/  mvs_ch_pm_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_dmasetprd ; 
 int /*<<< orphan*/  mvs_legacy_execute_transaction (struct mvs_slot*) ; 
 int /*<<< orphan*/  mvs_set_edma_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_softreset (int /*<<< orphan*/ ,union ccb*) ; 

__attribute__((used)) static void
mvs_begin_transaction(device_t dev, union ccb *ccb)
{
	struct mvs_channel *ch = device_get_softc(dev);
	struct mvs_slot *slot;
	int slotn, tag;

	if (ch->pm_level > 0)
		mvs_ch_pm_wake(dev);
	/* Softreset is a special case. */
	if (ccb->ccb_h.func_code == XPT_ATA_IO &&
	    (ccb->ataio.cmd.flags & CAM_ATAIO_CONTROL)) {
		mvs_softreset(dev, ccb);
		return;
	}
	/* Choose empty slot. */
	slotn = ffs(~ch->oslots) - 1;
	if ((ccb->ccb_h.func_code == XPT_ATA_IO) &&
	    (ccb->ataio.cmd.flags & CAM_ATAIO_FPDMA)) {
		if (ch->quirks & MVS_Q_GENIIE)
			tag = ffs(~ch->otagspd[ccb->ccb_h.target_id]) - 1;
		else
			tag = slotn;
	} else
		tag = 0;
	/* Occupy chosen slot. */
	slot = &ch->slot[slotn];
	slot->ccb = ccb;
	slot->tag = tag;
	/* Stop PM timer. */
	if (ch->numrslots == 0 && ch->pm_level > 3)
		callout_stop(&ch->pm_timer);
	/* Update channel stats. */
	ch->oslots |= (1 << slot->slot);
	ch->numrslots++;
	ch->numrslotspd[ccb->ccb_h.target_id]++;
	if (ccb->ccb_h.func_code == XPT_ATA_IO) {
		if (ccb->ataio.cmd.flags & CAM_ATAIO_FPDMA) {
			ch->otagspd[ccb->ccb_h.target_id] |= (1 << slot->tag);
			ch->numtslots++;
			ch->numtslotspd[ccb->ccb_h.target_id]++;
			ch->taggedtarget = ccb->ccb_h.target_id;
			mvs_set_edma_mode(dev, MVS_EDMA_NCQ);
		} else if (ccb->ataio.cmd.flags & CAM_ATAIO_DMA) {
			ch->numdslots++;
			mvs_set_edma_mode(dev, MVS_EDMA_ON);
		} else {
			ch->numpslots++;
			mvs_set_edma_mode(dev, MVS_EDMA_OFF);
		}
		if (ccb->ataio.cmd.flags &
		    (CAM_ATAIO_CONTROL | CAM_ATAIO_NEEDRESULT)) {
			ch->aslots |= (1 << slot->slot);
		}
	} else {
		uint8_t *cdb = (ccb->ccb_h.flags & CAM_CDB_POINTER) ?
		    ccb->csio.cdb_io.cdb_ptr : ccb->csio.cdb_io.cdb_bytes;
		ch->numpslots++;
		/* Use ATAPI DMA only for commands without under-/overruns. */
		if ((ccb->ccb_h.flags & CAM_DIR_MASK) != CAM_DIR_NONE &&
		    ch->curr[ccb->ccb_h.target_id].mode >= ATA_DMA &&
		    (ch->quirks & MVS_Q_SOC) == 0 &&
		    (cdb[0] == 0x08 ||
		     cdb[0] == 0x0a ||
		     cdb[0] == 0x28 ||
		     cdb[0] == 0x2a ||
		     cdb[0] == 0x88 ||
		     cdb[0] == 0x8a ||
		     cdb[0] == 0xa8 ||
		     cdb[0] == 0xaa ||
		     cdb[0] == 0xbe)) {
			ch->basic_dma = 1;
		}
		mvs_set_edma_mode(dev, MVS_EDMA_OFF);
	}
	if (ch->numpslots == 0 || ch->basic_dma) {
		slot->state = MVS_SLOT_LOADING;
		bus_dmamap_load_ccb(ch->dma.data_tag, slot->dma.data_map,
		    ccb, mvs_dmasetprd, slot, 0);
	} else
		mvs_legacy_execute_transaction(slot);
}