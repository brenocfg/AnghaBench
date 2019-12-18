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
struct TYPE_10__ {int flex8; uintptr_t cur_del_rate; uintptr_t bw_inuse; int /*<<< orphan*/  lost; int /*<<< orphan*/  applimited; int /*<<< orphan*/  pkts_out; int /*<<< orphan*/  cwnd_gain; int /*<<< orphan*/  pacing_gain; int /*<<< orphan*/  lt_epoch; void* delivered; int /*<<< orphan*/  epoch; void* timeStamp; void* inflight; int /*<<< orphan*/  flex7; int /*<<< orphan*/  flex6; int /*<<< orphan*/  rttProp; int /*<<< orphan*/  delRate; int /*<<< orphan*/  flex5; int /*<<< orphan*/  flex4; int /*<<< orphan*/  flex3; scalar_t__ flex2; int /*<<< orphan*/  flex1; } ;
union tcp_log_stackspecific {TYPE_4__ u_bbr; } ;
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct timeval {int dummy; } ;
struct tcpcb {scalar_t__ t_logstate; TYPE_6__* t_inpcb; } ;
struct TYPE_7__ {scalar_t__ len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct lro_entry {int /*<<< orphan*/  mbuf_appended; int /*<<< orphan*/  ulp_csum; int /*<<< orphan*/  mbuf_cnt; TYPE_3__* m_head; int /*<<< orphan*/  window; int /*<<< orphan*/  ack_seq; int /*<<< orphan*/  next_seq; int /*<<< orphan*/  p_len; int /*<<< orphan*/  append_cnt; } ;
struct lro_ctrl {int /*<<< orphan*/  lro_ackcnt_lim; int /*<<< orphan*/  lro_length_lim; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_12__ {TYPE_5__* inp_socket; } ;
struct TYPE_11__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;
struct TYPE_8__ {int /*<<< orphan*/  rcv_tstmp; int /*<<< orphan*/  len; } ;
struct TYPE_9__ {TYPE_2__ m_pkthdr; int /*<<< orphan*/  m_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_LOG_EVENTP (struct tcpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,struct timeval*) ; 
 int /*<<< orphan*/  TCP_LOG_LRO ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  memset (union tcp_log_stackspecific*,int /*<<< orphan*/ ,int) ; 
 void* tcp_get_usecs (struct timeval*) ; 

__attribute__((used)) static void
tcp_lro_log(struct tcpcb *tp, struct lro_ctrl *lc,
	    struct lro_entry *le, struct mbuf *m, int frm, int32_t tcp_data_len,
	    uint32_t th_seq , uint32_t th_ack, uint16_t th_win)
{
	if (tp->t_logstate != TCP_LOG_STATE_OFF) {
		union tcp_log_stackspecific log;
		struct timeval tv;
		uint32_t cts;
		
		cts = tcp_get_usecs(&tv);
		memset(&log, 0, sizeof(union tcp_log_stackspecific));
		log.u_bbr.flex8 = frm;
		log.u_bbr.flex1 = tcp_data_len;
		if (m)
			log.u_bbr.flex2 = m->m_pkthdr.len;
		else
			log.u_bbr.flex2 = 0;
		log.u_bbr.flex3 = le->append_cnt;
		log.u_bbr.flex4 = le->p_len;
		log.u_bbr.flex5 = le->m_head->m_pkthdr.len;
		log.u_bbr.delRate = le->m_head->m_flags;
		log.u_bbr.rttProp = le->m_head->m_pkthdr.rcv_tstmp;
		log.u_bbr.flex6 = lc->lro_length_lim;
		log.u_bbr.flex7 = lc->lro_ackcnt_lim;
		log.u_bbr.inflight = th_seq;
		log.u_bbr.timeStamp = cts;
		log.u_bbr.epoch = le->next_seq;
		log.u_bbr.delivered = th_ack;
		log.u_bbr.lt_epoch = le->ack_seq;
		log.u_bbr.pacing_gain = th_win;
		log.u_bbr.cwnd_gain = le->window;
		log.u_bbr.cur_del_rate = (uintptr_t)m;
		log.u_bbr.bw_inuse = (uintptr_t)le->m_head;
		log.u_bbr.pkts_out = le->mbuf_cnt;	/* Total mbufs added */
		log.u_bbr.applimited = le->ulp_csum;
		log.u_bbr.lost = le->mbuf_appended;
		TCP_LOG_EVENTP(tp, NULL,
			       &tp->t_inpcb->inp_socket->so_rcv,
			       &tp->t_inpcb->inp_socket->so_snd,
			       TCP_LOG_LRO, 0,
			       0, &log, false, &tv);
	}
}