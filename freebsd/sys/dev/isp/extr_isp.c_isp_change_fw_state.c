#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ispsoftc_t ;
struct TYPE_3__ {int isp_fwstate; } ;
typedef  TYPE_1__ fcparam ;

/* Variables and functions */
 TYPE_1__* FCPARAM (int /*<<< orphan*/ *,int) ; 
 int ISP_LOGCONFIG ; 
 int ISP_LOG_SANCFG ; 
 int /*<<< orphan*/  isp_fc_fw_statename (int) ; 
 int /*<<< orphan*/  isp_prt (int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
isp_change_fw_state(ispsoftc_t *isp, int chan, int state)
{
	fcparam *fcp = FCPARAM(isp, chan);

	if (fcp->isp_fwstate == state)
		return;
	isp_prt(isp, ISP_LOGCONFIG|ISP_LOG_SANCFG,
	    "Chan %d Firmware state <%s->%s>", chan,
	    isp_fc_fw_statename(fcp->isp_fwstate), isp_fc_fw_statename(state));
	fcp->isp_fwstate = state;
}