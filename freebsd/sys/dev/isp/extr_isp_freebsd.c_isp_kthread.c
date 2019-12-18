#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct isp_fc {scalar_t__ loop_seen_once; int loop_down_limit; int loop_down_time; int num_threads; TYPE_3__* isp; } ;
struct TYPE_10__ {struct isp_fc* fc; } ;
struct TYPE_11__ {scalar_t__ is_exiting; TYPE_1__ pc; } ;
struct TYPE_12__ {int /*<<< orphan*/  isp_lock; TYPE_2__ isp_osinfo; } ;
typedef  TYPE_3__ ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_LOCK (TYPE_3__*) ; 
 int ISP_LOGDEBUG0 ; 
 int ISP_LOG_SANCFG ; 
 int /*<<< orphan*/  ISP_UNLOCK (TYPE_3__*) ; 
 int LOOP_READY ; 
 int /*<<< orphan*/  PRIBIO ; 
 int hz ; 
 int isp_fc_loop_statename (int) ; 
 int isp_fc_runstate (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  isp_loop_dead (TYPE_3__*,int) ; 
 int /*<<< orphan*/  isp_loop_up (TYPE_3__*,int) ; 
 int /*<<< orphan*/  isp_prt (TYPE_3__*,int,char*,int,...) ; 
 int isp_quickboot_time ; 
 int /*<<< orphan*/  kthread_exit () ; 
 int /*<<< orphan*/  msleep (struct isp_fc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int time_uptime ; 

__attribute__((used)) static void
isp_kthread(void *arg)
{
	struct isp_fc *fc = arg;
	ispsoftc_t *isp = fc->isp;
	int chan = fc - isp->isp_osinfo.pc.fc;
	int slp = 0, d;
	int lb, lim;

	ISP_LOCK(isp);
	while (isp->isp_osinfo.is_exiting == 0) {
		isp_prt(isp, ISP_LOG_SANCFG|ISP_LOGDEBUG0,
		    "Chan %d Checking FC state", chan);
		lb = isp_fc_runstate(isp, chan, 250000);
		isp_prt(isp, ISP_LOG_SANCFG|ISP_LOGDEBUG0,
		    "Chan %d FC got to %s state", chan,
		    isp_fc_loop_statename(lb));

		/*
		 * Our action is different based upon whether we're supporting
		 * Initiator mode or not. If we are, we might freeze the simq
		 * when loop is down and set all sorts of different delays to
		 * check again.
		 *
		 * If not, we simply just wait for loop to come up.
		 */
		if (lb == LOOP_READY || lb < 0) {
			slp = 0;
		} else {
			/*
			 * If we've never seen loop up and we've waited longer
			 * than quickboot time, or we've seen loop up but we've
			 * waited longer than loop_down_limit, give up and go
			 * to sleep until loop comes up.
			 */
			if (fc->loop_seen_once == 0)
				lim = isp_quickboot_time;
			else
				lim = fc->loop_down_limit;
			d = time_uptime - fc->loop_down_time;
			if (d >= lim)
				slp = 0;
			else if (d < 10)
				slp = 1;
			else if (d < 30)
				slp = 5;
			else if (d < 60)
				slp = 10;
			else if (d < 120)
				slp = 20;
			else
				slp = 30;
		}

		if (slp == 0) {
			if (lb == LOOP_READY)
				isp_loop_up(isp, chan);
			else
				isp_loop_dead(isp, chan);
		}

		isp_prt(isp, ISP_LOG_SANCFG|ISP_LOGDEBUG0,
		    "Chan %d sleep for %d seconds", chan, slp);
		msleep(fc, &isp->isp_lock, PRIBIO, "ispf", slp * hz);
	}
	fc->num_threads -= 1;
	ISP_UNLOCK(isp);
	kthread_exit();
}