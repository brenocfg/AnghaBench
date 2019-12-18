#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct mbuf {struct mbuf* m_nextpkt; } ;
typedef  TYPE_1__* iflib_txq_t ;
typedef  TYPE_2__* if_t ;
typedef  TYPE_3__* if_ctx_t ;
struct TYPE_12__ {int ifc_sysctl_tx_abdicate; TYPE_1__* ifc_txqs; } ;
struct TYPE_11__ {int if_drv_flags; int /*<<< orphan*/  if_snd; } ;
struct TYPE_10__ {int /*<<< orphan*/  ift_br; scalar_t__ ift_closed; int /*<<< orphan*/  ift_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALTQ_IS_ENABLED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DBG_COUNTER_INC (int /*<<< orphan*/ ) ; 
 int ENETDOWN ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GROUPTASK_ENQUEUE (int /*<<< orphan*/ *) ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  LINK_ACTIVE (TYPE_3__*) ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 scalar_t__ M_HASHTYPE_GET (struct mbuf*) ; 
 int /*<<< orphan*/  M_IFLIB ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int NTXQSETS (TYPE_3__*) ; 
 int QIDX (TYPE_3__*,struct mbuf*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  TX_BATCH_SIZE ; 
 scalar_t__ __predict_false (int) ; 
 int count ; 
 size_t i ; 
 TYPE_3__* if_getsoftc (TYPE_2__*) ; 
 int /*<<< orphan*/  ifmp_ring_check_drainage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ifmp_ring_enqueue (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf** malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mbuf** marr ; 
 struct mbuf** mp ; 
 struct mbuf* next ; 
 int nitems (struct mbuf**) ; 
 int /*<<< orphan*/  tx_frees ; 
 int /*<<< orphan*/  tx_seen ; 

__attribute__((used)) static int
iflib_if_transmit(if_t ifp, struct mbuf *m)
{
	if_ctx_t	ctx = if_getsoftc(ifp);

	iflib_txq_t txq;
	int err, qidx;
	int abdicate = ctx->ifc_sysctl_tx_abdicate;

	if (__predict_false((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0 || !LINK_ACTIVE(ctx))) {
		DBG_COUNTER_INC(tx_frees);
		m_freem(m);
		return (ENETDOWN);
	}

	MPASS(m->m_nextpkt == NULL);
	/* ALTQ-enabled interfaces always use queue 0. */
	qidx = 0;
	if ((NTXQSETS(ctx) > 1) && M_HASHTYPE_GET(m) && !ALTQ_IS_ENABLED(&ifp->if_snd))
		qidx = QIDX(ctx, m);
	/*
	 * XXX calculate buf_ring based on flowid (divvy up bits?)
	 */
	txq = &ctx->ifc_txqs[qidx];

#ifdef DRIVER_BACKPRESSURE
	if (txq->ift_closed) {
		while (m != NULL) {
			next = m->m_nextpkt;
			m->m_nextpkt = NULL;
			m_freem(m);
			DBG_COUNTER_INC(tx_frees);
			m = next;
		}
		return (ENOBUFS);
	}
#endif
#ifdef notyet
	qidx = count = 0;
	mp = marr;
	next = m;
	do {
		count++;
		next = next->m_nextpkt;
	} while (next != NULL);

	if (count > nitems(marr))
		if ((mp = malloc(count*sizeof(struct mbuf *), M_IFLIB, M_NOWAIT)) == NULL) {
			/* XXX check nextpkt */
			m_freem(m);
			/* XXX simplify for now */
			DBG_COUNTER_INC(tx_frees);
			return (ENOBUFS);
		}
	for (next = m, i = 0; next != NULL; i++) {
		mp[i] = next;
		next = next->m_nextpkt;
		mp[i]->m_nextpkt = NULL;
	}
#endif
	DBG_COUNTER_INC(tx_seen);
	err = ifmp_ring_enqueue(txq->ift_br, (void **)&m, 1, TX_BATCH_SIZE, abdicate);

	if (abdicate)
		GROUPTASK_ENQUEUE(&txq->ift_task);
 	if (err) {
		if (!abdicate)
			GROUPTASK_ENQUEUE(&txq->ift_task);
		/* support forthcoming later */
#ifdef DRIVER_BACKPRESSURE
		txq->ift_closed = TRUE;
#endif
		ifmp_ring_check_drainage(txq->ift_br, TX_BATCH_SIZE);
		m_freem(m);
		DBG_COUNTER_INC(tx_frees);
	}

	return (err);
}