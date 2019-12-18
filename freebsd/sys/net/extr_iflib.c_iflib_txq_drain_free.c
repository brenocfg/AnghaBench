#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct mbuf {int dummy; } ;
struct ifmp_ring {int /*<<< orphan*/  size; TYPE_1__* cookie; } ;
typedef  TYPE_1__* iflib_txq_t ;
struct TYPE_4__ {int /*<<< orphan*/  ift_timer; int /*<<< orphan*/  ift_qstatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLOUT_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  CALLOUT_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  DBG_COUNTER_INC (int /*<<< orphan*/ ) ; 
 int IDXDIFF (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFLIB_QUEUE_IDLE ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ __predict_false (int) ; 
 struct mbuf** _ring_peek_one (struct ifmp_ring*,int,int,int) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 scalar_t__ ifmp_ring_is_stalled (struct ifmp_ring*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  tx_frees ; 

__attribute__((used)) static uint32_t
iflib_txq_drain_free(struct ifmp_ring *r, uint32_t cidx, uint32_t pidx)
{
	int i, avail;
	struct mbuf **mp;
	iflib_txq_t txq;

	txq = r->cookie;

	txq->ift_qstatus = IFLIB_QUEUE_IDLE;
	CALLOUT_LOCK(txq);
	callout_stop(&txq->ift_timer);
	CALLOUT_UNLOCK(txq);

	avail = IDXDIFF(pidx, cidx, r->size);
	for (i = 0; i < avail; i++) {
		mp = _ring_peek_one(r, cidx, i, avail - i);
		if (__predict_false(*mp == (struct mbuf *)txq))
			continue;
		m_freem(*mp);
		DBG_COUNTER_INC(tx_frees);
	}
	MPASS(ifmp_ring_is_stalled(r) == 0);
	return (avail);
}