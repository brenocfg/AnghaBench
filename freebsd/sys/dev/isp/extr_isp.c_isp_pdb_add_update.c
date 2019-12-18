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
typedef  void* uint64_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;
struct TYPE_8__ {scalar_t__ portid; scalar_t__ handle; scalar_t__ prli_word3; int prli_word0; int /*<<< orphan*/  portname; int /*<<< orphan*/  nodename; } ;
typedef  TYPE_1__ isp_pdb_t ;
struct TYPE_9__ {scalar_t__ portid; scalar_t__ handle; scalar_t__ state; scalar_t__ prli_word3; int prli_word0; scalar_t__ new_portid; int new_prli_word0; scalar_t__ new_prli_word3; void* node_wwn; void* port_wwn; scalar_t__ probational; } ;
typedef  TYPE_2__ fcportdb_t ;

/* Variables and functions */
 scalar_t__ FC_PORTDB_STATE_CHANGED ; 
 scalar_t__ FC_PORTDB_STATE_NEW ; 
 scalar_t__ FC_PORTDB_STATE_VALID ; 
 int /*<<< orphan*/  FC_PORTDB_TGT (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  ISP_LOGERR ; 
 int /*<<< orphan*/  ISP_LOG_SANCFG ; 
 int /*<<< orphan*/  ISP_MEMZERO (TYPE_2__*,int) ; 
 int /*<<< orphan*/  MAKE_WWN_FROM_NODE_NAME (void*,int /*<<< orphan*/ ) ; 
 int PRLI_WD0_EST_IMAGE_PAIR ; 
 int /*<<< orphan*/  isp_dump_portdb (int /*<<< orphan*/ *,int) ; 
 scalar_t__ isp_find_pdb_by_wwpn (int /*<<< orphan*/ *,int,void*,TYPE_2__**) ; 
 int /*<<< orphan*/  isp_find_pdb_empty (int /*<<< orphan*/ *,int,TYPE_2__**) ; 
 int /*<<< orphan*/  isp_prt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static void
isp_pdb_add_update(ispsoftc_t *isp, int chan, isp_pdb_t *pdb)
{
	fcportdb_t *lp;
	uint64_t wwnn, wwpn;

	MAKE_WWN_FROM_NODE_NAME(wwnn, pdb->nodename);
	MAKE_WWN_FROM_NODE_NAME(wwpn, pdb->portname);

	/* Search port database for the same WWPN. */
	if (isp_find_pdb_by_wwpn(isp, chan, wwpn, &lp)) {
		if (!lp->probational) {
			isp_prt(isp, ISP_LOGERR,
			    "Chan %d Port 0x%06x@0x%04x [%d] is not probational (0x%x)",
			    chan, lp->portid, lp->handle,
			    FC_PORTDB_TGT(isp, chan, lp), lp->state);
			isp_dump_portdb(isp, chan);
			return;
		}
		lp->probational = 0;
		lp->node_wwn = wwnn;

		/* Old device, nothing new. */
		if (lp->portid == pdb->portid &&
		    lp->handle == pdb->handle &&
		    lp->prli_word3 == pdb->prli_word3 &&
		    ((pdb->prli_word0 & PRLI_WD0_EST_IMAGE_PAIR) ==
		     (lp->prli_word0 & PRLI_WD0_EST_IMAGE_PAIR))) {
			if (lp->state != FC_PORTDB_STATE_NEW)
				lp->state = FC_PORTDB_STATE_VALID;
			isp_prt(isp, ISP_LOG_SANCFG,
			    "Chan %d Port 0x%06x@0x%04x is valid",
			    chan, pdb->portid, pdb->handle);
			return;
		}

		/* Something has changed. */
		lp->state = FC_PORTDB_STATE_CHANGED;
		lp->handle = pdb->handle;
		lp->new_portid = pdb->portid;
		lp->new_prli_word0 = pdb->prli_word0;
		lp->new_prli_word3 = pdb->prli_word3;
		isp_prt(isp, ISP_LOG_SANCFG,
		    "Chan %d Port 0x%06x@0x%04x is changed",
		    chan, pdb->portid, pdb->handle);
		return;
	}

	/* It seems like a new port. Find an empty slot for it. */
	if (!isp_find_pdb_empty(isp, chan, &lp)) {
		isp_prt(isp, ISP_LOGERR, "Chan %d out of portdb entries", chan);
		return;
	}

	ISP_MEMZERO(lp, sizeof (fcportdb_t));
	lp->probational = 0;
	lp->state = FC_PORTDB_STATE_NEW;
	lp->portid = lp->new_portid = pdb->portid;
	lp->prli_word0 = lp->new_prli_word0 = pdb->prli_word0;
	lp->prli_word3 = lp->new_prli_word3 = pdb->prli_word3;
	lp->handle = pdb->handle;
	lp->port_wwn = wwpn;
	lp->node_wwn = wwnn;
	isp_prt(isp, ISP_LOG_SANCFG, "Chan %d Port 0x%06x@0x%04x is new",
	    chan, pdb->portid, pdb->handle);
}