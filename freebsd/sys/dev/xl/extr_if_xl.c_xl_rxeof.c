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
typedef  int u_int32_t ;
struct TYPE_8__ {struct xl_chain_onefrag* xl_rx_chain; struct xl_chain_onefrag* xl_rx_head; } ;
struct TYPE_7__ {int /*<<< orphan*/  xl_rx_dmaaddr; int /*<<< orphan*/  xl_rx_dmamap; int /*<<< orphan*/  xl_rx_tag; } ;
struct xl_softc {scalar_t__ rxcycles; TYPE_4__ xl_cdata; TYPE_3__ xl_ldata; int /*<<< orphan*/  xl_mtag; int /*<<< orphan*/  xl_dev; struct ifnet* xl_ifp; } ;
struct xl_chain_onefrag {TYPE_1__* xl_ptr; struct mbuf* xl_mbuf; int /*<<< orphan*/  xl_map; struct xl_chain_onefrag* xl_next; } ;
struct TYPE_6__ {int len; int csum_flags; int csum_data; struct ifnet* rcvif; } ;
struct mbuf {int m_len; TYPE_2__ m_pkthdr; } ;
struct ifnet {int if_capenable; int if_drv_flags; int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;
struct TYPE_5__ {scalar_t__ xl_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int CSR_READ_4 (struct xl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct xl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct xl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CSUM_DATA_VALID ; 
 int CSUM_IP_CHECKED ; 
 int CSUM_IP_VALID ; 
 int CSUM_PSEUDO_HDR ; 
 int IFCAP_POLLING ; 
 int IFCAP_RXCSUM ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  XL_CMD_UP_STALL ; 
 int /*<<< orphan*/  XL_CMD_UP_UNSTALL ; 
 int /*<<< orphan*/  XL_COMMAND ; 
 int /*<<< orphan*/  XL_LOCK (struct xl_softc*) ; 
 int /*<<< orphan*/  XL_LOCK_ASSERT (struct xl_softc*) ; 
 int XL_MAX_FRAMELEN ; 
 int XL_PKTSTAT_UP_STALLED ; 
 int XL_RXSTAT_IPCKERR ; 
 int XL_RXSTAT_IPCKOK ; 
 int XL_RXSTAT_LENMASK ; 
 int XL_RXSTAT_OVERSIZE ; 
 int XL_RXSTAT_TCPCKERR ; 
 int XL_RXSTAT_TCPCOK ; 
 int XL_RXSTAT_UDPCKERR ; 
 int XL_RXSTAT_UDPCKOK ; 
 int XL_RXSTAT_UP_CMPLT ; 
 int XL_RXSTAT_UP_ERROR ; 
 int /*<<< orphan*/  XL_UNLOCK (struct xl_softc*) ; 
 int /*<<< orphan*/  XL_UPLIST_PTR ; 
 int /*<<< orphan*/  XL_UPLIST_STATUS ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int le32toh (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 
 scalar_t__ xl_newbuf (struct xl_softc*,struct xl_chain_onefrag*) ; 
 int /*<<< orphan*/  xl_wait (struct xl_softc*) ; 

__attribute__((used)) static int
xl_rxeof(struct xl_softc *sc)
{
	struct mbuf		*m;
	struct ifnet		*ifp = sc->xl_ifp;
	struct xl_chain_onefrag	*cur_rx;
	int			total_len;
	int			rx_npkts = 0;
	u_int32_t		rxstat;

	XL_LOCK_ASSERT(sc);
again:
	bus_dmamap_sync(sc->xl_ldata.xl_rx_tag, sc->xl_ldata.xl_rx_dmamap,
	    BUS_DMASYNC_POSTREAD);
	while ((rxstat = le32toh(sc->xl_cdata.xl_rx_head->xl_ptr->xl_status))) {
#ifdef DEVICE_POLLING
		if (ifp->if_capenable & IFCAP_POLLING) {
			if (sc->rxcycles <= 0)
				break;
			sc->rxcycles--;
		}
#endif
		cur_rx = sc->xl_cdata.xl_rx_head;
		sc->xl_cdata.xl_rx_head = cur_rx->xl_next;
		total_len = rxstat & XL_RXSTAT_LENMASK;
		rx_npkts++;

		/*
		 * Since we have told the chip to allow large frames,
		 * we need to trap giant frame errors in software. We allow
		 * a little more than the normal frame size to account for
		 * frames with VLAN tags.
		 */
		if (total_len > XL_MAX_FRAMELEN)
			rxstat |= (XL_RXSTAT_UP_ERROR|XL_RXSTAT_OVERSIZE);

		/*
		 * If an error occurs, update stats, clear the
		 * status word and leave the mbuf cluster in place:
		 * it should simply get re-used next time this descriptor
		 * comes up in the ring.
		 */
		if (rxstat & XL_RXSTAT_UP_ERROR) {
			if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
			cur_rx->xl_ptr->xl_status = 0;
			bus_dmamap_sync(sc->xl_ldata.xl_rx_tag,
			    sc->xl_ldata.xl_rx_dmamap, BUS_DMASYNC_PREWRITE);
			continue;
		}

		/*
		 * If the error bit was not set, the upload complete
		 * bit should be set which means we have a valid packet.
		 * If not, something truly strange has happened.
		 */
		if (!(rxstat & XL_RXSTAT_UP_CMPLT)) {
			device_printf(sc->xl_dev,
			    "bad receive status -- packet dropped\n");
			if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
			cur_rx->xl_ptr->xl_status = 0;
			bus_dmamap_sync(sc->xl_ldata.xl_rx_tag,
			    sc->xl_ldata.xl_rx_dmamap, BUS_DMASYNC_PREWRITE);
			continue;
		}

		/* No errors; receive the packet. */
		bus_dmamap_sync(sc->xl_mtag, cur_rx->xl_map,
		    BUS_DMASYNC_POSTREAD);
		m = cur_rx->xl_mbuf;

		/*
		 * Try to conjure up a new mbuf cluster. If that
		 * fails, it means we have an out of memory condition and
		 * should leave the buffer in place and continue. This will
		 * result in a lost packet, but there's little else we
		 * can do in this situation.
		 */
		if (xl_newbuf(sc, cur_rx)) {
			if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
			cur_rx->xl_ptr->xl_status = 0;
			bus_dmamap_sync(sc->xl_ldata.xl_rx_tag,
			    sc->xl_ldata.xl_rx_dmamap, BUS_DMASYNC_PREWRITE);
			continue;
		}
		bus_dmamap_sync(sc->xl_ldata.xl_rx_tag,
		    sc->xl_ldata.xl_rx_dmamap, BUS_DMASYNC_PREWRITE);

		if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);
		m->m_pkthdr.rcvif = ifp;
		m->m_pkthdr.len = m->m_len = total_len;

		if (ifp->if_capenable & IFCAP_RXCSUM) {
			/* Do IP checksum checking. */
			if (rxstat & XL_RXSTAT_IPCKOK)
				m->m_pkthdr.csum_flags |= CSUM_IP_CHECKED;
			if (!(rxstat & XL_RXSTAT_IPCKERR))
				m->m_pkthdr.csum_flags |= CSUM_IP_VALID;
			if ((rxstat & XL_RXSTAT_TCPCOK &&
			     !(rxstat & XL_RXSTAT_TCPCKERR)) ||
			    (rxstat & XL_RXSTAT_UDPCKOK &&
			     !(rxstat & XL_RXSTAT_UDPCKERR))) {
				m->m_pkthdr.csum_flags |=
					CSUM_DATA_VALID|CSUM_PSEUDO_HDR;
				m->m_pkthdr.csum_data = 0xffff;
			}
		}

		XL_UNLOCK(sc);
		(*ifp->if_input)(ifp, m);
		XL_LOCK(sc);

		/*
		 * If we are running from the taskqueue, the interface
		 * might have been stopped while we were passing the last
		 * packet up the network stack.
		 */
		if (!(ifp->if_drv_flags & IFF_DRV_RUNNING))
			return (rx_npkts);
	}

	/*
	 * Handle the 'end of channel' condition. When the upload
	 * engine hits the end of the RX ring, it will stall. This
	 * is our cue to flush the RX ring, reload the uplist pointer
	 * register and unstall the engine.
	 * XXX This is actually a little goofy. With the ThunderLAN
	 * chip, you get an interrupt when the receiver hits the end
	 * of the receive ring, which tells you exactly when you
	 * you need to reload the ring pointer. Here we have to
	 * fake it. I'm mad at myself for not being clever enough
	 * to avoid the use of a goto here.
	 */
	if (CSR_READ_4(sc, XL_UPLIST_PTR) == 0 ||
		CSR_READ_4(sc, XL_UPLIST_STATUS) & XL_PKTSTAT_UP_STALLED) {
		CSR_WRITE_2(sc, XL_COMMAND, XL_CMD_UP_STALL);
		xl_wait(sc);
		CSR_WRITE_4(sc, XL_UPLIST_PTR, sc->xl_ldata.xl_rx_dmaaddr);
		sc->xl_cdata.xl_rx_head = &sc->xl_cdata.xl_rx_chain[0];
		CSR_WRITE_2(sc, XL_COMMAND, XL_CMD_UP_UNSTALL);
		goto again;
	}
	return (rx_npkts);
}