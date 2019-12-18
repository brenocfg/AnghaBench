#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_9__ {scalar_t__ timeout; int /*<<< orphan*/ * param; int /*<<< orphan*/  lineno; int /*<<< orphan*/  func; } ;
typedef  TYPE_2__ mbreg_t ;
struct TYPE_8__ {int mbox_sleep_ok; int mbox_sleeping; int mboxcmd_done; } ;
struct TYPE_10__ {TYPE_1__ isp_osinfo; int /*<<< orphan*/  isp_lastmbxcmd; int /*<<< orphan*/  isp_lock; } ;
typedef  TYPE_3__ ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_DELAY (int) ; 
 int /*<<< orphan*/  ISP_LOGWARN ; 
 int /*<<< orphan*/  ISP_RUN_ISR (TYPE_3__*) ; 
 int MBCMD_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  MBOX_TIMEOUT ; 
 int /*<<< orphan*/  PRIBIO ; 
 int SBT_1US ; 
 int /*<<< orphan*/  isp_prt (TYPE_3__*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep_sbt (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
isp_mbox_wait_complete(ispsoftc_t *isp, mbreg_t *mbp)
{
	u_int t, to;

	to = (mbp->timeout == 0) ? MBCMD_DEFAULT_TIMEOUT : mbp->timeout;
	if (isp->isp_osinfo.mbox_sleep_ok) {
		isp->isp_osinfo.mbox_sleep_ok = 0;
		isp->isp_osinfo.mbox_sleeping = 1;
		msleep_sbt(&isp->isp_osinfo.mboxcmd_done, &isp->isp_lock,
		    PRIBIO, "ispmbx_sleep", to * SBT_1US, 0, 0);
		isp->isp_osinfo.mbox_sleep_ok = 1;
		isp->isp_osinfo.mbox_sleeping = 0;
	} else {
		for (t = 0; t < to; t += 100) {
			if (isp->isp_osinfo.mboxcmd_done)
				break;
			ISP_RUN_ISR(isp);
			if (isp->isp_osinfo.mboxcmd_done)
				break;
			ISP_DELAY(100);
		}
	}
	if (isp->isp_osinfo.mboxcmd_done == 0) {
		isp_prt(isp, ISP_LOGWARN, "%s Mailbox Command (0x%x) Timeout (%uus) (%s:%d)",
		    isp->isp_osinfo.mbox_sleep_ok? "Interrupting" : "Polled",
		    isp->isp_lastmbxcmd, to, mbp->func, mbp->lineno);
		mbp->param[0] = MBOX_TIMEOUT;
		isp->isp_osinfo.mboxcmd_done = 1;
	}
}