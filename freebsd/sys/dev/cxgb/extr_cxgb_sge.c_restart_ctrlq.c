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
struct sge_txq {size_t in_use; size_t size; size_t pidx; int gen; int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  stops; int /*<<< orphan*/  sendq; int /*<<< orphan*/ * desc; } ;
struct sge_qset {int /*<<< orphan*/  txq_stopped; TYPE_1__* port; struct sge_txq* txq; } ;
struct mbuf {int /*<<< orphan*/  m_len; int /*<<< orphan*/  m_data; } ;
typedef  int /*<<< orphan*/  adapter_t ;
struct TYPE_2__ {int /*<<< orphan*/ * adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_KDOORBELL ; 
 int F_SELEGRCNTX ; 
 size_t TXQ_CTRL ; 
 int /*<<< orphan*/  TXQ_LOCK (struct sge_qset*) ; 
 int /*<<< orphan*/  TXQ_UNLOCK (struct sge_qset*) ; 
 int V_EGRCNTX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_free (struct mbuf*) ; 
 struct mbuf* mbufq_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ mbufq_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reclaim_completed_tx_imm (struct sge_txq*) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ should_restart_tx (struct sge_txq*) ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_clear_bit (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_imm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
restart_ctrlq(void *data, int npending)
{
	struct mbuf *m;
	struct sge_qset *qs = (struct sge_qset *)data;
	struct sge_txq *q = &qs->txq[TXQ_CTRL];
	adapter_t *adap = qs->port->adapter;

	TXQ_LOCK(qs);
again:	reclaim_completed_tx_imm(q);

	while (q->in_use < q->size &&
	       (m = mbufq_dequeue(&q->sendq)) != NULL) {

		write_imm(&q->desc[q->pidx], m->m_data, m->m_len, q->gen);
		m_free(m);

		if (++q->pidx >= q->size) {
			q->pidx = 0;
			q->gen ^= 1;
		}
		q->in_use++;
	}
	if (mbufq_len(&q->sendq)) {
		setbit(&qs->txq_stopped, TXQ_CTRL);

		if (should_restart_tx(q) &&
		    test_and_clear_bit(TXQ_CTRL, &qs->txq_stopped))
			goto again;
		q->stops++;
	}
	TXQ_UNLOCK(qs);
	t3_write_reg(adap, A_SG_KDOORBELL,
		     F_SELEGRCNTX | V_EGRCNTX(q->cntxt_id));
}