#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tseg_qent {int tqe_flags; scalar_t__ tqe_len; TYPE_3__* tqe_m; scalar_t__ tqe_mbuf_cnt; TYPE_1__* tqe_last; } ;
struct tcpcb {int /*<<< orphan*/  t_segqlen; int /*<<< orphan*/  t_segq; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;
struct TYPE_6__ {TYPE_2__ m_pkthdr; } ;
struct TYPE_4__ {TYPE_3__* m_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct tseg_qent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_R_LOG_MERGE_INTO ; 
 int TH_FIN ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  merge_into ; 
 int /*<<< orphan*/  tcp_log_reassm (struct tcpcb*,struct tseg_qent*,struct tseg_qent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_reass_zone ; 
 int /*<<< orphan*/  tqe_q ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct tseg_qent*) ; 

__attribute__((used)) static void
tcp_reass_merge_into(struct tcpcb *tp, struct tseg_qent *ent,
    struct tseg_qent *q)
{
	/* 
	 * Merge q into ent and free q from the list.
	 */
#ifdef TCP_REASS_LOGGING
	tcp_log_reassm(tp, q, ent, 0, 0, TCP_R_LOG_MERGE_INTO, 0);
#endif
#ifdef TCP_REASS_COUNTERS
	counter_u64_add(merge_into, 1);
#endif
	ent->tqe_last->m_next = q->tqe_m;
	ent->tqe_last = q->tqe_last;
	ent->tqe_len += q->tqe_len;
	ent->tqe_mbuf_cnt += q->tqe_mbuf_cnt;
	ent->tqe_m->m_pkthdr.len += q->tqe_len;
	ent->tqe_flags |= (q->tqe_flags & TH_FIN);
	TAILQ_REMOVE(&tp->t_segq, q, tqe_q);
	uma_zfree(tcp_reass_zone, q);
	tp->t_segqlen--;

}