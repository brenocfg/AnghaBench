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
typedef  size_t u_int ;
struct vi_info {struct port_info* pi; } ;
struct txpkts {int npkt; } ;
struct sge_eq {size_t pidx; size_t cidx; int sidx; size_t dbidx; size_t equeqidx; int /*<<< orphan*/  equiq; int /*<<< orphan*/ * desc; } ;
struct sge_txq {struct ifnet* ifp; struct sge_eq eq; } ;
struct port_info {struct adapter* adapter; } ;
struct mp_ring {int size; struct mbuf** items; struct sge_txq* cookie; } ;
struct mbuf {struct mbuf* m_nextpkt; } ;
struct ifnet {struct vi_info* if_softc; } ;
struct fw_eth_tx_pkts_wr {int /*<<< orphan*/  equiq_to_len16; } ;
struct adapter {int flags; } ;

/* Variables and functions */
 int EQ_ESIZE ; 
 int /*<<< orphan*/  ETHER_BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int F_FW_WR_EQUEQ ; 
 int F_FW_WR_EQUIQ ; 
 int IDXDIFF (size_t,size_t,int) ; 
 int /*<<< orphan*/  IDXINCR (size_t,size_t,int) ; 
 int IS_VF ; 
 int MC_RAW_WR ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_ASSERTPKTHDR (struct mbuf*) ; 
 size_t SGE_MAX_WR_NDESC ; 
 int /*<<< orphan*/  TXQ_LOCK (struct sge_txq*) ; 
 int /*<<< orphan*/  TXQ_UNLOCK (struct sge_txq*) ; 
 scalar_t__ __predict_false (int) ; 
 scalar_t__ add_to_txpkts (struct mbuf*,struct txpkts*,size_t) ; 
 scalar_t__ atomic_cmpset_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int discard_tx (struct sge_eq*) ; 
 size_t howmany (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  htobe32 (int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int mbuf_cflags (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_len16 (struct mbuf*) ; 
 scalar_t__ reclaim_tx_descs (struct sge_txq*,int) ; 
 int /*<<< orphan*/  ring_eq_db (struct adapter*,struct sge_eq*,size_t) ; 
 int total_available_tx_desc (struct sge_eq*) ; 
 scalar_t__ try_txpkts (struct mbuf*,struct mbuf*,struct txpkts*,size_t) ; 
 scalar_t__ wr_can_update_eq (struct fw_eth_tx_pkts_wr*) ; 
 size_t write_raw_wr (struct sge_txq*,void*,struct mbuf*,size_t) ; 
 size_t write_txpkt_vm_wr (struct adapter*,struct sge_txq*,void*,struct mbuf*,size_t) ; 
 size_t write_txpkt_wr (struct sge_txq*,void*,struct mbuf*,size_t) ; 
 size_t write_txpkts_wr (struct sge_txq*,struct fw_eth_tx_pkts_wr*,struct mbuf*,struct txpkts*,size_t) ; 

__attribute__((used)) static u_int
eth_tx(struct mp_ring *r, u_int cidx, u_int pidx)
{
	struct sge_txq *txq = r->cookie;
	struct sge_eq *eq = &txq->eq;
	struct ifnet *ifp = txq->ifp;
	struct vi_info *vi = ifp->if_softc;
	struct port_info *pi = vi->pi;
	struct adapter *sc = pi->adapter;
	u_int total, remaining;		/* # of packets */
	u_int available, dbdiff;	/* # of hardware descriptors */
	u_int n, next_cidx;
	struct mbuf *m0, *tail;
	struct txpkts txp;
	struct fw_eth_tx_pkts_wr *wr;	/* any fw WR struct will do */

	remaining = IDXDIFF(pidx, cidx, r->size);
	MPASS(remaining > 0);	/* Must not be called without work to do. */
	total = 0;

	TXQ_LOCK(txq);
	if (__predict_false(discard_tx(eq))) {
		while (cidx != pidx) {
			m0 = r->items[cidx];
			m_freem(m0);
			if (++cidx == r->size)
				cidx = 0;
		}
		reclaim_tx_descs(txq, 2048);
		total = remaining;
		goto done;
	}

	/* How many hardware descriptors do we have readily available. */
	if (eq->pidx == eq->cidx)
		available = eq->sidx - 1;
	else
		available = IDXDIFF(eq->cidx, eq->pidx, eq->sidx) - 1;
	dbdiff = IDXDIFF(eq->pidx, eq->dbidx, eq->sidx);

	while (remaining > 0) {

		m0 = r->items[cidx];
		M_ASSERTPKTHDR(m0);
		MPASS(m0->m_nextpkt == NULL);

		if (available < SGE_MAX_WR_NDESC) {
			available += reclaim_tx_descs(txq, 64);
			if (available < howmany(mbuf_len16(m0), EQ_ESIZE / 16))
				break;	/* out of descriptors */
		}

		next_cidx = cidx + 1;
		if (__predict_false(next_cidx == r->size))
			next_cidx = 0;

		wr = (void *)&eq->desc[eq->pidx];
		if (sc->flags & IS_VF) {
			total++;
			remaining--;
			ETHER_BPF_MTAP(ifp, m0);
			n = write_txpkt_vm_wr(sc, txq, (void *)wr, m0,
			    available);
		} else if (remaining > 1 &&
		    try_txpkts(m0, r->items[next_cidx], &txp, available) == 0) {

			/* pkts at cidx, next_cidx should both be in txp. */
			MPASS(txp.npkt == 2);
			tail = r->items[next_cidx];
			MPASS(tail->m_nextpkt == NULL);
			ETHER_BPF_MTAP(ifp, m0);
			ETHER_BPF_MTAP(ifp, tail);
			m0->m_nextpkt = tail;

			if (__predict_false(++next_cidx == r->size))
				next_cidx = 0;

			while (next_cidx != pidx) {
				if (add_to_txpkts(r->items[next_cidx], &txp,
				    available) != 0)
					break;
				tail->m_nextpkt = r->items[next_cidx];
				tail = tail->m_nextpkt;
				ETHER_BPF_MTAP(ifp, tail);
				if (__predict_false(++next_cidx == r->size))
					next_cidx = 0;
			}

			n = write_txpkts_wr(txq, wr, m0, &txp, available);
			total += txp.npkt;
			remaining -= txp.npkt;
		} else if (mbuf_cflags(m0) & MC_RAW_WR) {
			total++;
			remaining--;
			n = write_raw_wr(txq, (void *)wr, m0, available);
		} else {
			total++;
			remaining--;
			ETHER_BPF_MTAP(ifp, m0);
			n = write_txpkt_wr(txq, (void *)wr, m0, available);
		}
		MPASS(n >= 1 && n <= available && n <= SGE_MAX_WR_NDESC);

		available -= n;
		dbdiff += n;
		IDXINCR(eq->pidx, n, eq->sidx);

		if (wr_can_update_eq(wr)) {
			if (total_available_tx_desc(eq) < eq->sidx / 4 &&
			    atomic_cmpset_int(&eq->equiq, 0, 1)) {
				wr->equiq_to_len16 |= htobe32(F_FW_WR_EQUIQ |
				    F_FW_WR_EQUEQ);
				eq->equeqidx = eq->pidx;
			} else if (IDXDIFF(eq->pidx, eq->equeqidx, eq->sidx) >=
			    32) {
				wr->equiq_to_len16 |= htobe32(F_FW_WR_EQUEQ);
				eq->equeqidx = eq->pidx;
			}
		}

		if (dbdiff >= 16 && remaining >= 4) {
			ring_eq_db(sc, eq, dbdiff);
			available += reclaim_tx_descs(txq, 4 * dbdiff);
			dbdiff = 0;
		}

		cidx = next_cidx;
	}
	if (dbdiff != 0) {
		ring_eq_db(sc, eq, dbdiff);
		reclaim_tx_descs(txq, 32);
	}
done:
	TXQ_UNLOCK(txq);

	return (total);
}