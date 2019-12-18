#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int* param; int ibits; int timeout; int /*<<< orphan*/  logval; } ;
typedef  TYPE_1__ mbreg_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;

/* Variables and functions */
 scalar_t__ ISP_CAP_2KLOGIN (int /*<<< orphan*/ *) ; 
 int ISP_LOG_SANCFG ; 
 int ISP_LOG_WARN1 ; 
 int /*<<< orphan*/  MBLOGNONE ; 
#define  MBOX_ALL_IDS_USED 132 
#define  MBOX_COMMAND_COMPLETE 131 
#define  MBOX_COMMAND_ERROR 130 
 int /*<<< orphan*/  MBOX_FABRIC_LOGIN ; 
#define  MBOX_LOOP_ID_USED 129 
#define  MBOX_PORT_ID_USED 128 
 int /*<<< orphan*/  MBSINIT (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isp_mboxcmd (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  isp_prt (int /*<<< orphan*/ *,int,char*,...) ; 

__attribute__((used)) static int
isp_port_login(ispsoftc_t *isp, uint16_t handle, uint32_t portid)
{
	mbreg_t mbs;

	MBSINIT(&mbs, MBOX_FABRIC_LOGIN, MBLOGNONE, 500000);
	if (ISP_CAP_2KLOGIN(isp)) {
		mbs.param[1] = handle;
		mbs.ibits = (1 << 10);
	} else {
		mbs.param[1] = handle << 8;
	}
	mbs.param[2] = portid >> 16;
	mbs.param[3] = portid;
	mbs.logval = MBLOGNONE;
	mbs.timeout = 500000;
	isp_mboxcmd(isp, &mbs);

	switch (mbs.param[0]) {
	case MBOX_PORT_ID_USED:
		isp_prt(isp, ISP_LOG_SANCFG|ISP_LOG_WARN1, "isp_port_login: portid 0x%06x already logged in as 0x%x", portid, mbs.param[1]);
		return (MBOX_PORT_ID_USED | (mbs.param[1] << 16));

	case MBOX_LOOP_ID_USED:
		isp_prt(isp, ISP_LOG_SANCFG|ISP_LOG_WARN1, "isp_port_login: handle 0x%x in use for port id 0x%02xXXXX", handle, mbs.param[1] & 0xff);
		return (MBOX_LOOP_ID_USED);

	case MBOX_COMMAND_COMPLETE:
		return (0);

	case MBOX_COMMAND_ERROR:
		isp_prt(isp, ISP_LOG_SANCFG|ISP_LOG_WARN1, "isp_port_login: error 0x%x in PLOGI to port 0x%06x", mbs.param[1], portid);
		return (MBOX_COMMAND_ERROR);

	case MBOX_ALL_IDS_USED:
		isp_prt(isp, ISP_LOG_SANCFG|ISP_LOG_WARN1, "isp_port_login: all IDs used for fabric login");
		return (MBOX_ALL_IDS_USED);

	default:
		isp_prt(isp, ISP_LOG_SANCFG, "isp_port_login: error 0x%x on port login of 0x%06x@0x%0x", mbs.param[0], portid, handle);
		return (mbs.param[0]);
	}
}