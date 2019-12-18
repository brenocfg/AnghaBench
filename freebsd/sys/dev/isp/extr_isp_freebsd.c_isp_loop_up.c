#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct isp_fc {int loop_seen_once; scalar_t__ loop_down_time; } ;
typedef  int /*<<< orphan*/  ispsoftc_t ;

/* Variables and functions */
 struct isp_fc* ISP_FC_PC (int /*<<< orphan*/ *,int) ; 
 int ISP_LOGDEBUG0 ; 
 int ISP_LOG_SANCFG ; 
 int /*<<< orphan*/  isp_prt (int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  isp_unfreeze_loopdown (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
isp_loop_up(ispsoftc_t *isp, int chan)
{
	struct isp_fc *fc = ISP_FC_PC(isp, chan);

	isp_prt(isp, ISP_LOG_SANCFG|ISP_LOGDEBUG0, "Chan %d Loop is up", chan);
	fc->loop_seen_once = 1;
	fc->loop_down_time = 0;
	isp_unfreeze_loopdown(isp, chan);
}