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
struct isp_fc {scalar_t__ loop_down_time; } ;
typedef  int /*<<< orphan*/  ispsoftc_t ;
struct TYPE_3__ {int role; } ;
typedef  TYPE_1__ fcparam ;

/* Variables and functions */
 TYPE_1__* FCPARAM (int /*<<< orphan*/ *,int) ; 
 struct isp_fc* ISP_FC_PC (int /*<<< orphan*/ *,int) ; 
 int ISP_LOGDEBUG0 ; 
 int ISP_LOG_SANCFG ; 
 int ISP_ROLE_INITIATOR ; 
 int /*<<< orphan*/  isp_freeze_loopdown (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  isp_prt (int /*<<< orphan*/ *,int,char*,int) ; 
 scalar_t__ time_uptime ; 
 int /*<<< orphan*/  wakeup (struct isp_fc*) ; 

__attribute__((used)) static void
isp_loop_changed(ispsoftc_t *isp, int chan)
{
	fcparam *fcp = FCPARAM(isp, chan);
	struct isp_fc *fc = ISP_FC_PC(isp, chan);

	if (fc->loop_down_time)
		return;
	isp_prt(isp, ISP_LOG_SANCFG|ISP_LOGDEBUG0, "Chan %d Loop changed", chan);
	if (fcp->role & ISP_ROLE_INITIATOR)
		isp_freeze_loopdown(isp, chan);
	fc->loop_down_time = time_uptime;
	wakeup(fc);
}