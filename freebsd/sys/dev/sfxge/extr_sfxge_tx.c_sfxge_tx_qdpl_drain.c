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
struct sfxge_tx_dpl {unsigned int std_get_count; unsigned int std_get_non_tcp_count; unsigned int std_get_hiwat; struct mbuf* std_get; struct mbuf** std_getp; } ;
struct sfxge_txq {unsigned int added; scalar_t__ init_state; scalar_t__ blocked; struct mbuf* common; struct sfxge_tx_dpl dpl; struct sfxge_softc* sc; } ;
struct sfxge_softc {int /*<<< orphan*/  ifnet; struct mbuf* enp; } ;
struct mbuf {struct mbuf* m_nextpkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_BPF_MTAP (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SFXGE_TXQ_LOCK_ASSERT_OWNED (struct sfxge_txq*) ; 
 scalar_t__ SFXGE_TXQ_STARTED ; 
 unsigned int SFXGE_TX_BATCH ; 
 scalar_t__ __predict_true (int) ; 
 int /*<<< orphan*/  efx_tx_qpush (struct mbuf*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  prefetch_read_many (struct mbuf*) ; 
 scalar_t__ sfxge_is_mbuf_non_tcp (struct mbuf*) ; 
 int sfxge_tx_queue_mbuf (struct sfxge_txq*,struct mbuf*) ; 

__attribute__((used)) static void
sfxge_tx_qdpl_drain(struct sfxge_txq *txq)
{
	struct sfxge_softc *sc;
	struct sfxge_tx_dpl *stdp;
	struct mbuf *mbuf, *next;
	unsigned int count;
	unsigned int non_tcp_count;
	unsigned int pushed;
	int rc;

	SFXGE_TXQ_LOCK_ASSERT_OWNED(txq);

	sc = txq->sc;
	stdp = &txq->dpl;
	pushed = txq->added;

	if (__predict_true(txq->init_state == SFXGE_TXQ_STARTED)) {
		prefetch_read_many(sc->enp);
		prefetch_read_many(txq->common);
	}

	mbuf = stdp->std_get;
	count = stdp->std_get_count;
	non_tcp_count = stdp->std_get_non_tcp_count;

	if (count > stdp->std_get_hiwat)
		stdp->std_get_hiwat = count;

	while (count != 0) {
		KASSERT(mbuf != NULL, ("mbuf == NULL"));

		next = mbuf->m_nextpkt;
		mbuf->m_nextpkt = NULL;

		ETHER_BPF_MTAP(sc->ifnet, mbuf); /* packet capture */

		if (next != NULL)
			prefetch_read_many(next);

		rc = sfxge_tx_queue_mbuf(txq, mbuf);
		--count;
		non_tcp_count -= sfxge_is_mbuf_non_tcp(mbuf);
		mbuf = next;
		if (rc != 0)
			continue;

		if (txq->blocked)
			break;

		/* Push the fragments to the hardware in batches. */
		if (txq->added - pushed >= SFXGE_TX_BATCH) {
			efx_tx_qpush(txq->common, txq->added, pushed);
			pushed = txq->added;
		}
	}

	if (count == 0) {
		KASSERT(mbuf == NULL, ("mbuf != NULL"));
		KASSERT(non_tcp_count == 0,
			("inconsistent TCP/non-TCP detection"));
		stdp->std_get = NULL;
		stdp->std_get_count = 0;
		stdp->std_get_non_tcp_count = 0;
		stdp->std_getp = &stdp->std_get;
	} else {
		stdp->std_get = mbuf;
		stdp->std_get_count = count;
		stdp->std_get_non_tcp_count = non_tcp_count;
	}

	if (txq->added != pushed)
		efx_tx_qpush(txq->common, txq->added, pushed);

	KASSERT(txq->blocked || stdp->std_get_count == 0,
		("queue unblocked but count is non-zero"));
}