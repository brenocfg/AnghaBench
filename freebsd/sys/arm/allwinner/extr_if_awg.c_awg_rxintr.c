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
typedef  int uint32_t ;
struct TYPE_7__ {int len; int csum_flags; int csum_data; int /*<<< orphan*/  rcvif; } ;
struct mbuf {int m_len; struct mbuf* m_nextpkt; TYPE_3__ m_pkthdr; } ;
struct TYPE_8__ {int cur; int /*<<< orphan*/  desc_map; int /*<<< orphan*/  desc_tag; TYPE_2__* buf_map; TYPE_1__* desc_ring; } ;
struct awg_softc {TYPE_4__ rx; int /*<<< orphan*/  ifp; } ;
typedef  int /*<<< orphan*/  if_t ;
struct TYPE_6__ {struct mbuf* mbuf; } ;
struct TYPE_5__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  AWG_LOCK (struct awg_softc*) ; 
 int /*<<< orphan*/  AWG_UNLOCK (struct awg_softc*) ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int CSUM_DATA_VALID ; 
 int CSUM_IP_CHECKED ; 
 int CSUM_IP_VALID ; 
 int CSUM_PSEUDO_HDR ; 
 int IFCAP_RXCSUM ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_IQDROPS ; 
 int RX_DESC_CTL ; 
 int RX_FRM_LEN ; 
 int RX_FRM_LEN_SHIFT ; 
 int RX_FRM_TYPE ; 
 int RX_HEADER_ERR ; 
 int RX_NEXT (int) ; 
 int RX_NO_ENOUGH_BUF_ERR ; 
 int RX_OVERFLOW_ERR ; 
 int RX_PAYLOAD_ERR ; 
 int awg_newbuf_rx (struct awg_softc*,int) ; 
 int /*<<< orphan*/  awg_reuse_rxdesc (struct awg_softc*,int) ; 
 int awg_rx_batch ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_input (int /*<<< orphan*/ ,struct mbuf*) ; 
 int le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
awg_rxintr(struct awg_softc *sc)
{
	if_t ifp;
	struct mbuf *m, *mh, *mt;
	int error, index, len, cnt, npkt;
	uint32_t status;

	ifp = sc->ifp;
	mh = mt = NULL;
	cnt = 0;
	npkt = 0;

	bus_dmamap_sync(sc->rx.desc_tag, sc->rx.desc_map,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

	for (index = sc->rx.cur; ; index = RX_NEXT(index)) {
		status = le32toh(sc->rx.desc_ring[index].status);
		if ((status & RX_DESC_CTL) != 0)
			break;

		len = (status & RX_FRM_LEN) >> RX_FRM_LEN_SHIFT;

		if (len == 0) {
			if ((status & (RX_NO_ENOUGH_BUF_ERR | RX_OVERFLOW_ERR)) != 0)
				if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
			awg_reuse_rxdesc(sc, index);
			continue;
		}

		m = sc->rx.buf_map[index].mbuf;

		error = awg_newbuf_rx(sc, index);
		if (error != 0) {
			if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
			awg_reuse_rxdesc(sc, index);
			continue;
		}

		m->m_pkthdr.rcvif = ifp;
		m->m_pkthdr.len = len;
		m->m_len = len;
		if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);

		if ((if_getcapenable(ifp) & IFCAP_RXCSUM) != 0 &&
		    (status & RX_FRM_TYPE) != 0) {
			m->m_pkthdr.csum_flags = CSUM_IP_CHECKED;
			if ((status & RX_HEADER_ERR) == 0)
				m->m_pkthdr.csum_flags |= CSUM_IP_VALID;
			if ((status & RX_PAYLOAD_ERR) == 0) {
				m->m_pkthdr.csum_flags |=
				    CSUM_DATA_VALID | CSUM_PSEUDO_HDR;
				m->m_pkthdr.csum_data = 0xffff;
			}
		}

		m->m_nextpkt = NULL;
		if (mh == NULL)
			mh = m;
		else
			mt->m_nextpkt = m;
		mt = m;
		++cnt;
		++npkt;

		if (cnt == awg_rx_batch) {
			AWG_UNLOCK(sc);
			if_input(ifp, mh);
			AWG_LOCK(sc);
			mh = mt = NULL;
			cnt = 0;
		}
	}

	if (index != sc->rx.cur) {
		bus_dmamap_sync(sc->rx.desc_tag, sc->rx.desc_map,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
	}

	if (mh != NULL) {
		AWG_UNLOCK(sc);
		if_input(ifp, mh);
		AWG_LOCK(sc);
	}

	sc->rx.cur = index;

	return (npkt);
}