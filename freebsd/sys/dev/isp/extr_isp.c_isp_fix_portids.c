#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;
struct TYPE_6__ {int handle; int /*<<< orphan*/  portid; int /*<<< orphan*/  portname; } ;
typedef  TYPE_1__ isp_pdb_t ;
struct TYPE_7__ {scalar_t__ state; scalar_t__ port_wwn; int /*<<< orphan*/  new_portid; int /*<<< orphan*/  portid; int /*<<< orphan*/  handle; } ;
typedef  TYPE_2__ fcportdb_t ;
struct TYPE_8__ {scalar_t__ isp_loopstate; TYPE_2__* portdb; } ;
typedef  TYPE_3__ fcparam ;

/* Variables and functions */
 TYPE_3__* FCPARAM (int /*<<< orphan*/ *,int) ; 
 scalar_t__ FC_PORTDB_STATE_NIL ; 
 scalar_t__ FC_PORTDB_STATE_ZOMBIE ; 
 int /*<<< orphan*/  ISP_LOGDEBUG1 ; 
 int /*<<< orphan*/  ISP_LOG_SANCFG ; 
 scalar_t__ LOOP_SCANNING_LOOP ; 
 int /*<<< orphan*/  MAKE_WWN_FROM_NODE_NAME (scalar_t__,int /*<<< orphan*/ ) ; 
 int MAX_FC_TARG ; 
 scalar_t__ VALID_PORT (int /*<<< orphan*/ ) ; 
 int isp_getpdb (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  isp_prt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
isp_fix_portids(ispsoftc_t *isp, int chan)
{
	fcparam *fcp = FCPARAM(isp, chan);
	isp_pdb_t pdb;
	uint64_t wwpn;
	int i, r;

	for (i = 0; i < MAX_FC_TARG; i++) {
		fcportdb_t *lp = &fcp->portdb[i];

		if (lp->state == FC_PORTDB_STATE_NIL ||
		    lp->state == FC_PORTDB_STATE_ZOMBIE)
			continue;
		if (VALID_PORT(lp->portid))
			continue;

		r = isp_getpdb(isp, chan, lp->handle, &pdb);
		if (fcp->isp_loopstate < LOOP_SCANNING_LOOP)
			return;
		if (r != 0) {
			isp_prt(isp, ISP_LOGDEBUG1,
			    "Chan %d FC Scan Loop handle %d returned %x",
			    chan, lp->handle, r);
			continue;
		}

		MAKE_WWN_FROM_NODE_NAME(wwpn, pdb.portname);
		if (lp->port_wwn != wwpn)
			continue;
		lp->portid = lp->new_portid = pdb.portid;
		isp_prt(isp, ISP_LOG_SANCFG,
		    "Chan %d Port 0x%06x@0x%04x is fixed",
		    chan, pdb.portid, pdb.handle);
	}
}