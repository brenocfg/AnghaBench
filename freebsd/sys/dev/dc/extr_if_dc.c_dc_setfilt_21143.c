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
typedef  int /*<<< orphan*/  uint16_t ;
struct mbuf {int dummy; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_broadcastaddr; } ;
struct TYPE_4__ {int dc_tx_prod; int* dc_sbuf; struct mbuf** dc_tx_chain; int /*<<< orphan*/  dc_tx_cnt; } ;
struct TYPE_3__ {struct dc_desc* dc_tx_list; } ;
struct dc_softc {int dc_wdog_timer; int /*<<< orphan*/  dc_smap; int /*<<< orphan*/  dc_stag; int /*<<< orphan*/  dc_tx_lmap; int /*<<< orphan*/  dc_tx_ltag; struct ifnet* dc_ifp; TYPE_2__ dc_cdata; int /*<<< orphan*/  dc_saddr; TYPE_1__ dc_ldata; } ;
struct dc_desc {int dc_data; int dc_ctl; int dc_status; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct dc_softc*,int /*<<< orphan*/ ,int) ; 
 int DC_ADDR_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_CLRBIT (struct dc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DC_FILTER_HASHPERF ; 
 int /*<<< orphan*/  DC_INC (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_NETCFG ; 
 int /*<<< orphan*/  DC_NETCFG_RX_ALLMULTI ; 
 int /*<<< orphan*/  DC_NETCFG_RX_PROMISC ; 
 int /*<<< orphan*/  DC_SETBIT (struct dc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DC_SFRAME_LEN ; 
 int DC_SP_MAC (int /*<<< orphan*/ ) ; 
 int DC_TXCTL_FINT ; 
 int DC_TXCTL_SETUP ; 
 int DC_TXCTL_TLINK ; 
 int /*<<< orphan*/  DC_TXSTART ; 
 int DC_TXSTAT_OWN ; 
 int /*<<< orphan*/  DC_TX_LIST_CNT ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int IFF_ALLMULTI ; 
 int IFF_BROADCAST ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 int /*<<< orphan*/  dc_hash_maddr_21143 ; 
 int dc_mchash_le (struct dc_softc*,int /*<<< orphan*/ ) ; 
 int htole32 (int) ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
dc_setfilt_21143(struct dc_softc *sc)
{
	uint16_t eaddr[(ETHER_ADDR_LEN+1)/2];
	struct dc_desc *sframe;
	uint32_t h, *sp;
	struct ifnet *ifp;
	int i;

	ifp = sc->dc_ifp;

	i = sc->dc_cdata.dc_tx_prod;
	DC_INC(sc->dc_cdata.dc_tx_prod, DC_TX_LIST_CNT);
	sc->dc_cdata.dc_tx_cnt++;
	sframe = &sc->dc_ldata.dc_tx_list[i];
	sp = sc->dc_cdata.dc_sbuf;
	bzero(sp, DC_SFRAME_LEN);

	sframe->dc_data = htole32(DC_ADDR_LO(sc->dc_saddr));
	sframe->dc_ctl = htole32(DC_SFRAME_LEN | DC_TXCTL_SETUP |
	    DC_TXCTL_TLINK | DC_FILTER_HASHPERF | DC_TXCTL_FINT);

	sc->dc_cdata.dc_tx_chain[i] = (struct mbuf *)sc->dc_cdata.dc_sbuf;

	/* If we want promiscuous mode, set the allframes bit. */
	if (ifp->if_flags & IFF_PROMISC)
		DC_SETBIT(sc, DC_NETCFG, DC_NETCFG_RX_PROMISC);
	else
		DC_CLRBIT(sc, DC_NETCFG, DC_NETCFG_RX_PROMISC);

	if (ifp->if_flags & IFF_ALLMULTI)
		DC_SETBIT(sc, DC_NETCFG, DC_NETCFG_RX_ALLMULTI);
	else
		DC_CLRBIT(sc, DC_NETCFG, DC_NETCFG_RX_ALLMULTI);

	if_foreach_llmaddr(ifp, dc_hash_maddr_21143, sp);

	if (ifp->if_flags & IFF_BROADCAST) {
		h = dc_mchash_le(sc, ifp->if_broadcastaddr);
		sp[h >> 4] |= htole32(1 << (h & 0xF));
	}

	/* Set our MAC address. */
	bcopy(IF_LLADDR(sc->dc_ifp), eaddr, ETHER_ADDR_LEN);
	sp[39] = DC_SP_MAC(eaddr[0]);
	sp[40] = DC_SP_MAC(eaddr[1]);
	sp[41] = DC_SP_MAC(eaddr[2]);

	sframe->dc_status = htole32(DC_TXSTAT_OWN);
	bus_dmamap_sync(sc->dc_tx_ltag, sc->dc_tx_lmap, BUS_DMASYNC_PREREAD |
	    BUS_DMASYNC_PREWRITE);
	bus_dmamap_sync(sc->dc_stag, sc->dc_smap, BUS_DMASYNC_PREWRITE);
	CSR_WRITE_4(sc, DC_TXSTART, 0xFFFFFFFF);

	/*
	 * The PNIC takes an exceedingly long time to process its
	 * setup frame; wait 10ms after posting the setup frame
	 * before proceeding, just so it has time to swallow its
	 * medicine.
	 */
	DELAY(10000);

	sc->dc_wdog_timer = 5;
}