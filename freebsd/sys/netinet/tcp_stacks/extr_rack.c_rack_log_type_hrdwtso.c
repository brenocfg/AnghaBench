#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flex4; int flex7; int flex8; int /*<<< orphan*/  inflight; void* timeStamp; int /*<<< orphan*/  flex6; int /*<<< orphan*/  flex5; int /*<<< orphan*/  flex3; int /*<<< orphan*/  flex1; } ;
union tcp_log_stackspecific {TYPE_1__ u_bbr; } ;
typedef  void* uint32_t ;
struct timeval {int dummy; } ;
struct tcpcb {scalar_t__ t_logstate; TYPE_4__* t_inpcb; } ;
struct TYPE_6__ {int /*<<< orphan*/  rc_sacked; int /*<<< orphan*/  rc_pace_max_segs; int /*<<< orphan*/  rc_pace_min_segs; } ;
struct tcp_rack {TYPE_2__ r_ctl; int /*<<< orphan*/  rc_tp; } ;
typedef  int /*<<< orphan*/  log ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_8__ {TYPE_3__* inp_socket; } ;
struct TYPE_7__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_HDWR_TLS ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (struct tcpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,struct timeval*) ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  ctf_flight_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union tcp_log_stackspecific*,int /*<<< orphan*/ ,int) ; 
 void* tcp_get_usecs (struct timeval*) ; 

__attribute__((used)) static void
rack_log_type_hrdwtso(struct tcpcb *tp, struct tcp_rack *rack, int len, int mod, int32_t orig_len, int frm)
{
	if (tp->t_logstate != TCP_LOG_STATE_OFF) {
		union tcp_log_stackspecific log;
		struct timeval tv;
		uint32_t cts;

		memset(&log, 0, sizeof(log));
		cts = tcp_get_usecs(&tv);
		log.u_bbr.flex1 = rack->r_ctl.rc_pace_min_segs;
		log.u_bbr.flex3 = rack->r_ctl.rc_pace_max_segs;
		log.u_bbr.flex4 = len;
		log.u_bbr.flex5 = orig_len;
		log.u_bbr.flex6 = rack->r_ctl.rc_sacked;
		log.u_bbr.flex7 = mod;
		log.u_bbr.flex8 = frm;
		log.u_bbr.timeStamp = tcp_get_usecs(&tv);
		log.u_bbr.inflight = ctf_flight_size(rack->rc_tp, rack->r_ctl.rc_sacked);
		TCP_LOG_EVENTP(tp, NULL,
		    &tp->t_inpcb->inp_socket->so_rcv,
		    &tp->t_inpcb->inp_socket->so_snd,
		    TCP_HDWR_TLS, 0,
		    0, &log, false, &tv);
	}
}