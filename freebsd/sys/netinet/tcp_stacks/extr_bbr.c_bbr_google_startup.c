#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int rc_bbr_lastbtlbw; scalar_t__ rc_bbr_last_startup_epoch; scalar_t__ rc_pkt_epoch; int /*<<< orphan*/  rc_lost_at_startup; } ;
struct tcp_bbr {TYPE_1__ r_ctl; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ BBR_STARTUP_EPOCHS ; 
 int bbr_get_full_bw (struct tcp_bbr*) ; 
 int /*<<< orphan*/  bbr_log_startup_event (struct tcp_bbr*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ bbr_start_exit ; 

__attribute__((used)) static int32_t 
bbr_google_startup(struct tcp_bbr *bbr, uint32_t cts, int32_t  pkt_epoch)
{
	uint64_t btlbw, gain;
	if (pkt_epoch == 0) {
		/*
		 * Need to be on a pkt-epoch to continue.
		 */
		return (0);
	}
	btlbw = bbr_get_full_bw(bbr);
	gain = ((bbr->r_ctl.rc_bbr_lastbtlbw *
		 (uint64_t)bbr_start_exit) / (uint64_t)100) + bbr->r_ctl.rc_bbr_lastbtlbw;
	if (btlbw >= gain) {
		bbr->r_ctl.rc_bbr_last_startup_epoch = bbr->r_ctl.rc_pkt_epoch;
		bbr_log_startup_event(bbr, cts, bbr->r_ctl.rc_bbr_last_startup_epoch,
				      bbr->r_ctl.rc_lost_at_startup, bbr_start_exit, 3);
		bbr->r_ctl.rc_bbr_lastbtlbw = btlbw;
	}
	if ((bbr->r_ctl.rc_pkt_epoch - bbr->r_ctl.rc_bbr_last_startup_epoch) >= BBR_STARTUP_EPOCHS)
		return (1);
	bbr_log_startup_event(bbr, cts, bbr->r_ctl.rc_bbr_last_startup_epoch,
			      bbr->r_ctl.rc_lost_at_startup, bbr_start_exit, 8);
	return(0);
}