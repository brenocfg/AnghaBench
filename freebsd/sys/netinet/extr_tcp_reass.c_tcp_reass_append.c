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
struct tseg_qent {int tqe_len; int tqe_flags; int tqe_mbuf_cnt; TYPE_2__* tqe_m; int /*<<< orphan*/  tqe_start; struct mbuf* tqe_last; } ;
struct tcphdr {int th_flags; int /*<<< orphan*/  th_seq; } ;
struct tcpcb {int /*<<< orphan*/  t_rcvoopack; } ;
struct mbuf {struct mbuf* m_next; } ;
struct TYPE_3__ {int len; } ;
struct TYPE_4__ {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCPSTAT_ADD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_R_LOG_APPEND ; 
 int TH_FIN ; 
 int /*<<< orphan*/  tcp_log_reassm (struct tcpcb*,struct tseg_qent*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_reass_log_new_in (struct tcpcb*,int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ,struct tseg_qent*) ; 
 int /*<<< orphan*/  tcps_rcvoobyte ; 
 int /*<<< orphan*/  tcps_rcvoopack ; 

__attribute__((used)) static void
tcp_reass_append(struct tcpcb *tp, struct tseg_qent *last,
    struct mbuf *m, struct tcphdr *th, int tlen, 
    struct mbuf *mlast, int lenofoh)
{

#ifdef TCP_REASS_LOGGING
	tcp_log_reassm(tp, last, NULL, th->th_seq, tlen, TCP_R_LOG_APPEND, 0);
#endif
	last->tqe_len += tlen;
	last->tqe_m->m_pkthdr.len += tlen;
	/* Preserve the FIN bit if its there */
	last->tqe_flags |= (th->th_flags & TH_FIN);
	last->tqe_last->m_next = m;
	last->tqe_last = mlast;
	last->tqe_mbuf_cnt += lenofoh;
	tp->t_rcvoopack++;
	TCPSTAT_INC(tcps_rcvoopack);
	TCPSTAT_ADD(tcps_rcvoobyte, tlen);
#ifdef TCP_REASS_LOGGING
	tcp_reass_log_new_in(tp, last->tqe_start, lenofoh, last->tqe_m,
			     TCP_R_LOG_APPEND,
			     last);
#endif
}