#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tseg_qent {int /*<<< orphan*/  tqe_m; } ;
struct tcpcb {scalar_t__ t_segqlen; scalar_t__ t_segqmbuflen; int /*<<< orphan*/  t_segq; int /*<<< orphan*/  t_inpcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_WLOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct tseg_qent* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct tseg_qent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_reass_zone ; 
 int /*<<< orphan*/  tqe_q ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct tseg_qent*) ; 

void
tcp_reass_flush(struct tcpcb *tp)
{
	struct tseg_qent *qe;

	INP_WLOCK_ASSERT(tp->t_inpcb);

	while ((qe = TAILQ_FIRST(&tp->t_segq)) != NULL) {
		TAILQ_REMOVE(&tp->t_segq, qe, tqe_q);
		m_freem(qe->tqe_m);
		uma_zfree(tcp_reass_zone, qe);
		tp->t_segqlen--;
	}
	tp->t_segqmbuflen = 0;
	KASSERT((tp->t_segqlen == 0),
	    ("TCP reass queue %p segment count is %d instead of 0 after flush.",
	    tp, tp->t_segqlen));
}