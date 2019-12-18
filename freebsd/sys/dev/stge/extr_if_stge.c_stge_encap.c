#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct stge_txdesc {int /*<<< orphan*/  tx_dmamap; struct mbuf* tx_m; } ;
struct stge_tfd {void* tfd_control; TYPE_2__* tfd_frags; } ;
struct TYPE_10__ {int stge_tx_prod; scalar_t__ stge_tx_cnt; int /*<<< orphan*/  stge_tx_ring_map; int /*<<< orphan*/  stge_tx_ring_tag; int /*<<< orphan*/  stge_tx_tag; int /*<<< orphan*/  stge_txbusyq; int /*<<< orphan*/  stge_txfreeq; } ;
struct TYPE_7__ {struct stge_tfd* stge_tx_ring; } ;
struct stge_softc {TYPE_4__ sc_cdata; TYPE_1__ sc_rdata; } ;
struct TYPE_9__ {int csum_flags; int /*<<< orphan*/  ether_vtag; } ;
struct mbuf {int m_flags; TYPE_3__ m_pkthdr; } ;
struct TYPE_11__ {int /*<<< orphan*/  ds_len; int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_5__ bus_dma_segment_t ;
struct TYPE_8__ {void* frag_word0; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int CSUM_IP ; 
 int CSUM_TCP ; 
 int CSUM_UDP ; 
 int EFBIG ; 
 int EIO ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int FRAG_ADDR (int /*<<< orphan*/ ) ; 
 int FRAG_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int M_VLANTAG ; 
 struct stge_txdesc* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct stge_txdesc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int STGE_CSUM_FEATURES ; 
 int /*<<< orphan*/  STGE_LOCK_ASSERT (struct stge_softc*) ; 
 int STGE_MAXTXSEGS ; 
 scalar_t__ STGE_TX_HIWAT ; 
 int STGE_TX_RING_CNT ; 
 int TFD_FragCount (int) ; 
 int TFD_FrameId (int) ; 
 int TFD_IPChecksumEnable ; 
 int TFD_TCPChecksumEnable ; 
 int TFD_TxDMAIndicate ; 
 int TFD_UDPChecksumEnable ; 
 int TFD_VID (int /*<<< orphan*/ ) ; 
 int TFD_VLANTagInsert ; 
 int TFD_WordAlign (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TFD_WordAlign_disable ; 
 int bus_dmamap_load_mbuf_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,TYPE_5__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* htole64 (int) ; 
 struct mbuf* m_collapse (struct mbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  tx_q ; 

__attribute__((used)) static int
stge_encap(struct stge_softc *sc, struct mbuf **m_head)
{
	struct stge_txdesc *txd;
	struct stge_tfd *tfd;
	struct mbuf *m;
	bus_dma_segment_t txsegs[STGE_MAXTXSEGS];
	int error, i, nsegs, si;
	uint64_t csum_flags, tfc;

	STGE_LOCK_ASSERT(sc);

	if ((txd = STAILQ_FIRST(&sc->sc_cdata.stge_txfreeq)) == NULL)
		return (ENOBUFS);

	error =  bus_dmamap_load_mbuf_sg(sc->sc_cdata.stge_tx_tag,
	    txd->tx_dmamap, *m_head, txsegs, &nsegs, 0);
	if (error == EFBIG) {
		m = m_collapse(*m_head, M_NOWAIT, STGE_MAXTXSEGS);
		if (m == NULL) {
			m_freem(*m_head);
			*m_head = NULL;
			return (ENOMEM);
		}
		*m_head = m;
		error = bus_dmamap_load_mbuf_sg(sc->sc_cdata.stge_tx_tag,
		    txd->tx_dmamap, *m_head, txsegs, &nsegs, 0);
		if (error != 0) {
			m_freem(*m_head);
			*m_head = NULL;
			return (error);
		}
	} else if (error != 0)
		return (error);
	if (nsegs == 0) {
		m_freem(*m_head);
		*m_head = NULL;
		return (EIO);
	}

	m = *m_head;
	csum_flags = 0;
	if ((m->m_pkthdr.csum_flags & STGE_CSUM_FEATURES) != 0) {
		if (m->m_pkthdr.csum_flags & CSUM_IP)
			csum_flags |= TFD_IPChecksumEnable;
		if (m->m_pkthdr.csum_flags & CSUM_TCP)
			csum_flags |= TFD_TCPChecksumEnable;
		else if (m->m_pkthdr.csum_flags & CSUM_UDP)
			csum_flags |= TFD_UDPChecksumEnable;
	}

	si = sc->sc_cdata.stge_tx_prod;
	tfd = &sc->sc_rdata.stge_tx_ring[si];
	for (i = 0; i < nsegs; i++)
		tfd->tfd_frags[i].frag_word0 =
		    htole64(FRAG_ADDR(txsegs[i].ds_addr) |
		    FRAG_LEN(txsegs[i].ds_len));
	sc->sc_cdata.stge_tx_cnt++;

	tfc = TFD_FrameId(si) | TFD_WordAlign(TFD_WordAlign_disable) |
	    TFD_FragCount(nsegs) | csum_flags;
	if (sc->sc_cdata.stge_tx_cnt >= STGE_TX_HIWAT)
		tfc |= TFD_TxDMAIndicate;

	/* Update producer index. */
	sc->sc_cdata.stge_tx_prod = (si + 1) % STGE_TX_RING_CNT;

	/* Check if we have a VLAN tag to insert. */
	if (m->m_flags & M_VLANTAG)
		tfc |= (TFD_VLANTagInsert | TFD_VID(m->m_pkthdr.ether_vtag));
	tfd->tfd_control = htole64(tfc);

	/* Update Tx Queue. */
	STAILQ_REMOVE_HEAD(&sc->sc_cdata.stge_txfreeq, tx_q);
	STAILQ_INSERT_TAIL(&sc->sc_cdata.stge_txbusyq, txd, tx_q);
	txd->tx_m = m;

	/* Sync descriptors. */
	bus_dmamap_sync(sc->sc_cdata.stge_tx_tag, txd->tx_dmamap,
	    BUS_DMASYNC_PREWRITE);
	bus_dmamap_sync(sc->sc_cdata.stge_tx_ring_tag,
	    sc->sc_cdata.stge_tx_ring_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	return (0);
}