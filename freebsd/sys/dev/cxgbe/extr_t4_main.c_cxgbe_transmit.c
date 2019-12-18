#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vi_info {size_t first_txq; int ntxq; int rsrv_noflowq; struct port_info* pi; } ;
struct sge_txq {int /*<<< orphan*/  r; } ;
struct TYPE_5__ {int link_ok; } ;
struct port_info {int /*<<< orphan*/  tx_parse_error; TYPE_1__ link_cfg; struct adapter* adapter; } ;
struct TYPE_7__ {int csum_flags; int flowid; TYPE_4__* snd_tag; } ;
struct mbuf {TYPE_3__ m_pkthdr; int /*<<< orphan*/ * m_nextpkt; } ;
struct ifnet {struct vi_info* if_softc; } ;
struct cxgbe_snd_tag {scalar_t__ type; } ;
struct TYPE_6__ {struct sge_txq* txq; } ;
struct adapter {TYPE_2__ sge; } ;
struct TYPE_8__ {struct ifnet* ifp; } ;

/* Variables and functions */
 int CSUM_SND_TAG ; 
 int ENETDOWN ; 
 scalar_t__ IF_SND_TAG_TYPE_RATE_LIMIT ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_ASSERTPKTHDR (struct mbuf*) ; 
 scalar_t__ M_HASHTYPE_GET (struct mbuf*) ; 
 scalar_t__ M_HASHTYPE_NONE ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int ethofld_transmit (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int mp_ring_enqueue (int /*<<< orphan*/ ,void**,int,int) ; 
 struct cxgbe_snd_tag* mst_to_cst (TYPE_4__*) ; 
 int parse_pkt (struct adapter*,struct mbuf**) ; 

__attribute__((used)) static int
cxgbe_transmit(struct ifnet *ifp, struct mbuf *m)
{
	struct vi_info *vi = ifp->if_softc;
	struct port_info *pi = vi->pi;
	struct adapter *sc = pi->adapter;
	struct sge_txq *txq;
#ifdef RATELIMIT
	struct cxgbe_snd_tag *cst;
#endif
	void *items[1];
	int rc;

	M_ASSERTPKTHDR(m);
	MPASS(m->m_nextpkt == NULL);	/* not quite ready for this yet */
#ifdef RATELIMIT
	if (m->m_pkthdr.csum_flags & CSUM_SND_TAG)
		MPASS(m->m_pkthdr.snd_tag->ifp == ifp);
#endif

	if (__predict_false(pi->link_cfg.link_ok == false)) {
		m_freem(m);
		return (ENETDOWN);
	}

	rc = parse_pkt(sc, &m);
	if (__predict_false(rc != 0)) {
		MPASS(m == NULL);			/* was freed already */
		atomic_add_int(&pi->tx_parse_error, 1);	/* rare, atomic is ok */
		return (rc);
	}
#ifdef RATELIMIT
	if (m->m_pkthdr.csum_flags & CSUM_SND_TAG) {
		cst = mst_to_cst(m->m_pkthdr.snd_tag);
		if (cst->type == IF_SND_TAG_TYPE_RATE_LIMIT)
			return (ethofld_transmit(ifp, m));
	}
#endif

	/* Select a txq. */
	txq = &sc->sge.txq[vi->first_txq];
	if (M_HASHTYPE_GET(m) != M_HASHTYPE_NONE)
		txq += ((m->m_pkthdr.flowid % (vi->ntxq - vi->rsrv_noflowq)) +
		    vi->rsrv_noflowq);

	items[0] = m;
	rc = mp_ring_enqueue(txq->r, items, 1, 4096);
	if (__predict_false(rc != 0))
		m_freem(m);

	return (rc);
}