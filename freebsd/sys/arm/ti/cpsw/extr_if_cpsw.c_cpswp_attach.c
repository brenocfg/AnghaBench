#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_capabilities; int if_capenable; TYPE_4__ if_snd; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_init; struct cpswp_softc* if_softc; } ;
struct cpswp_softc {size_t unit; int phy; int vlan; int /*<<< orphan*/  mii_callout; struct ifnet* ifp; int /*<<< orphan*/  physel; TYPE_3__* swsc; int /*<<< orphan*/  miibus; void* mii; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  phyaccess; int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_7__ {int /*<<< orphan*/  queue_slots; } ;
struct TYPE_8__ {TYPE_2__ tx; scalar_t__ dualemac; TYPE_1__* port; } ;
struct TYPE_6__ {int phy; int vlan; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int ENXIO ; 
 int ETHER_ADDR_LEN ; 
 int IFCAP_HWCSUM ; 
 int IFCAP_VLAN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_4__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  MDIOUSERACCESS0 ; 
 int /*<<< orphan*/  MDIOUSERACCESS1 ; 
 int /*<<< orphan*/  MDIOUSERPHYSEL0 ; 
 int /*<<< orphan*/  MDIOUSERPHYSEL1 ; 
 int MDIO_PHYSEL_LINKINTENB ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 scalar_t__ SCM_MAC_ID0_HI ; 
 scalar_t__ SCM_MAC_ID0_LO ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_write_4 (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpswp_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpswp_ifmedia_sts ; 
 int /*<<< orphan*/  cpswp_ifmedia_upd ; 
 int /*<<< orphan*/  cpswp_init ; 
 int /*<<< orphan*/  cpswp_ioctl ; 
 int /*<<< orphan*/  cpswp_start ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 size_t device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int*) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_scm_reg_read_4 (scalar_t__,int*) ; 

__attribute__((used)) static int
cpswp_attach(device_t dev)
{
	int error;
	struct ifnet *ifp;
	struct cpswp_softc *sc;
	uint32_t reg;
	uint8_t mac_addr[ETHER_ADDR_LEN];

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->pdev = device_get_parent(dev);
	sc->swsc = device_get_softc(sc->pdev);
	sc->unit = device_get_unit(dev);
	sc->phy = sc->swsc->port[sc->unit].phy;
	sc->vlan = sc->swsc->port[sc->unit].vlan;
	if (sc->swsc->dualemac && sc->vlan == -1)
		sc->vlan = sc->unit + 1;

	if (sc->unit == 0) {
		sc->physel = MDIOUSERPHYSEL0;
		sc->phyaccess = MDIOUSERACCESS0;
	} else {
		sc->physel = MDIOUSERPHYSEL1;
		sc->phyaccess = MDIOUSERACCESS1;
	}

	mtx_init(&sc->lock, device_get_nameunit(dev), "cpsw port lock",
	    MTX_DEF);

	/* Allocate network interface */
	ifp = sc->ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		cpswp_detach(dev);
		return (ENXIO);
	}

	if_initname(ifp, device_get_name(sc->dev), sc->unit);
	ifp->if_softc = sc;
	ifp->if_flags = IFF_SIMPLEX | IFF_MULTICAST | IFF_BROADCAST;
	ifp->if_capabilities = IFCAP_VLAN_MTU | IFCAP_HWCSUM; //FIXME VLAN?
	ifp->if_capenable = ifp->if_capabilities;

	ifp->if_init = cpswp_init;
	ifp->if_start = cpswp_start;
	ifp->if_ioctl = cpswp_ioctl;

	ifp->if_snd.ifq_drv_maxlen = sc->swsc->tx.queue_slots;
	IFQ_SET_MAXLEN(&ifp->if_snd, ifp->if_snd.ifq_drv_maxlen);
	IFQ_SET_READY(&ifp->if_snd);

	/* Get high part of MAC address from control module (mac_id[0|1]_hi) */
	ti_scm_reg_read_4(SCM_MAC_ID0_HI + sc->unit * 8, &reg);
	mac_addr[0] = reg & 0xFF;
	mac_addr[1] = (reg >>  8) & 0xFF;
	mac_addr[2] = (reg >> 16) & 0xFF;
	mac_addr[3] = (reg >> 24) & 0xFF;

	/* Get low part of MAC address from control module (mac_id[0|1]_lo) */
	ti_scm_reg_read_4(SCM_MAC_ID0_LO + sc->unit * 8, &reg);
	mac_addr[4] = reg & 0xFF;
	mac_addr[5] = (reg >>  8) & 0xFF;

	error = mii_attach(dev, &sc->miibus, ifp, cpswp_ifmedia_upd,
	    cpswp_ifmedia_sts, BMSR_DEFCAPMASK, sc->phy, MII_OFFSET_ANY, 0);
	if (error) {
		device_printf(dev, "attaching PHYs failed\n");
		cpswp_detach(dev);
		return (error);
	}
	sc->mii = device_get_softc(sc->miibus);

	/* Select PHY and enable interrupts */
	cpsw_write_4(sc->swsc, sc->physel,
	    MDIO_PHYSEL_LINKINTENB | (sc->phy & 0x1F));

	ether_ifattach(sc->ifp, mac_addr);
	callout_init(&sc->mii_callout, 0);

	return (0);
}