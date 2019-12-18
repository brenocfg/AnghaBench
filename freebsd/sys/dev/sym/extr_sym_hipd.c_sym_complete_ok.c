#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
typedef  TYPE_4__* tcb_p ;
struct ccb_scsiio {int /*<<< orphan*/  scsi_status; scalar_t__ resid; } ;
typedef  int /*<<< orphan*/  lcb_p ;
typedef  TYPE_5__* hcb_p ;
typedef  TYPE_6__* ccb_p ;
struct TYPE_17__ {scalar_t__ lastp; scalar_t__ goalp; } ;
struct TYPE_18__ {TYPE_2__ head; } ;
struct TYPE_21__ {scalar_t__ host_status; size_t target; scalar_t__ dmamapped; int /*<<< orphan*/  ssss_status; int /*<<< orphan*/  dmamap; TYPE_3__ phys; int /*<<< orphan*/  lun; TYPE_1__* cam_ccb; } ;
struct TYPE_20__ {int /*<<< orphan*/  data_dmat; TYPE_4__* target; } ;
struct TYPE_19__ {int /*<<< orphan*/  lun_map; } ;
struct TYPE_16__ {struct ccb_scsiio csio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 scalar_t__ HS_COMPLETE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SYM_CONF_RESIDUAL_SUPPORT ; 
 scalar_t__ SYM_DMA_READ ; 
 int /*<<< orphan*/  SYM_LOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sym_compute_residual (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  sym_free_ccb (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  sym_lp (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_set_cam_status (union ccb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_xpt_done (TYPE_5__*,union ccb*,TYPE_6__*) ; 

__attribute__((used)) static void sym_complete_ok (hcb_p np, ccb_p cp)
{
	struct ccb_scsiio *csio;
	tcb_p tp;
	lcb_p lp;

	SYM_LOCK_ASSERT(MA_OWNED);

	/*
	 *  Paranoid check. :)
	 */
	if (!cp || !cp->cam_ccb)
		return;
	assert (cp->host_status == HS_COMPLETE);

	/*
	 *  Get command, target and lun pointers.
	 */
	csio = &cp->cam_ccb->csio;
	tp = &np->target[cp->target];
	lp = sym_lp(tp, cp->lun);

	/*
	 *  Assume device discovered on first success.
	 */
	if (!lp)
		sym_set_bit(tp->lun_map, cp->lun);

	/*
	 *  If all data have been transferred, given than no
	 *  extended error did occur, there is no residual.
	 */
	csio->resid = 0;
	if (cp->phys.head.lastp != cp->phys.head.goalp)
		csio->resid = sym_compute_residual(np, cp);

	/*
	 *  Wrong transfer residuals may be worse than just always
	 *  returning zero. User can disable this feature from
	 *  sym_conf.h. Residual support is enabled by default.
	 */
	if (!SYM_CONF_RESIDUAL_SUPPORT)
		csio->resid  = 0;

	/*
	 *  Synchronize DMA map if needed.
	 */
	if (cp->dmamapped) {
		bus_dmamap_sync(np->data_dmat, cp->dmamap,
			(cp->dmamapped == SYM_DMA_READ ?
				BUS_DMASYNC_POSTREAD : BUS_DMASYNC_POSTWRITE));
	}
	/*
	 *  Set status and complete the command.
	 */
	csio->scsi_status = cp->ssss_status;
	sym_set_cam_status((union ccb *) csio, CAM_REQ_CMP);
	sym_xpt_done(np, (union ccb *) csio, cp);
	sym_free_ccb(np, cp);
}