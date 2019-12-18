#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  inflight; int /*<<< orphan*/  timeStamp; int /*<<< orphan*/  pkts_out; int /*<<< orphan*/  flex8; int /*<<< orphan*/  rttProp; int /*<<< orphan*/  flex6; int /*<<< orphan*/  flex5; int /*<<< orphan*/  flex4; void* flex3; void* flex2; int /*<<< orphan*/  flex1; int /*<<< orphan*/  ininput; int /*<<< orphan*/  inhpts; } ;
union tcp_log_stackspecific {TYPE_5__ u_bbr; } ;
typedef  void* uint32_t ;
struct timeval {int dummy; } ;
struct tcpcb {scalar_t__ t_logstate; } ;
struct TYPE_6__ {int /*<<< orphan*/  rs_rtt_tot; int /*<<< orphan*/  rs_rtt_cnt; int /*<<< orphan*/  rs_rtt_highest; int /*<<< orphan*/  rs_rtt_lowest; } ;
struct TYPE_7__ {int /*<<< orphan*/  rc_sacked; int /*<<< orphan*/  rc_prr_sndcnt; int /*<<< orphan*/  rc_rate_sample_method; TYPE_1__ rack_rs; } ;
struct tcp_rack {TYPE_4__* rc_inp; TYPE_2__ r_ctl; int /*<<< orphan*/  rc_tp; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_9__ {TYPE_3__* inp_socket; int /*<<< orphan*/  inp_in_input; int /*<<< orphan*/  inp_in_hpts; } ;
struct TYPE_8__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_LOG_BBRRTT ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (struct tcpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,struct timeval*) ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  ctf_flight_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_get_usecs (struct timeval*) ; 

__attribute__((used)) static void
rack_log_rtt_upd(struct tcpcb *tp, struct tcp_rack *rack, int32_t t,
    uint32_t o_srtt, uint32_t o_var)
{
	if (tp->t_logstate != TCP_LOG_STATE_OFF) {
		union tcp_log_stackspecific log;
		struct timeval tv;

		memset(&log.u_bbr, 0, sizeof(log.u_bbr));
		log.u_bbr.inhpts = rack->rc_inp->inp_in_hpts;
		log.u_bbr.ininput = rack->rc_inp->inp_in_input;
		log.u_bbr.flex1 = t;
		log.u_bbr.flex2 = o_srtt;
		log.u_bbr.flex3 = o_var;
		log.u_bbr.flex4 = rack->r_ctl.rack_rs.rs_rtt_lowest;
		log.u_bbr.flex5 = rack->r_ctl.rack_rs.rs_rtt_highest;		
		log.u_bbr.flex6 = rack->r_ctl.rack_rs.rs_rtt_cnt;
		log.u_bbr.rttProp = rack->r_ctl.rack_rs.rs_rtt_tot;
		log.u_bbr.flex8 = rack->r_ctl.rc_rate_sample_method;
		log.u_bbr.pkts_out = rack->r_ctl.rc_prr_sndcnt;
		log.u_bbr.timeStamp = tcp_get_usecs(&tv);
		log.u_bbr.inflight = ctf_flight_size(rack->rc_tp, rack->r_ctl.rc_sacked);
		TCP_LOG_EVENTP(tp, NULL,
		    &rack->rc_inp->inp_socket->so_rcv,
		    &rack->rc_inp->inp_socket->so_snd,
		    BBR_LOG_BBRRTT, 0,
		    0, &log, false, &tv);
	}
}