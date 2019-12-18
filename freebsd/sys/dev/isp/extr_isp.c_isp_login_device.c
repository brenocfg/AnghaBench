#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;
struct TYPE_5__ {scalar_t__ portid; int handle; } ;
typedef  TYPE_1__ isp_pdb_t ;
struct TYPE_6__ {scalar_t__ isp_loopstate; } ;

/* Variables and functions */
 TYPE_4__* FCPARAM (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ISP_CAP_2KLOGIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_LOGERR ; 
 int /*<<< orphan*/  ISP_LOGWARN ; 
 scalar_t__ LOOP_SCANNING_FABRIC ; 
 int MBOX_LOOP_ID_USED ; 
 int MBOX_PORT_ID_USED ; 
 int NPH_MAX ; 
 int NPH_MAX_2K ; 
 int PLOGX_FLG_CMD_LOGO ; 
 int PLOGX_FLG_CMD_PLOGI ; 
 int PLOGX_FLG_FREE_NPHDL ; 
 int PLOGX_FLG_IMPLICIT ; 
 int isp_getpdb (int /*<<< orphan*/ *,int,int,TYPE_1__*) ; 
 int isp_next_handle (int /*<<< orphan*/ *,int*) ; 
 int isp_plogx (int /*<<< orphan*/ *,int,int,scalar_t__,int) ; 
 int /*<<< orphan*/  isp_prt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int
isp_login_device(ispsoftc_t *isp, int chan, uint32_t portid, isp_pdb_t *p, uint16_t *ohp)
{
	int lim, i, r;
	uint16_t handle;

	if (ISP_CAP_2KLOGIN(isp)) {
		lim = NPH_MAX_2K;
	} else {
		lim = NPH_MAX;
	}

	handle = isp_next_handle(isp, ohp);
	for (i = 0; i < lim; i++) {
		if (FCPARAM(isp, chan)->isp_loopstate != LOOP_SCANNING_FABRIC)
			return (-1);

		/* Check if this handle is free. */
		r = isp_getpdb(isp, chan, handle, p);
		if (r == 0) {
			if (p->portid != portid) {
				/* This handle is busy, try next one. */
				handle = isp_next_handle(isp, ohp);
				continue;
			}
			break;
		}
		if (FCPARAM(isp, chan)->isp_loopstate != LOOP_SCANNING_FABRIC)
			return (-1);

		/*
		 * Now try and log into the device
		 */
		r = isp_plogx(isp, chan, handle, portid, PLOGX_FLG_CMD_PLOGI);
		if (r == 0) {
			break;
		} else if ((r & 0xffff) == MBOX_PORT_ID_USED) {
			/*
			 * If we get here, then the firmwware still thinks we're logged into this device, but with a different
			 * handle. We need to break that association. We used to try and just substitute the handle, but then
			 * failed to get any data via isp_getpdb (below).
			 */
			if (isp_plogx(isp, chan, r >> 16, portid, PLOGX_FLG_CMD_LOGO | PLOGX_FLG_IMPLICIT | PLOGX_FLG_FREE_NPHDL)) {
				isp_prt(isp, ISP_LOGERR, "baw... logout of %x failed", r >> 16);
			}
			if (FCPARAM(isp, chan)->isp_loopstate != LOOP_SCANNING_FABRIC)
				return (-1);
			r = isp_plogx(isp, chan, handle, portid, PLOGX_FLG_CMD_PLOGI);
			if (r != 0)
				i = lim;
			break;
		} else if ((r & 0xffff) == MBOX_LOOP_ID_USED) {
			/* Try the next handle. */
			handle = isp_next_handle(isp, ohp);
		} else {
			/* Give up. */
			i = lim;
			break;
		}
	}

	if (i == lim) {
		isp_prt(isp, ISP_LOGWARN, "Chan %d PLOGI 0x%06x failed", chan, portid);
		return (-1);
	}

	/*
	 * If we successfully logged into it, get the PDB for it
	 * so we can crosscheck that it is still what we think it
	 * is and that we also have the role it plays
	 */
	r = isp_getpdb(isp, chan, handle, p);
	if (r != 0) {
		isp_prt(isp, ISP_LOGERR, "Chan %d new device 0x%06x@0x%x disappeared", chan, portid, handle);
		return (-1);
	}

	if (p->handle != handle || p->portid != portid) {
		isp_prt(isp, ISP_LOGERR, "Chan %d new device 0x%06x@0x%x changed (0x%06x@0x%0x)",
		    chan, portid, handle, p->portid, p->handle);
		return (-1);
	}
	return (0);
}