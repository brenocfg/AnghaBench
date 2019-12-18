#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ifnet {int if_drv_flags; int if_flags; } ;
struct TYPE_6__ {int an_rxmode; int an_len; int /*<<< orphan*/  an_type; int /*<<< orphan*/  an_macaddr; } ;
struct TYPE_5__ {int an_len; int /*<<< orphan*/  an_type; } ;
struct TYPE_4__ {int an_len; int /*<<< orphan*/  an_type; } ;
struct an_softc {int an_monitor; int /*<<< orphan*/  an_stat_ch; scalar_t__ mpi350; TYPE_3__ an_config; TYPE_2__ an_aplist; TYPE_1__ an_ssidlist; scalar_t__ an_have_rssimap; struct ifnet* an_ifp; scalar_t__ an_associated; scalar_t__ an_gone; } ;
struct an_ltv_ssidlist_new {int dummy; } ;
struct an_ltv_genconfig {int dummy; } ;
struct an_ltv_gen {int dummy; } ;
struct an_ltv_aplist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AN_CMD_ENABLE ; 
 int /*<<< orphan*/  AN_CMD_SET_MODE ; 
 int /*<<< orphan*/  AN_INTRS (scalar_t__) ; 
 int /*<<< orphan*/  AN_INT_EN (scalar_t__) ; 
 int /*<<< orphan*/  AN_LOCK_ASSERT (struct an_softc*) ; 
 int AN_MONITOR ; 
 int AN_MONITOR_ANY_BSS ; 
 int /*<<< orphan*/  AN_RID_APLIST ; 
 int /*<<< orphan*/  AN_RID_GENCONFIG ; 
 int /*<<< orphan*/  AN_RID_SSIDLIST ; 
 int AN_RXMODE_80211_MONITOR_ANYBSS ; 
 int AN_RXMODE_80211_MONITOR_CURBSS ; 
 int AN_RXMODE_ADDR ; 
 int AN_RXMODE_BC_ADDR ; 
 int AN_RXMODE_BC_MC_ADDR ; 
 int AN_RXMODE_NORMALIZED_RSSI ; 
 int AN_RXMODE_NO_8023_HEADER ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct an_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int IFF_BROADCAST ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int IFF_MULTICAST ; 
 int IFF_PROMISC ; 
 scalar_t__ IF_LLADDR (struct ifnet*) ; 
 scalar_t__ an_cmd (struct an_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  an_init_mpi350_desc (struct an_softc*) ; 
 scalar_t__ an_init_tx_ring (struct an_softc*) ; 
 int /*<<< orphan*/  an_reset (struct an_softc*) ; 
 int /*<<< orphan*/  an_stats_update ; 
 int /*<<< orphan*/  an_stop (struct an_softc*) ; 
 scalar_t__ an_write_record (struct an_softc*,struct an_ltv_gen*) ; 
 int /*<<< orphan*/  bcopy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct an_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 

__attribute__((used)) static void
an_init_locked(struct an_softc *sc)
{
	struct ifnet *ifp;

	AN_LOCK_ASSERT(sc);
	ifp = sc->an_ifp;
	if (sc->an_gone)
		return;

	if (ifp->if_drv_flags & IFF_DRV_RUNNING)
		an_stop(sc);

	sc->an_associated = 0;

	/* Allocate the TX buffers */
	if (an_init_tx_ring(sc)) {
		an_reset(sc);
		if (sc->mpi350)
			an_init_mpi350_desc(sc);
		if (an_init_tx_ring(sc)) {
			if_printf(ifp, "tx buffer allocation failed\n");
			return;
		}
	}

	/* Set our MAC address. */
	bcopy((char *)IF_LLADDR(sc->an_ifp),
	    (char *)&sc->an_config.an_macaddr, ETHER_ADDR_LEN);

	if (ifp->if_flags & IFF_BROADCAST)
		sc->an_config.an_rxmode = AN_RXMODE_BC_ADDR;
	else
		sc->an_config.an_rxmode = AN_RXMODE_ADDR;

	if (ifp->if_flags & IFF_MULTICAST)
		sc->an_config.an_rxmode = AN_RXMODE_BC_MC_ADDR;

	if (ifp->if_flags & IFF_PROMISC) {
		if (sc->an_monitor & AN_MONITOR) {
			if (sc->an_monitor & AN_MONITOR_ANY_BSS) {
				sc->an_config.an_rxmode |=
				    AN_RXMODE_80211_MONITOR_ANYBSS |
				    AN_RXMODE_NO_8023_HEADER;
			} else {
				sc->an_config.an_rxmode |=
				    AN_RXMODE_80211_MONITOR_CURBSS |
				    AN_RXMODE_NO_8023_HEADER;
			}
		}
	}

#ifdef ANCACHE
	if (sc->an_have_rssimap)
		sc->an_config.an_rxmode |= AN_RXMODE_NORMALIZED_RSSI;
#endif

	/* Set the ssid list */
	sc->an_ssidlist.an_type = AN_RID_SSIDLIST;
	sc->an_ssidlist.an_len = sizeof(struct an_ltv_ssidlist_new);
	if (an_write_record(sc, (struct an_ltv_gen *)&sc->an_ssidlist)) {
		if_printf(ifp, "failed to set ssid list\n");
		return;
	}

	/* Set the AP list */
	sc->an_aplist.an_type = AN_RID_APLIST;
	sc->an_aplist.an_len = sizeof(struct an_ltv_aplist);
	if (an_write_record(sc, (struct an_ltv_gen *)&sc->an_aplist)) {
		if_printf(ifp, "failed to set AP list\n");
		return;
	}

	/* Set the configuration in the NIC */
	sc->an_config.an_len = sizeof(struct an_ltv_genconfig);
	sc->an_config.an_type = AN_RID_GENCONFIG;
	if (an_write_record(sc, (struct an_ltv_gen *)&sc->an_config)) {
		if_printf(ifp, "failed to set configuration\n");
		return;
	}

	/* Enable the MAC */
	if (an_cmd(sc, AN_CMD_ENABLE, 0)) {
		if_printf(ifp, "failed to enable MAC\n");
		return;
	}

	if (ifp->if_flags & IFF_PROMISC)
		an_cmd(sc, AN_CMD_SET_MODE, 0xffff);

	/* enable interrupts */
	CSR_WRITE_2(sc, AN_INT_EN(sc->mpi350), AN_INTRS(sc->mpi350));

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	callout_reset(&sc->an_stat_ch, hz, an_stats_update, sc);

	return;
}