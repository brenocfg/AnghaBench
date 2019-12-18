#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
struct ccb_hdr {int flags; int /*<<< orphan*/  status; } ;
struct ccb_scsiio {struct ccb_hdr ccb_h; int /*<<< orphan*/  dxfer_len; } ;
typedef  TYPE_1__* hcb_p ;
typedef  TYPE_2__* ccb_p ;
struct TYPE_9__ {int /*<<< orphan*/  host_status; int /*<<< orphan*/  dmamap; int /*<<< orphan*/  dmamapped; TYPE_1__* arg; int /*<<< orphan*/  data_len; } ;
struct TYPE_8__ {int /*<<< orphan*/  sim; int /*<<< orphan*/  data_dmat; } ;

/* Variables and functions */
 int CAM_DIR_IN ; 
 int CAM_DIR_MASK ; 
 int CAM_DIR_NONE ; 
 int /*<<< orphan*/  CAM_RELEASE_SIMQ ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  HS_WAIT ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SYM_DMA_READ ; 
 int /*<<< orphan*/  SYM_DMA_WRITE ; 
 int /*<<< orphan*/  SYM_LOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int bus_dmamap_load_ccb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ccb*,int /*<<< orphan*/  (*) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ),TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_execute_ccb (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sym_setup_data_and_start(hcb_p np, struct ccb_scsiio *csio, ccb_p cp)
{
	struct ccb_hdr *ccb_h;
	int dir, retv;

	SYM_LOCK_ASSERT(MA_OWNED);

	ccb_h = &csio->ccb_h;

	/*
	 *  Now deal with the data.
	 */
	cp->data_len = csio->dxfer_len;
	cp->arg      = np;

	/*
	 *  No direction means no data.
	 */
	dir = (ccb_h->flags & CAM_DIR_MASK);
	if (dir == CAM_DIR_NONE) {
		sym_execute_ccb(cp, NULL, 0, 0);
		return;
	}

	cp->dmamapped = (dir == CAM_DIR_IN) ?  SYM_DMA_READ : SYM_DMA_WRITE;
	retv = bus_dmamap_load_ccb(np->data_dmat, cp->dmamap,
			       (union ccb *)csio, sym_execute_ccb, cp, 0);
	if (retv == EINPROGRESS) {
		cp->host_status	= HS_WAIT;
		xpt_freeze_simq(np->sim, 1);
		csio->ccb_h.status |= CAM_RELEASE_SIMQ;
	}
}