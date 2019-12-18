#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_9__ {int* param; } ;
typedef  TYPE_1__ mbreg_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;
struct TYPE_10__ {scalar_t__ portid; } ;
typedef  TYPE_2__ isp_pdb_t ;
struct TYPE_11__ {scalar_t__ isp_loopstate; scalar_t__ isp_fwstate; int isp_topo; int isp_portid; int isp_loopid; int isp_fabric_params; scalar_t__ role; int isp_gbspeed; scalar_t__ isp_wwnn; scalar_t__ isp_wwpn; int /*<<< orphan*/  isp_sns_hdl; } ;
typedef  TYPE_3__ fcparam ;
typedef  int /*<<< orphan*/  NANOTIME_T ;

/* Variables and functions */
 TYPE_3__* FCPARAM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FL_ID ; 
 scalar_t__ FW_READY ; 
 int /*<<< orphan*/  GET_NANOTIME (int /*<<< orphan*/ *) ; 
 scalar_t__ ISP_FW_NEWER_THAN (int /*<<< orphan*/ *,int,int,int) ; 
 int ISP_LOGCONFIG ; 
 int ISP_LOGWARN ; 
 int ISP_LOG_SANCFG ; 
 scalar_t__ ISP_ROLE_TARGET ; 
 int /*<<< orphan*/  ISP_SLEEP (int /*<<< orphan*/ *,int) ; 
 scalar_t__ IS_2100 (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_23XX (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_24XX (int /*<<< orphan*/ *) ; 
 scalar_t__ LOOP_HAVE_ADDR ; 
 scalar_t__ LOOP_HAVE_LINK ; 
 scalar_t__ LOOP_LTEST_DONE ; 
 scalar_t__ LOOP_TESTING_LINK ; 
 int MBGSD_10GB ; 
 int MBGSD_16GB ; 
 int MBGSD_1GB ; 
 int MBGSD_2GB ; 
 int MBGSD_32GB ; 
 int MBGSD_4GB ; 
 int MBGSD_8GB ; 
 int MBGSD_GET_RATE ; 
 int /*<<< orphan*/  MBLOGALL ; 
 int MBOX_COMMAND_COMPLETE ; 
 int /*<<< orphan*/  MBOX_GET_LOOP_ID ; 
 int /*<<< orphan*/  MBOX_GET_SET_DATA_RATE ; 
 int /*<<< orphan*/  MBSINIT (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int NANOTIME_SUB (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NPH_FL_ID ; 
 int /*<<< orphan*/  NPH_SNS_ID ; 
 int /*<<< orphan*/  SNS_ID ; 
 int TOPO_FL_PORT ; 
 int TOPO_F_PORT ; 
 int /*<<< orphan*/  TOPO_IS_FABRIC (int) ; 
 int TOPO_NL_PORT ; 
 int TOPO_PTP_STUB ; 
 scalar_t__* alpa_map ; 
 int /*<<< orphan*/  isp_change_fw_state (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_fc_fw_statename (scalar_t__) ; 
 int /*<<< orphan*/  isp_fc_toponame (TYPE_3__*) ; 
 int /*<<< orphan*/  isp_fw_state (int /*<<< orphan*/ *,int) ; 
 int isp_getpdb (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  isp_mboxcmd (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  isp_prt (int /*<<< orphan*/ *,int,char*,int,...) ; 
 int isp_register_fc4_features_24xx (int /*<<< orphan*/ *,int) ; 
 int isp_register_fc4_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  isp_register_node_name_24xx (int /*<<< orphan*/ *,int) ; 
 int isp_register_port_name_24xx (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  isp_send_change_request (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
isp_fclink_test(ispsoftc_t *isp, int chan, int usdelay)
{
	mbreg_t mbs;
	int i, r;
	uint16_t nphdl;
	fcparam *fcp;
	isp_pdb_t pdb;
	NANOTIME_T hra, hrb;

	fcp = FCPARAM(isp, chan);

	if (fcp->isp_loopstate < LOOP_HAVE_LINK)
		return (-1);
	if (fcp->isp_loopstate >= LOOP_LTEST_DONE)
		return (0);

	isp_prt(isp, ISP_LOG_SANCFG, "Chan %d FC link test", chan);

	/*
	 * Wait up to N microseconds for F/W to go to a ready state.
	 */
	GET_NANOTIME(&hra);
	while (1) {
		isp_change_fw_state(isp, chan, isp_fw_state(isp, chan));
		if (fcp->isp_fwstate == FW_READY) {
			break;
		}
		if (fcp->isp_loopstate < LOOP_HAVE_LINK)
			goto abort;
		GET_NANOTIME(&hrb);
		if ((NANOTIME_SUB(&hrb, &hra) / 1000 + 1000 >= usdelay))
			break;
		ISP_SLEEP(isp, 1000);
	}
	if (fcp->isp_fwstate != FW_READY) {
		isp_prt(isp, ISP_LOG_SANCFG,
		    "Chan %d Firmware is not ready (%s)",
		    chan, isp_fc_fw_statename(fcp->isp_fwstate));
		return (-1);
	}

	/*
	 * Get our Loop ID and Port ID.
	 */
	MBSINIT(&mbs, MBOX_GET_LOOP_ID, MBLOGALL, 0);
	mbs.param[9] = chan;
	isp_mboxcmd(isp, &mbs);
	if (mbs.param[0] != MBOX_COMMAND_COMPLETE) {
		return (-1);
	}

	if (IS_2100(isp)) {
		/*
		 * Don't bother with fabric if we are using really old
		 * 2100 firmware. It's just not worth it.
		 */
		if (ISP_FW_NEWER_THAN(isp, 1, 15, 37))
			fcp->isp_topo = TOPO_FL_PORT;
		else
			fcp->isp_topo = TOPO_NL_PORT;
	} else {
		int topo = (int) mbs.param[6];
		if (topo < TOPO_NL_PORT || topo > TOPO_PTP_STUB) {
			topo = TOPO_PTP_STUB;
		}
		fcp->isp_topo = topo;
	}
	fcp->isp_portid = mbs.param[2] | (mbs.param[3] << 16);

	if (!TOPO_IS_FABRIC(fcp->isp_topo)) {
		fcp->isp_loopid = mbs.param[1] & 0xff;
	} else if (fcp->isp_topo != TOPO_F_PORT) {
		uint8_t alpa = fcp->isp_portid;

		for (i = 0; alpa_map[i]; i++) {
			if (alpa_map[i] == alpa)
				break;
		}
		if (alpa_map[i])
			fcp->isp_loopid = i;
	}

#if 0
	fcp->isp_loopstate = LOOP_HAVE_ADDR;
#endif
	fcp->isp_loopstate = LOOP_TESTING_LINK;

	if (fcp->isp_topo == TOPO_F_PORT || fcp->isp_topo == TOPO_FL_PORT) {
		nphdl = IS_24XX(isp) ? NPH_FL_ID : FL_ID;
		r = isp_getpdb(isp, chan, nphdl, &pdb);
		if (r != 0 || pdb.portid == 0) {
			if (IS_2100(isp)) {
				fcp->isp_topo = TOPO_NL_PORT;
			} else {
				isp_prt(isp, ISP_LOGWARN,
				    "fabric topology, but cannot get info about fabric controller (0x%x)", r);
				fcp->isp_topo = TOPO_PTP_STUB;
			}
			goto not_on_fabric;
		}

		if (IS_24XX(isp)) {
			fcp->isp_fabric_params = mbs.param[7];
			fcp->isp_sns_hdl = NPH_SNS_ID;
			r = isp_register_fc4_type(isp, chan);
			if (fcp->isp_loopstate < LOOP_TESTING_LINK)
				goto abort;
			if (r != 0)
				goto not_on_fabric;
			r = isp_register_fc4_features_24xx(isp, chan);
			if (fcp->isp_loopstate < LOOP_TESTING_LINK)
				goto abort;
			if (r != 0)
				goto not_on_fabric;
			r = isp_register_port_name_24xx(isp, chan);
			if (fcp->isp_loopstate < LOOP_TESTING_LINK)
				goto abort;
			if (r != 0)
				goto not_on_fabric;
			isp_register_node_name_24xx(isp, chan);
			if (fcp->isp_loopstate < LOOP_TESTING_LINK)
				goto abort;
		} else {
			fcp->isp_sns_hdl = SNS_ID;
			r = isp_register_fc4_type(isp, chan);
			if (r != 0)
				goto not_on_fabric;
			if (fcp->role == ISP_ROLE_TARGET)
				isp_send_change_request(isp, chan);
		}
	}

not_on_fabric:
	/* Get link speed. */
	fcp->isp_gbspeed = 1;
	if (IS_23XX(isp) || IS_24XX(isp)) {
		MBSINIT(&mbs, MBOX_GET_SET_DATA_RATE, MBLOGALL, 3000000);
		mbs.param[1] = MBGSD_GET_RATE;
		/* mbs.param[2] undefined if we're just getting rate */
		isp_mboxcmd(isp, &mbs);
		if (mbs.param[0] == MBOX_COMMAND_COMPLETE) {
			if (mbs.param[1] == MBGSD_10GB)
				fcp->isp_gbspeed = 10;
			else if (mbs.param[1] == MBGSD_32GB)
				fcp->isp_gbspeed = 32;
			else if (mbs.param[1] == MBGSD_16GB)
				fcp->isp_gbspeed = 16;
			else if (mbs.param[1] == MBGSD_8GB)
				fcp->isp_gbspeed = 8;
			else if (mbs.param[1] == MBGSD_4GB)
				fcp->isp_gbspeed = 4;
			else if (mbs.param[1] == MBGSD_2GB)
				fcp->isp_gbspeed = 2;
			else if (mbs.param[1] == MBGSD_1GB)
				fcp->isp_gbspeed = 1;
		}
	}

	if (fcp->isp_loopstate < LOOP_TESTING_LINK) {
abort:
		isp_prt(isp, ISP_LOG_SANCFG,
		    "Chan %d FC link test aborted", chan);
		return (1);
	}
	fcp->isp_loopstate = LOOP_LTEST_DONE;
	isp_prt(isp, ISP_LOG_SANCFG|ISP_LOGCONFIG,
	    "Chan %d WWPN %016jx WWNN %016jx",
	    chan, (uintmax_t)fcp->isp_wwpn, (uintmax_t)fcp->isp_wwnn);
	isp_prt(isp, ISP_LOG_SANCFG|ISP_LOGCONFIG,
	    "Chan %d %dGb %s PortID 0x%06x LoopID 0x%02x",
	    chan, fcp->isp_gbspeed, isp_fc_toponame(fcp), fcp->isp_portid,
	    fcp->isp_loopid);
	isp_prt(isp, ISP_LOG_SANCFG, "Chan %d FC link test done", chan);
	return (0);
}