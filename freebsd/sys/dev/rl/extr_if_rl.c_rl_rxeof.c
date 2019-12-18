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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/ * rl_rx_buf; int /*<<< orphan*/  rl_rx_dmamap; int /*<<< orphan*/  rl_rx_tag; } ;
struct rl_softc {scalar_t__ rxcycles; TYPE_1__ rl_cdata; struct ifnet* rl_ifp; } ;
struct mbuf {int dummy; } ;
struct ifnet {int if_capenable; int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int CSR_READ_1 (struct rl_softc*,int /*<<< orphan*/ ) ; 
 int CSR_READ_2 (struct rl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct rl_softc*,int /*<<< orphan*/ ,int) ; 
 int ETHER_CRC_LEN ; 
 int ETHER_MAX_LEN ; 
 int ETHER_MIN_LEN ; 
 int ETHER_VLAN_ENCAP_LEN ; 
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_IQDROPS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int RL_CMD_EMPTY_RXBUF ; 
 int /*<<< orphan*/  RL_COMMAND ; 
 int /*<<< orphan*/  RL_CURRXADDR ; 
 int /*<<< orphan*/  RL_CURRXBUF ; 
 int /*<<< orphan*/  RL_ETHER_ALIGN ; 
 int /*<<< orphan*/  RL_LOCK (struct rl_softc*) ; 
 int /*<<< orphan*/  RL_LOCK_ASSERT (struct rl_softc*) ; 
 int RL_RXBUFLEN ; 
 int RL_RXSTAT_RXOK ; 
 int RL_RXSTAT_UNFINISHED ; 
 int /*<<< orphan*/  RL_UNLOCK (struct rl_softc*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int le32toh (int) ; 
 int /*<<< orphan*/  m_copyback (struct mbuf*,int,int,int /*<<< orphan*/ *) ; 
 struct mbuf* m_devget (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rl_init_locked (struct rl_softc*) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static int
rl_rxeof(struct rl_softc *sc)
{
	struct mbuf		*m;
	struct ifnet		*ifp = sc->rl_ifp;
	uint8_t			*rxbufpos;
	int			total_len = 0;
	int			wrap = 0;
	int			rx_npkts = 0;
	uint32_t		rxstat;
	uint16_t		cur_rx;
	uint16_t		limit;
	uint16_t		max_bytes, rx_bytes = 0;

	RL_LOCK_ASSERT(sc);

	bus_dmamap_sync(sc->rl_cdata.rl_rx_tag, sc->rl_cdata.rl_rx_dmamap,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

	cur_rx = (CSR_READ_2(sc, RL_CURRXADDR) + 16) % RL_RXBUFLEN;

	/* Do not try to read past this point. */
	limit = CSR_READ_2(sc, RL_CURRXBUF) % RL_RXBUFLEN;

	if (limit < cur_rx)
		max_bytes = (RL_RXBUFLEN - cur_rx) + limit;
	else
		max_bytes = limit - cur_rx;

	while((CSR_READ_1(sc, RL_COMMAND) & RL_CMD_EMPTY_RXBUF) == 0) {
#ifdef DEVICE_POLLING
		if (ifp->if_capenable & IFCAP_POLLING) {
			if (sc->rxcycles <= 0)
				break;
			sc->rxcycles--;
		}
#endif
		rxbufpos = sc->rl_cdata.rl_rx_buf + cur_rx;
		rxstat = le32toh(*(uint32_t *)rxbufpos);

		/*
		 * Here's a totally undocumented fact for you. When the
		 * RealTek chip is in the process of copying a packet into
		 * RAM for you, the length will be 0xfff0. If you spot a
		 * packet header with this value, you need to stop. The
		 * datasheet makes absolutely no mention of this and
		 * RealTek should be shot for this.
		 */
		total_len = rxstat >> 16;
		if (total_len == RL_RXSTAT_UNFINISHED)
			break;

		if (!(rxstat & RL_RXSTAT_RXOK) ||
		    total_len < ETHER_MIN_LEN ||
		    total_len > ETHER_MAX_LEN + ETHER_VLAN_ENCAP_LEN) {
			if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
			ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
			rl_init_locked(sc);
			return (rx_npkts);
		}

		/* No errors; receive the packet. */
		rx_bytes += total_len + 4;

		/*
		 * XXX The RealTek chip includes the CRC with every
		 * received frame, and there's no way to turn this
		 * behavior off (at least, I can't find anything in
		 * the manual that explains how to do it) so we have
		 * to trim off the CRC manually.
		 */
		total_len -= ETHER_CRC_LEN;

		/*
		 * Avoid trying to read more bytes than we know
		 * the chip has prepared for us.
		 */
		if (rx_bytes > max_bytes)
			break;

		rxbufpos = sc->rl_cdata.rl_rx_buf +
			((cur_rx + sizeof(uint32_t)) % RL_RXBUFLEN);
		if (rxbufpos == (sc->rl_cdata.rl_rx_buf + RL_RXBUFLEN))
			rxbufpos = sc->rl_cdata.rl_rx_buf;

		wrap = (sc->rl_cdata.rl_rx_buf + RL_RXBUFLEN) - rxbufpos;
		if (total_len > wrap) {
			m = m_devget(rxbufpos, total_len, RL_ETHER_ALIGN, ifp,
			    NULL);
			if (m != NULL)
				m_copyback(m, wrap, total_len - wrap,
					sc->rl_cdata.rl_rx_buf);
			cur_rx = (total_len - wrap + ETHER_CRC_LEN);
		} else {
			m = m_devget(rxbufpos, total_len, RL_ETHER_ALIGN, ifp,
			    NULL);
			cur_rx += total_len + 4 + ETHER_CRC_LEN;
		}

		/* Round up to 32-bit boundary. */
		cur_rx = (cur_rx + 3) & ~3;
		CSR_WRITE_2(sc, RL_CURRXADDR, cur_rx - 16);

		if (m == NULL) {
			if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
			continue;
		}

		if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);
		RL_UNLOCK(sc);
		(*ifp->if_input)(ifp, m);
		RL_LOCK(sc);
		rx_npkts++;
	}

	/* No need to sync Rx memory block as we didn't modify it. */
	return (rx_npkts);
}