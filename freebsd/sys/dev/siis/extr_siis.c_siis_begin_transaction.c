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
struct TYPE_10__ {scalar_t__ func_code; size_t target_id; int flags; } ;
struct TYPE_8__ {int flags; } ;
struct TYPE_9__ {TYPE_2__ cmd; } ;
union ccb {TYPE_4__ ccb_h; TYPE_3__ ataio; } ;
struct TYPE_12__ {int /*<<< orphan*/  data_map; scalar_t__ nsegs; } ;
struct siis_slot {int slot; TYPE_6__ dma; int /*<<< orphan*/  state; union ccb* ccb; } ;
struct TYPE_11__ {int /*<<< orphan*/  data_tag; } ;
struct siis_channel {int oslots; int aslots; TYPE_5__ dma; int /*<<< orphan*/ * numtslots; int /*<<< orphan*/  numrslots; struct siis_slot* slot; TYPE_1__* curr; int /*<<< orphan*/  mtx; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_7__ {int tags; } ;

/* Variables and functions */
 int CAM_ATAIO_CONTROL ; 
 int CAM_ATAIO_FPDMA ; 
 int CAM_ATAIO_NEEDRESULT ; 
 int CAM_DIR_MASK ; 
 int CAM_DIR_NONE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int SIIS_MAX_SLOTS ; 
 int /*<<< orphan*/  SIIS_SLOT_LOADING ; 
 scalar_t__ XPT_ATA_IO ; 
 int /*<<< orphan*/  bus_dmamap_load_ccb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ccb*,int /*<<< orphan*/ ,struct siis_slot*,int /*<<< orphan*/ ) ; 
 struct siis_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int fls (int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siis_dmasetprd ; 
 int /*<<< orphan*/  siis_execute_transaction (struct siis_slot*) ; 

__attribute__((used)) static void
siis_begin_transaction(device_t dev, union ccb *ccb)
{
	struct siis_channel *ch = device_get_softc(dev);
	struct siis_slot *slot;
	int tag, tags;

	mtx_assert(&ch->mtx, MA_OWNED);
	/* Choose empty slot. */
	tags = SIIS_MAX_SLOTS;
	if ((ccb->ccb_h.func_code == XPT_ATA_IO) &&
	    (ccb->ataio.cmd.flags & CAM_ATAIO_FPDMA))
		tags = ch->curr[ccb->ccb_h.target_id].tags;
	tag = fls((~ch->oslots) & (0x7fffffff >> (31 - tags))) - 1;
	/* Occupy chosen slot. */
	slot = &ch->slot[tag];
	slot->ccb = ccb;
	/* Update channel stats. */
	ch->oslots |= (1 << slot->slot);
	ch->numrslots++;
	if ((ccb->ccb_h.func_code == XPT_ATA_IO) &&
	    (ccb->ataio.cmd.flags & CAM_ATAIO_FPDMA)) {
		ch->numtslots[ccb->ccb_h.target_id]++;
	}
	if ((ccb->ccb_h.func_code == XPT_ATA_IO) &&
	    (ccb->ataio.cmd.flags & (CAM_ATAIO_CONTROL | CAM_ATAIO_NEEDRESULT)))
		ch->aslots |= (1 << slot->slot);
	slot->dma.nsegs = 0;
	/* If request moves data, setup and load SG list */
	if ((ccb->ccb_h.flags & CAM_DIR_MASK) != CAM_DIR_NONE) {
		slot->state = SIIS_SLOT_LOADING;
		bus_dmamap_load_ccb(ch->dma.data_tag, slot->dma.data_map,
		    ccb, siis_dmasetprd, slot, 0);
	} else
		siis_execute_transaction(slot);
}