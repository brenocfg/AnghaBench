#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ rc_lost; scalar_t__ rc_lost_at_pktepoch; scalar_t__ rc_delivered; scalar_t__ rc_pkt_epoch_del; scalar_t__ rc_pkt_epoch; scalar_t__ rc_pkt_epoch_time; int /*<<< orphan*/  rc_pkt_epoch_rtt; int /*<<< orphan*/  recovery_lr; scalar_t__ rc_pkt_epoch_loss_rate; } ;
struct tcp_bbr {scalar_t__ no_pacing_until; TYPE_2__ r_ctl; scalar_t__ rc_no_pacing; TYPE_1__* rc_tp; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  t_flags; } ;

/* Variables and functions */
 scalar_t__ IN_RECOVERY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bbr_calc_time (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bbr_log_pkt_epoch (struct tcp_bbr*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tcp_bbr_tso_size_check (struct tcp_bbr*,scalar_t__) ; 

__attribute__((used)) static inline void
bbr_set_pktepoch(struct tcp_bbr *bbr, uint32_t cts, int32_t line)
{
	uint64_t calclr;
	uint32_t lost, del;

	if (bbr->r_ctl.rc_lost > bbr->r_ctl.rc_lost_at_pktepoch)
		lost = bbr->r_ctl.rc_lost - bbr->r_ctl.rc_lost_at_pktepoch;
	else
		lost = 0;
	del = bbr->r_ctl.rc_delivered - bbr->r_ctl.rc_pkt_epoch_del;
	if (lost == 0)  {
		calclr = 0;
	} else if (del) {
		calclr = lost;
		calclr *= (uint64_t)1000;
		calclr /= (uint64_t)del;
	} else {
		/* Nothing delivered? 100.0% loss */
		calclr = 1000; 
	}
	bbr->r_ctl.rc_pkt_epoch_loss_rate =  (uint32_t)calclr;
	if (IN_RECOVERY(bbr->rc_tp->t_flags)) 
		bbr->r_ctl.recovery_lr += (uint32_t)calclr;
	bbr->r_ctl.rc_pkt_epoch++;
	if (bbr->rc_no_pacing &&
	    (bbr->r_ctl.rc_pkt_epoch >= bbr->no_pacing_until)) {
		bbr->rc_no_pacing = 0;
		tcp_bbr_tso_size_check(bbr, cts);
	}
	bbr->r_ctl.rc_pkt_epoch_rtt = bbr_calc_time(cts, bbr->r_ctl.rc_pkt_epoch_time);
	bbr->r_ctl.rc_pkt_epoch_time = cts;
	/* What was our loss rate */
	bbr_log_pkt_epoch(bbr, cts, line, lost, del);
	bbr->r_ctl.rc_pkt_epoch_del = bbr->r_ctl.rc_delivered;
	bbr->r_ctl.rc_lost_at_pktepoch = bbr->r_ctl.rc_lost;
}