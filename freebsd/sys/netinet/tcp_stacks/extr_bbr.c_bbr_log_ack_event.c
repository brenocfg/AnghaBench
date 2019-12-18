#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int flex3; int /*<<< orphan*/  flex8; int /*<<< orphan*/  flex7; int /*<<< orphan*/  flex4; scalar_t__ pkts_out; scalar_t__ flex6; void* flex5; void* lt_epoch; int /*<<< orphan*/  flex2; int /*<<< orphan*/  flex1; } ;
union tcp_log_stackspecific {TYPE_5__ u_bbr; } ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct timeval {int tv_sec; int tv_usec; } ;
struct timespec {int tv_sec; int tv_nsec; } ;
struct tcpopt {int dummy; } ;
struct tcphdr {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  rc_target_at_state; int /*<<< orphan*/  rc_lost_bytes; } ;
struct tcp_bbr {int /*<<< orphan*/  rc_tv; TYPE_4__* rc_inp; TYPE_6__* rc_tp; int /*<<< orphan*/  rc_in_persist; int /*<<< orphan*/  r_wanted_output; TYPE_2__ r_ctl; } ;
struct TYPE_7__ {int rcv_tstmp; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_12__ {scalar_t__ t_logstate; } ;
struct TYPE_10__ {TYPE_3__* inp_socket; } ;
struct TYPE_9__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int M_TSTMP ; 
 int M_TSTMP_LRO ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (TYPE_6__*,struct tcphdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TCP_LOG_IN ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  bbr_fill_in_logging_data (struct tcp_bbr*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_tstmp2timespec (struct mbuf*,struct timespec*) ; 
 scalar_t__ tcp_get_usecs (struct timeval*) ; 
 void* tcp_tv_to_usectick (struct timeval*) ; 

__attribute__((used)) static void
bbr_log_ack_event(struct tcp_bbr *bbr, struct tcphdr *th, struct tcpopt *to, uint32_t tlen,
		  uint16_t nsegs, uint32_t cts, int32_t nxt_pkt, struct mbuf *m)
{
	if (bbr->rc_tp->t_logstate != TCP_LOG_STATE_OFF) {
		union tcp_log_stackspecific log;
		struct timeval tv;

		bbr_fill_in_logging_data(bbr, &log.u_bbr, cts);
		log.u_bbr.flex1 = nsegs;
		log.u_bbr.flex2 = bbr->r_ctl.rc_lost_bytes;
		if (m) {
			struct timespec ts;

			log.u_bbr.flex3 = m->m_flags;
			if (m->m_flags & M_TSTMP) {
				mbuf_tstmp2timespec(m, &ts);
				tv.tv_sec = ts.tv_sec;
				tv.tv_usec = ts.tv_nsec / 1000;
				log.u_bbr.lt_epoch = tcp_tv_to_usectick(&tv);
			} else {
				log.u_bbr.lt_epoch = 0;
			}
			if (m->m_flags & M_TSTMP_LRO) {
				tv.tv_sec = m->m_pkthdr.rcv_tstmp / 1000000000;
				tv.tv_usec = (m->m_pkthdr.rcv_tstmp % 1000000000) / 1000;
				log.u_bbr.flex5 = tcp_tv_to_usectick(&tv);
			} else {
				/* No arrival timestamp */
				log.u_bbr.flex5 = 0;
			}

			log.u_bbr.pkts_out = tcp_get_usecs(&tv);
		} else {
			log.u_bbr.flex3 = 0;
			log.u_bbr.flex5 = 0;
			log.u_bbr.flex6 = 0;
			log.u_bbr.pkts_out = 0;
		}
		log.u_bbr.flex4 = bbr->r_ctl.rc_target_at_state;
		log.u_bbr.flex7 = bbr->r_wanted_output;
		log.u_bbr.flex8 = bbr->rc_in_persist;
		TCP_LOG_EVENTP(bbr->rc_tp, th,
		    &bbr->rc_inp->inp_socket->so_rcv,
		    &bbr->rc_inp->inp_socket->so_snd,
		    TCP_LOG_IN, 0,
		    tlen, &log, true, &bbr->rc_tv);
	}
}