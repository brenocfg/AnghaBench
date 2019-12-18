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
struct sge_txq {unsigned int size; unsigned int in_use; int /*<<< orphan*/  stops; int /*<<< orphan*/  sendq; } ;
struct sge_qset {int /*<<< orphan*/  txq_stopped; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  mbufq_enqueue (int /*<<< orphan*/ *,struct mbuf*) ; 
 int mbufq_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ should_restart_tx (struct sge_txq*) ; 
 scalar_t__ test_and_clear_bit (unsigned int,int /*<<< orphan*/ *) ; 
 struct sge_qset* txq_to_qset (struct sge_txq*,unsigned int) ; 

__attribute__((used)) static __inline int
check_desc_avail(adapter_t *adap, struct sge_txq *q,
		 struct mbuf *m, unsigned int ndesc,
		 unsigned int qid)
{
	/* 
	 * XXX We currently only use this for checking the control queue
	 * the control queue is only used for binding qsets which happens
	 * at init time so we are guaranteed enough descriptors
	 */
	if (__predict_false(mbufq_len(&q->sendq))) {
addq_exit:	(void )mbufq_enqueue(&q->sendq, m);
		return 1;
	}
	if (__predict_false(q->size - q->in_use < ndesc)) {

		struct sge_qset *qs = txq_to_qset(q, qid);

		setbit(&qs->txq_stopped, qid);
		if (should_restart_tx(q) &&
		    test_and_clear_bit(qid, &qs->txq_stopped))
			return 2;

		q->stops++;
		goto addq_exit;
	}
	return 0;
}