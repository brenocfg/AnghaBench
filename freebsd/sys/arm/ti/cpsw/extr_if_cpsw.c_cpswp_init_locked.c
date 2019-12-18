#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct ifnet {int if_drv_flags; } ;
struct cpswp_softc {int unit; int vlan; int /*<<< orphan*/  mii_callout; int /*<<< orphan*/  mii; TYPE_3__* swsc; int /*<<< orphan*/  init_uptime; struct ifnet* ifp; } ;
struct TYPE_13__ {int vid; } ;
struct TYPE_11__ {int /*<<< orphan*/  running; } ;
struct TYPE_10__ {int /*<<< orphan*/  running; } ;
struct TYPE_12__ {scalar_t__ dualemac; TYPE_2__ tx; TYPE_1__ rx; } ;

/* Variables and functions */
 int ALE_PORTCTL_FORWARD ; 
 int ALE_PORTCTL_INGRESS ; 
 int /*<<< orphan*/  CPSW_ALE_PORTCTL (int) ; 
 int /*<<< orphan*/  CPSW_DEBUGF (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  CPSW_PORT_LOCK_ASSERT (struct cpswp_softc*) ; 
 int /*<<< orphan*/  CPSW_PORT_P_TX_PRI_MAP (int) ; 
 int /*<<< orphan*/  CPSW_PORT_P_VLAN (int) ; 
 int /*<<< orphan*/  CPSW_SL_MACCONTROL (int) ; 
 int CPSW_SL_MACTL_GMII_ENABLE ; 
 int /*<<< orphan*/  CPSW_SL_RX_MAXLEN (int) ; 
 int /*<<< orphan*/  CPSW_SL_RX_PRI_MAP (int) ; 
 int CPSW_VLANS ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cpswp_softc*) ; 
 int /*<<< orphan*/  cpsw_ale_update_vlan_table (TYPE_3__*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_init (TYPE_3__*) ; 
 int cpsw_read_4 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_reset (TYPE_3__*) ; 
 TYPE_4__* cpsw_vgroups ; 
 int /*<<< orphan*/  cpsw_write_4 (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpswp_ale_update_addresses (struct cpswp_softc*,int) ; 
 int /*<<< orphan*/  cpswp_tick ; 
 int /*<<< orphan*/  getbinuptime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_mediachg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cpswp_init_locked(void *arg)
{
#ifdef CPSW_ETHERSWITCH
	int i;
#endif
	struct cpswp_softc *sc = arg;
	struct ifnet *ifp;
	uint32_t reg;

	CPSW_DEBUGF(sc->swsc, (""));
	CPSW_PORT_LOCK_ASSERT(sc);
	ifp = sc->ifp;
	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
		return;

	getbinuptime(&sc->init_uptime);

	if (!sc->swsc->rx.running && !sc->swsc->tx.running) {
		/* Reset the controller. */
		cpsw_reset(sc->swsc);
		cpsw_init(sc->swsc);
	}

	/* Set Slave Mapping. */
	cpsw_write_4(sc->swsc, CPSW_SL_RX_PRI_MAP(sc->unit), 0x76543210);
	cpsw_write_4(sc->swsc, CPSW_PORT_P_TX_PRI_MAP(sc->unit + 1),
	    0x33221100);
	cpsw_write_4(sc->swsc, CPSW_SL_RX_MAXLEN(sc->unit), 0x5f2);
	/* Enable MAC RX/TX modules. */
	/* TODO: Docs claim that IFCTL_B and IFCTL_A do the same thing? */
	/* Huh?  Docs call bit 0 "Loopback" some places, "FullDuplex" others. */
	reg = cpsw_read_4(sc->swsc, CPSW_SL_MACCONTROL(sc->unit));
	reg |= CPSW_SL_MACTL_GMII_ENABLE;
	cpsw_write_4(sc->swsc, CPSW_SL_MACCONTROL(sc->unit), reg);

	/* Initialize ALE: set port to forwarding, initialize addrs */
	cpsw_write_4(sc->swsc, CPSW_ALE_PORTCTL(sc->unit + 1),
	    ALE_PORTCTL_INGRESS | ALE_PORTCTL_FORWARD);
	cpswp_ale_update_addresses(sc, 1);

	if (sc->swsc->dualemac) {
		/* Set Port VID. */
		cpsw_write_4(sc->swsc, CPSW_PORT_P_VLAN(sc->unit + 1),
		    sc->vlan & 0xfff);
		cpsw_ale_update_vlan_table(sc->swsc, sc->vlan,
		    (1 << (sc->unit + 1)) | (1 << 0), /* Member list */
		    (1 << (sc->unit + 1)) | (1 << 0), /* Untagged egress */
		    (1 << (sc->unit + 1)) | (1 << 0), 0); /* mcast reg flood */
#ifdef CPSW_ETHERSWITCH
		for (i = 0; i < CPSW_VLANS; i++) {
			if (cpsw_vgroups[i].vid != -1)
				continue;
			cpsw_vgroups[i].vid = sc->vlan;
			break;
		}
#endif
	}

	mii_mediachg(sc->mii);
	callout_reset(&sc->mii_callout, hz, cpswp_tick, sc);
	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
}