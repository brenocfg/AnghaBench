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
typedef  size_t uint32_t ;
typedef  int uint16_t ;
struct tsec_softc {int /*<<< orphan*/  tsec_rx_dmap; int /*<<< orphan*/  tsec_rx_dtag; scalar_t__ is_etsec; int /*<<< orphan*/  tsec_rx_mtag; struct mbuf* frame; struct rx_data_type* rx_data; struct ifnet* tsec_ifp; } ;
struct tsec_desc {int flags; scalar_t__ length; int /*<<< orphan*/  bufptr; } ;
struct rx_data_type {int /*<<< orphan*/  paddr; struct mbuf* mbuf; int /*<<< orphan*/  map; } ;
struct TYPE_2__ {struct ifnet* rcvif; } ;
struct mbuf {TYPE_1__ m_pkthdr; int /*<<< orphan*/  m_flags; scalar_t__ m_len; } ;
struct ifnet {int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  ETHER_CRC_LEN ; 
 int /*<<< orphan*/  IFCOUNTER_IQDROPS ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  TSEC_BACK_CUR_RX_DESC (struct tsec_softc*) ; 
 struct tsec_desc* TSEC_GET_CUR_RX_DESC (struct tsec_softc*) ; 
 size_t TSEC_GET_CUR_RX_DESC_CNT (struct tsec_softc*) ; 
 int TSEC_IEVENT_RXB ; 
 int TSEC_IEVENT_RXF ; 
 int /*<<< orphan*/  TSEC_RECEIVE_LOCK (struct tsec_softc*) ; 
 int /*<<< orphan*/  TSEC_RECEIVE_LOCK_ASSERT (struct tsec_softc*) ; 
 int /*<<< orphan*/  TSEC_RECEIVE_UNLOCK (struct tsec_softc*) ; 
 int /*<<< orphan*/  TSEC_REG_IEVENT ; 
 int /*<<< orphan*/  TSEC_REG_RSTAT ; 
 int TSEC_RSTAT_QHLT ; 
 int TSEC_RXBD_CR ; 
 int TSEC_RXBD_E ; 
 int TSEC_RXBD_I ; 
 int TSEC_RXBD_L ; 
 int TSEC_RXBD_LG ; 
 int TSEC_RXBD_NO ; 
 int TSEC_RXBD_OV ; 
 int TSEC_RXBD_SH ; 
 int TSEC_RXBD_TR ; 
 int TSEC_RXBD_ZEROONINIT ; 
 int TSEC_RX_NUM_DESC ; 
 int /*<<< orphan*/  TSEC_WRITE (struct tsec_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_cat (struct mbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  m_fixhdr (struct mbuf*) ; 
 int /*<<< orphan*/  m_free (struct mbuf*) ; 
 scalar_t__ m_length (struct mbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 
 scalar_t__ tsec_new_rxbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsec_offload_process_frame (struct tsec_softc*,struct mbuf*) ; 

__attribute__((used)) static int
tsec_receive_intr_locked(struct tsec_softc *sc, int count)
{
	struct tsec_desc *rx_desc;
	struct ifnet *ifp;
	struct rx_data_type *rx_data;
	struct mbuf *m;
	uint32_t i;
	int c, rx_npkts;
	uint16_t flags;

	TSEC_RECEIVE_LOCK_ASSERT(sc);

	ifp = sc->tsec_ifp;
	rx_data = sc->rx_data;
	rx_npkts = 0;

	bus_dmamap_sync(sc->tsec_rx_dtag, sc->tsec_rx_dmap,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

	for (c = 0; ; c++) {
		if (count >= 0 && count-- == 0)
			break;

		rx_desc = TSEC_GET_CUR_RX_DESC(sc);
		flags = rx_desc->flags;

		/* Check if there is anything to receive */
		if ((flags & TSEC_RXBD_E) || (c >= TSEC_RX_NUM_DESC)) {
			/*
			 * Avoid generating another interrupt
			 */
			if (flags & TSEC_RXBD_E)
				TSEC_WRITE(sc, TSEC_REG_IEVENT,
				    TSEC_IEVENT_RXB | TSEC_IEVENT_RXF);
			/*
			 * We didn't consume current descriptor and have to
			 * return it to the queue
			 */
			TSEC_BACK_CUR_RX_DESC(sc);
			break;
		}

		if (flags & (TSEC_RXBD_LG | TSEC_RXBD_SH | TSEC_RXBD_NO |
		    TSEC_RXBD_CR | TSEC_RXBD_OV | TSEC_RXBD_TR)) {

			rx_desc->length = 0;
			rx_desc->flags = (rx_desc->flags &
			    ~TSEC_RXBD_ZEROONINIT) | TSEC_RXBD_E | TSEC_RXBD_I;

			if (sc->frame != NULL) {
				m_free(sc->frame);
				sc->frame = NULL;
			}

			continue;
		}

		/* Ok... process frame */
		i = TSEC_GET_CUR_RX_DESC_CNT(sc);
		m = rx_data[i].mbuf;
		m->m_len = rx_desc->length;

		if (sc->frame != NULL) {
			if ((flags & TSEC_RXBD_L) != 0)
				m->m_len -= m_length(sc->frame, NULL);

			m->m_flags &= ~M_PKTHDR;
			m_cat(sc->frame, m);
		} else {
			sc->frame = m;
		}

		m = NULL;

		if ((flags & TSEC_RXBD_L) != 0) {
			m = sc->frame;
			sc->frame = NULL;
		}

		if (tsec_new_rxbuf(sc->tsec_rx_mtag, rx_data[i].map,
		    &rx_data[i].mbuf, &rx_data[i].paddr)) {
			if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
			/*
			 * We ran out of mbufs; didn't consume current
			 * descriptor and have to return it to the queue.
			 */
			TSEC_BACK_CUR_RX_DESC(sc);
			break;
		}

		/* Attach new buffer to descriptor and clear flags */
		rx_desc->bufptr = rx_data[i].paddr;
		rx_desc->length = 0;
		rx_desc->flags = (rx_desc->flags & ~TSEC_RXBD_ZEROONINIT) |
		    TSEC_RXBD_E | TSEC_RXBD_I;

		if (m != NULL) {
			m->m_pkthdr.rcvif = ifp;

			m_fixhdr(m);
			m_adj(m, -ETHER_CRC_LEN);

			if (sc->is_etsec)
				tsec_offload_process_frame(sc, m);

			TSEC_RECEIVE_UNLOCK(sc);
			(*ifp->if_input)(ifp, m);
			TSEC_RECEIVE_LOCK(sc);
			rx_npkts++;
		}
	}

	bus_dmamap_sync(sc->tsec_rx_dtag, sc->tsec_rx_dmap,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	/*
	 * Make sure TSEC receiver is not halted.
	 *
	 * Various conditions can stop the TSEC receiver, but not all are
	 * signaled and handled by error interrupt, so make sure the receiver
	 * is running. Writing to TSEC_REG_RSTAT restarts the receiver when
	 * halted, and is harmless if already running.
	 */
	TSEC_WRITE(sc, TSEC_REG_RSTAT, TSEC_RSTAT_QHLT);
	return (rx_npkts);
}