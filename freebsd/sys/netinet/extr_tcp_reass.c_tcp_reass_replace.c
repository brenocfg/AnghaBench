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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  tcp_seq ;
struct tseg_qent {int tqe_mbuf_cnt; int tqe_len; int tqe_flags; struct mbuf* tqe_m; int /*<<< orphan*/  tqe_start; struct mbuf* tqe_last; } ;
struct tcpcb {int t_segqmbuflen; int /*<<< orphan*/  t_rcvoopack; } ;
struct TYPE_2__ {int len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  TCPSTAT_ADD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_R_LOG_REPLACE ; 
 int TH_FIN ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  tcp_log_reassm (struct tcpcb*,struct tseg_qent*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcps_rcvoobyte ; 
 int /*<<< orphan*/  tcps_rcvoopack ; 

__attribute__((used)) static void 
tcp_reass_replace(struct tcpcb *tp, struct tseg_qent *q, struct mbuf *m,
    tcp_seq seq, int len, struct mbuf *mlast, int mbufoh, uint8_t flags)
{
	/*
	 * Free the data in q, and replace
	 * it with the new segment.
	 */
	int len_dif;

#ifdef TCP_REASS_LOGGING
	tcp_log_reassm(tp, q, NULL, seq, len, TCP_R_LOG_REPLACE, 0);
#endif
	m_freem(q->tqe_m);
	KASSERT(tp->t_segqmbuflen >= q->tqe_mbuf_cnt,
		("Tp:%p seg queue goes negative", tp));
	tp->t_segqmbuflen -= q->tqe_mbuf_cnt;		       
	q->tqe_mbuf_cnt = mbufoh;
	q->tqe_m = m;
	q->tqe_last = mlast;
	q->tqe_start = seq;
	if (len > q->tqe_len)
		len_dif = len - q->tqe_len;
	else
		len_dif = 0;
	tp->t_rcvoopack++;
	TCPSTAT_INC(tcps_rcvoopack);
	TCPSTAT_ADD(tcps_rcvoobyte, len_dif);
	q->tqe_len = len;
	q->tqe_flags = (flags & TH_FIN);
	q->tqe_m->m_pkthdr.len = q->tqe_len;
	tp->t_segqmbuflen += mbufoh;

}