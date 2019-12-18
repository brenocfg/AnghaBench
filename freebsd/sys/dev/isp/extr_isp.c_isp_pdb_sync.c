#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;
struct TYPE_5__ {int state; int portid; int new_portid; int /*<<< orphan*/  new_prli_word3; int /*<<< orphan*/  prli_word3; int /*<<< orphan*/  new_prli_word0; int /*<<< orphan*/  prli_word0; int /*<<< orphan*/  handle; scalar_t__ probational; } ;
typedef  TYPE_1__ fcportdb_t ;
struct TYPE_6__ {scalar_t__ isp_loopstate; TYPE_1__* portdb; } ;
typedef  TYPE_2__ fcparam ;

/* Variables and functions */
 TYPE_2__* FCPARAM (int /*<<< orphan*/ *,int) ; 
#define  FC_PORTDB_STATE_CHANGED 132 
#define  FC_PORTDB_STATE_DEAD 131 
#define  FC_PORTDB_STATE_NEW 130 
 int FC_PORTDB_STATE_NIL ; 
#define  FC_PORTDB_STATE_VALID 129 
#define  FC_PORTDB_STATE_ZOMBIE 128 
 int /*<<< orphan*/  ISPASYNC_DEV_ARRIVED ; 
 int /*<<< orphan*/  ISPASYNC_DEV_CHANGED ; 
 int /*<<< orphan*/  ISPASYNC_DEV_GONE ; 
 int /*<<< orphan*/  ISPASYNC_DEV_STAYED ; 
 int /*<<< orphan*/  ISP_LOGWARN ; 
 int /*<<< orphan*/  ISP_LOG_SANCFG ; 
 scalar_t__ LOOP_FSCAN_DONE ; 
 scalar_t__ LOOP_READY ; 
 scalar_t__ LOOP_SYNCING_PDB ; 
 size_t MAX_FC_TARG ; 
 int PLOGX_FLG_CMD_LOGO ; 
 int PLOGX_FLG_FREE_NPHDL ; 
 int PLOGX_FLG_IMPLICIT ; 
 int /*<<< orphan*/  isp_async (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  isp_dump_portdb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  isp_plogx (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  isp_prt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int
isp_pdb_sync(ispsoftc_t *isp, int chan)
{
	fcparam *fcp = FCPARAM(isp, chan);
	fcportdb_t *lp;
	uint16_t dbidx;

	if (fcp->isp_loopstate < LOOP_FSCAN_DONE)
		return (-1);
	if (fcp->isp_loopstate >= LOOP_READY)
		return (0);

	isp_prt(isp, ISP_LOG_SANCFG, "Chan %d FC PDB sync", chan);

	fcp->isp_loopstate = LOOP_SYNCING_PDB;

	for (dbidx = 0; dbidx < MAX_FC_TARG; dbidx++) {
		lp = &fcp->portdb[dbidx];

		if (lp->state == FC_PORTDB_STATE_NIL)
			continue;
		if (lp->probational && lp->state != FC_PORTDB_STATE_ZOMBIE)
			lp->state = FC_PORTDB_STATE_DEAD;
		switch (lp->state) {
		case FC_PORTDB_STATE_DEAD:
			lp->state = FC_PORTDB_STATE_NIL;
			isp_async(isp, ISPASYNC_DEV_GONE, chan, lp);
			if ((lp->portid & 0xffff00) != 0) {
				(void) isp_plogx(isp, chan, lp->handle,
				    lp->portid,
				    PLOGX_FLG_CMD_LOGO |
				    PLOGX_FLG_IMPLICIT |
				    PLOGX_FLG_FREE_NPHDL);
			}
			/*
			 * Note that we might come out of this with our state
			 * set to FC_PORTDB_STATE_ZOMBIE.
			 */
			break;
		case FC_PORTDB_STATE_NEW:
			lp->state = FC_PORTDB_STATE_VALID;
			isp_async(isp, ISPASYNC_DEV_ARRIVED, chan, lp);
			break;
		case FC_PORTDB_STATE_CHANGED:
			lp->state = FC_PORTDB_STATE_VALID;
			isp_async(isp, ISPASYNC_DEV_CHANGED, chan, lp);
			lp->portid = lp->new_portid;
			lp->prli_word0 = lp->new_prli_word0;
			lp->prli_word3 = lp->new_prli_word3;
			break;
		case FC_PORTDB_STATE_VALID:
			isp_async(isp, ISPASYNC_DEV_STAYED, chan, lp);
			break;
		case FC_PORTDB_STATE_ZOMBIE:
			break;
		default:
			isp_prt(isp, ISP_LOGWARN,
			    "isp_pdb_sync: state %d for idx %d",
			    lp->state, dbidx);
			isp_dump_portdb(isp, chan);
		}
	}

	if (fcp->isp_loopstate < LOOP_SYNCING_PDB) {
		isp_prt(isp, ISP_LOG_SANCFG,
		    "Chan %d FC PDB sync aborted", chan);
		return (1);
	}

	fcp->isp_loopstate = LOOP_READY;
	isp_prt(isp, ISP_LOG_SANCFG, "Chan %d FC PDB sync done", chan);
	return (0);
}