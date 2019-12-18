#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int flags; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  TYPE_2__* hcb_p ;
typedef  TYPE_3__* ccb_p ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;
struct TYPE_19__ {scalar_t__ dmamapped; int* cdb_buf; scalar_t__ nego_status; int /*<<< orphan*/  host_status; int /*<<< orphan*/  dmamap; union ccb* cam_ccb; scalar_t__ arg; } ;
struct TYPE_18__ {scalar_t__ device_id; int revision_id; int /*<<< orphan*/  data_dmat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int CAM_DIR_MASK ; 
 int /*<<< orphan*/  CAM_REQ_ABORTED ; 
 scalar_t__ CAM_REQ_INPROG ; 
 int /*<<< orphan*/  CAM_REQ_TOO_BIG ; 
 int /*<<< orphan*/  HS_BUSY ; 
 int /*<<< orphan*/  HS_NEGOTIATE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MDELAY (int) ; 
 scalar_t__ PCI_ID_SYM53C896 ; 
 scalar_t__ SYM_DMA_READ ; 
 int /*<<< orphan*/  SYM_LOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  sym_enqueue_cam_ccb (TYPE_3__*) ; 
 int sym_fast_scatter_sg_physical (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sym_free_ccb (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ sym_get_cam_status (union ccb*) ; 
 int /*<<< orphan*/  sym_put_start_queue (TYPE_2__*,TYPE_3__*) ; 
 int sym_scatter_sg_physical (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sym_set_cam_status (union ccb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_setup_data_pointers (TYPE_2__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  sym_xpt_done (TYPE_2__*,union ccb*,TYPE_3__*) ; 

__attribute__((used)) static void
sym_execute_ccb(void *arg, bus_dma_segment_t *psegs, int nsegs, int error)
{
	ccb_p	cp;
	hcb_p	np;
	union	ccb *ccb;

	cp  = (ccb_p) arg;
	ccb = cp->cam_ccb;
	np  = (hcb_p) cp->arg;

	SYM_LOCK_ASSERT(MA_OWNED);

	/*
	 *  Deal with weird races.
	 */
	if (sym_get_cam_status(ccb) != CAM_REQ_INPROG)
		goto out_abort;

	/*
	 *  Deal with weird errors.
	 */
	if (error) {
		cp->dmamapped = 0;
		sym_set_cam_status(cp->cam_ccb, CAM_REQ_ABORTED);
		goto out_abort;
	}

	/*
	 *  Build the data descriptor for the chip.
	 */
	if (nsegs) {
		int retv;
		/* 896 rev 1 requires to be careful about boundaries */
		if (np->device_id == PCI_ID_SYM53C896 && np->revision_id <= 1)
			retv = sym_scatter_sg_physical(np, cp, psegs, nsegs);
		else
			retv = sym_fast_scatter_sg_physical(np,cp, psegs,nsegs);
		if (retv < 0) {
			sym_set_cam_status(cp->cam_ccb, CAM_REQ_TOO_BIG);
			goto out_abort;
		}
	}

	/*
	 *  Synchronize the DMA map only if we have
	 *  actually mapped the data.
	 */
	if (cp->dmamapped) {
		bus_dmamap_sync(np->data_dmat, cp->dmamap,
			(cp->dmamapped == SYM_DMA_READ ?
				BUS_DMASYNC_PREREAD : BUS_DMASYNC_PREWRITE));
	}

	/*
	 *  Set host status to busy state.
	 *  May have been set back to HS_WAIT to avoid a race.
	 */
	cp->host_status	= cp->nego_status ? HS_NEGOTIATE : HS_BUSY;

	/*
	 *  Set data pointers.
	 */
	sym_setup_data_pointers(np, cp,  (ccb->ccb_h.flags & CAM_DIR_MASK));

	/*
	 *  Enqueue this IO in our pending queue.
	 */
	sym_enqueue_cam_ccb(cp);

	/*
	 *  When `#ifed 1', the code below makes the driver
	 *  panic on the first attempt to write to a SCSI device.
	 *  It is the first test we want to do after a driver
	 *  change that does not seem obviously safe. :)
	 */
#if 0
	switch (cp->cdb_buf[0]) {
	case 0x0A: case 0x2A: case 0xAA:
		panic("XXXXXXXXXXXXX WRITE NOT YET ALLOWED XXXXXXXXXXXXXX\n");
		MDELAY(10000);
		break;
	default:
		break;
	}
#endif
	/*
	 *  Activate this job.
	 */
	sym_put_start_queue(np, cp);
	return;
out_abort:
	sym_xpt_done(np, ccb, cp);
	sym_free_ccb(np, cp);
}