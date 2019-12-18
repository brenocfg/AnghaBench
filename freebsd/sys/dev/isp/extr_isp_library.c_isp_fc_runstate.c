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
struct TYPE_3__ {scalar_t__ role; int isp_loopstate; } ;
typedef  TYPE_1__ fcparam ;

/* Variables and functions */
 TYPE_1__* FCPARAM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ISPCTL_FCLINK_TEST ; 
 int /*<<< orphan*/  ISPCTL_PDB_SYNC ; 
 int /*<<< orphan*/  ISPCTL_SCAN_FABRIC ; 
 int /*<<< orphan*/  ISPCTL_SCAN_LOOP ; 
 scalar_t__ ISP_ROLE_NONE ; 
 int isp_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,...) ; 

int
isp_fc_runstate(ispsoftc_t *isp, int chan, int tval)
{
	fcparam *fcp = FCPARAM(isp, chan);
	int res;

again:
	if (fcp->role == ISP_ROLE_NONE)
		return (-1);
	res = isp_control(isp, ISPCTL_FCLINK_TEST, chan, tval);
	if (res > 0)
		goto again;
	if (res < 0)
		return (fcp->isp_loopstate);
	res = isp_control(isp, ISPCTL_SCAN_LOOP, chan);
	if (res > 0)
		goto again;
	if (res < 0)
		return (fcp->isp_loopstate);
	res = isp_control(isp, ISPCTL_SCAN_FABRIC, chan);
	if (res > 0)
		goto again;
	if (res < 0)
		return (fcp->isp_loopstate);
	res = isp_control(isp, ISPCTL_PDB_SYNC, chan);
	if (res > 0)
		goto again;
	return (fcp->isp_loopstate);
}