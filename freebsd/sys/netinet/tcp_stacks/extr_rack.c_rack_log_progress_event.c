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
struct TYPE_8__ {int flex1; int flex8; int /*<<< orphan*/  inflight; int /*<<< orphan*/  timeStamp; int /*<<< orphan*/  flex4; int /*<<< orphan*/  flex3; int /*<<< orphan*/  flex2; int /*<<< orphan*/  ininput; int /*<<< orphan*/  inhpts; } ;
union tcp_log_stackspecific {TYPE_4__ u_bbr; } ;
typedef  int /*<<< orphan*/  uint32_t ;
struct timeval {int dummy; } ;
struct tcpcb {scalar_t__ t_logstate; int /*<<< orphan*/  t_acktime; int /*<<< orphan*/  t_maxunacktime; } ;
struct TYPE_5__ {int /*<<< orphan*/  rc_sacked; } ;
struct tcp_rack {TYPE_3__* rc_inp; TYPE_1__ r_ctl; int /*<<< orphan*/  rc_tp; } ;
struct TYPE_7__ {TYPE_2__* inp_socket; int /*<<< orphan*/  inp_in_input; int /*<<< orphan*/  inp_in_hpts; } ;
struct TYPE_6__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_LOG_PROGRESS ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (struct tcpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,struct timeval*) ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  ctf_flight_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rack_verbose_logging ; 
 int /*<<< orphan*/  tcp_get_usecs (struct timeval*) ; 

__attribute__((used)) static inline void
rack_log_progress_event(struct tcp_rack *rack, struct tcpcb *tp, uint32_t tick,  int event, int line)
{
	if (rack_verbose_logging && (tp->t_logstate != TCP_LOG_STATE_OFF)) {
		union tcp_log_stackspecific log;
		struct timeval tv;

		memset(&log.u_bbr, 0, sizeof(log.u_bbr));
		log.u_bbr.inhpts = rack->rc_inp->inp_in_hpts;
		log.u_bbr.ininput = rack->rc_inp->inp_in_input;
		log.u_bbr.flex1 = line;
		log.u_bbr.flex2 = tick;
		log.u_bbr.flex3 = tp->t_maxunacktime;
		log.u_bbr.flex4 = tp->t_acktime;
		log.u_bbr.flex8 = event;
		log.u_bbr.timeStamp = tcp_get_usecs(&tv);
		log.u_bbr.inflight = ctf_flight_size(rack->rc_tp, rack->r_ctl.rc_sacked);
		TCP_LOG_EVENTP(tp, NULL,
		    &rack->rc_inp->inp_socket->so_rcv,
		    &rack->rc_inp->inp_socket->so_snd,
		    BBR_LOG_PROGRESS, 0,
		    0, &log, false, &tv);
	}
}