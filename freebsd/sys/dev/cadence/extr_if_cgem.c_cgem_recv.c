#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int len; int csum_flags; int csum_data; int /*<<< orphan*/  rcvif; } ;
struct mbuf {int m_len; struct mbuf* m_next; TYPE_2__ m_pkthdr; int /*<<< orphan*/  m_data; } ;
struct cgem_softc {scalar_t__ rxring_queued; size_t rxring_tl_ptr; int /*<<< orphan*/ ** rxring_m_dmamap; int /*<<< orphan*/  mbuf_dma_tag; struct mbuf** rxring_m; TYPE_1__* rxring; int /*<<< orphan*/  ifp; } ;
typedef  int /*<<< orphan*/  if_t ;
struct TYPE_3__ {int addr; int ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  CGEM_ASSERT_LOCKED (struct cgem_softc*) ; 
 int /*<<< orphan*/  CGEM_LOCK (struct cgem_softc*) ; 
 size_t CGEM_NUM_RX_DESCS ; 
 int CGEM_RXDESC_BAD_FCS ; 
 int CGEM_RXDESC_CKSUM_STAT_IP_GOOD ; 
 int CGEM_RXDESC_CKSUM_STAT_MASK ; 
 int CGEM_RXDESC_CKSUM_STAT_TCP_GOOD ; 
 int CGEM_RXDESC_CKSUM_STAT_UDP_GOOD ; 
 int CGEM_RXDESC_EOF ; 
 int CGEM_RXDESC_LENGTH_MASK ; 
 int CGEM_RXDESC_OWN ; 
 int CGEM_RXDESC_SOF ; 
 int /*<<< orphan*/  CGEM_UNLOCK (struct cgem_softc*) ; 
 int CSUM_DATA_VALID ; 
 int CSUM_IP_CHECKED ; 
 int CSUM_IP_VALID ; 
 int CSUM_PSEUDO_HDR ; 
 scalar_t__ ETHER_ALIGN ; 
 int IFCAP_RXCSUM ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cgem_fill_rqueue (struct cgem_softc*) ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_input (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  m_free (struct mbuf*) ; 

__attribute__((used)) static void
cgem_recv(struct cgem_softc *sc)
{
	if_t ifp = sc->ifp;
	struct mbuf *m, *m_hd, **m_tl;
	uint32_t ctl;

	CGEM_ASSERT_LOCKED(sc);

	/* Pick up all packets in which the OWN bit is set. */
	m_hd = NULL;
	m_tl = &m_hd;
	while (sc->rxring_queued > 0 &&
	       (sc->rxring[sc->rxring_tl_ptr].addr & CGEM_RXDESC_OWN) != 0) {

		ctl = sc->rxring[sc->rxring_tl_ptr].ctl;

		/* Grab filled mbuf. */
		m = sc->rxring_m[sc->rxring_tl_ptr];
		sc->rxring_m[sc->rxring_tl_ptr] = NULL;

		/* Sync cache with receive buffer. */
		bus_dmamap_sync(sc->mbuf_dma_tag,
				sc->rxring_m_dmamap[sc->rxring_tl_ptr],
				BUS_DMASYNC_POSTREAD);

		/* Unload and destroy dmamap. */
		bus_dmamap_unload(sc->mbuf_dma_tag,
		  	sc->rxring_m_dmamap[sc->rxring_tl_ptr]);
		bus_dmamap_destroy(sc->mbuf_dma_tag,
				   sc->rxring_m_dmamap[sc->rxring_tl_ptr]);
		sc->rxring_m_dmamap[sc->rxring_tl_ptr] = NULL;

		/* Increment tail pointer. */
		if (++sc->rxring_tl_ptr == CGEM_NUM_RX_DESCS)
			sc->rxring_tl_ptr = 0;
		sc->rxring_queued--;

		/* Check FCS and make sure entire packet landed in one mbuf
		 * cluster (which is much bigger than the largest ethernet
		 * packet).
		 */
		if ((ctl & CGEM_RXDESC_BAD_FCS) != 0 ||
		    (ctl & (CGEM_RXDESC_SOF | CGEM_RXDESC_EOF)) !=
		           (CGEM_RXDESC_SOF | CGEM_RXDESC_EOF)) {
			/* discard. */
			m_free(m);
			if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
			continue;
		}

		/* Ready it to hand off to upper layers. */
		m->m_data += ETHER_ALIGN;
		m->m_len = (ctl & CGEM_RXDESC_LENGTH_MASK);
		m->m_pkthdr.rcvif = ifp;
		m->m_pkthdr.len = m->m_len;

		/* Are we using hardware checksumming?  Check the
		 * status in the receive descriptor.
		 */
		if ((if_getcapenable(ifp) & IFCAP_RXCSUM) != 0) {
			/* TCP or UDP checks out, IP checks out too. */
			if ((ctl & CGEM_RXDESC_CKSUM_STAT_MASK) ==
			    CGEM_RXDESC_CKSUM_STAT_TCP_GOOD ||
			    (ctl & CGEM_RXDESC_CKSUM_STAT_MASK) ==
			    CGEM_RXDESC_CKSUM_STAT_UDP_GOOD) {
				m->m_pkthdr.csum_flags |=
					CSUM_IP_CHECKED | CSUM_IP_VALID |
					CSUM_DATA_VALID | CSUM_PSEUDO_HDR;
				m->m_pkthdr.csum_data = 0xffff;
			} else if ((ctl & CGEM_RXDESC_CKSUM_STAT_MASK) ==
				   CGEM_RXDESC_CKSUM_STAT_IP_GOOD) {
				/* Only IP checks out. */
				m->m_pkthdr.csum_flags |=
					CSUM_IP_CHECKED | CSUM_IP_VALID;
				m->m_pkthdr.csum_data = 0xffff;
			}
		}

		/* Queue it up for delivery below. */
		*m_tl = m;
		m_tl = &m->m_next;
	}

	/* Replenish receive buffers. */
	cgem_fill_rqueue(sc);

	/* Unlock and send up packets. */
	CGEM_UNLOCK(sc);
	while (m_hd != NULL) {
		m = m_hd;
		m_hd = m_hd->m_next;
		m->m_next = NULL;
		if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);
		if_input(ifp, m);
	}
	CGEM_LOCK(sc);
}