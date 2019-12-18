#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  tn ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct rl_type {int rl_did; scalar_t__ rl_basetype; int /*<<< orphan*/ * rl_name; } ;
struct rl_softc {int rl_twister_enable; int rl_res_id; scalar_t__ rl_type; int /*<<< orphan*/  rl_dev; int /*<<< orphan*/ * rl_intrhand; int /*<<< orphan*/ ** rl_irq; int /*<<< orphan*/  rl_miibus; struct ifnet* rl_ifp; int /*<<< orphan*/  rl_eecmd_read; int /*<<< orphan*/  rl_cfg5; int /*<<< orphan*/  rl_cfg4; int /*<<< orphan*/  rl_cfg3; scalar_t__ rl_cfg2; int /*<<< orphan*/  rl_cfg1; int /*<<< orphan*/  rl_cfg0; int /*<<< orphan*/ * rl_res; int /*<<< orphan*/  rl_bhandle; int /*<<< orphan*/  rl_btag; int /*<<< orphan*/  rl_res_type; int /*<<< orphan*/  rl_mtx; int /*<<< orphan*/  rl_stat_callout; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_capabilities; int if_capenable; TYPE_1__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_mtu; struct rl_softc* if_softc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int CSR_READ_1 (struct rl_softc*,scalar_t__) ; 
 int CSR_READ_4 (struct rl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int ENOSPC ; 
 int ENXIO ; 
 int /*<<< orphan*/  ETHERMTU ; 
 int ETHER_ADDR_LEN ; 
 int IFCAP_POLLING ; 
 int IFCAP_VLAN_MTU ; 
 int IFCAP_WOL ; 
 int IFCAP_WOL_MCAST ; 
 int IFCAP_WOL_UCAST ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_1__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int MII_PHY_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  OID_AUTO ; 
 void* PCIR_BAR (int) ; 
 int /*<<< orphan*/  PCIY_PMG ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 scalar_t__ RL_8139 ; 
 int /*<<< orphan*/  RL_8139_CFG0 ; 
 int /*<<< orphan*/  RL_8139_CFG1 ; 
 int /*<<< orphan*/  RL_8139_CFG3 ; 
 int /*<<< orphan*/  RL_8139_CFG4 ; 
 int /*<<< orphan*/  RL_8139_CFG5 ; 
 int /*<<< orphan*/  RL_EECMD_READ_6BIT ; 
 int /*<<< orphan*/  RL_EECMD_READ_8BIT ; 
 int /*<<< orphan*/  RL_EE_EADDR ; 
 int /*<<< orphan*/  RL_EE_PCI_DID ; 
#define  RL_HWREV_8100 133 
#define  RL_HWREV_8101 132 
#define  RL_HWREV_8130 131 
#define  RL_HWREV_8139B 130 
#define  RL_HWREV_8139C 129 
#define  RL_HWREV_8139D 128 
 scalar_t__ RL_IDR0 ; 
 int /*<<< orphan*/  RL_LOCK (struct rl_softc*) ; 
 int RL_PHYAD_INTERNAL ; 
 int /*<<< orphan*/  RL_TXCFG ; 
 int RL_TXCFG_HWREV ; 
 int /*<<< orphan*/  RL_UNLOCK (struct rl_softc*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rl_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct rl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int*) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rl_clrwol (struct rl_softc*) ; 
 int /*<<< orphan*/  rl_detach (int /*<<< orphan*/ ) ; 
 struct rl_type* rl_devs ; 
 int rl_dma_alloc (struct rl_softc*) ; 
 int /*<<< orphan*/  rl_ifmedia_sts ; 
 int /*<<< orphan*/  rl_ifmedia_upd ; 
 int /*<<< orphan*/  rl_init ; 
 int /*<<< orphan*/  rl_intr ; 
 int /*<<< orphan*/  rl_ioctl ; 
 int /*<<< orphan*/  rl_read_eeprom (struct rl_softc*,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rl_reset (struct rl_softc*) ; 
 int /*<<< orphan*/  rl_start ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int rman_get_end (int /*<<< orphan*/ *) ; 
 int rman_get_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
rl_attach(device_t dev)
{
	uint8_t			eaddr[ETHER_ADDR_LEN];
	uint16_t		as[3];
	struct ifnet		*ifp;
	struct rl_softc		*sc;
	const struct rl_type	*t;
	struct sysctl_ctx_list	*ctx;
	struct sysctl_oid_list	*children;
	int			error = 0, hwrev, i, phy, pmc, rid;
	int			prefer_iomap, unit;
	uint16_t		rl_did = 0;
	char			tn[32];

	sc = device_get_softc(dev);
	unit = device_get_unit(dev);
	sc->rl_dev = dev;

	sc->rl_twister_enable = 0;
	snprintf(tn, sizeof(tn), "dev.rl.%d.twister_enable", unit);
	TUNABLE_INT_FETCH(tn, &sc->rl_twister_enable);
	ctx = device_get_sysctl_ctx(sc->rl_dev);
	children = SYSCTL_CHILDREN(device_get_sysctl_tree(sc->rl_dev));
	SYSCTL_ADD_INT(ctx, children, OID_AUTO, "twister_enable", CTLFLAG_RD,
	   &sc->rl_twister_enable, 0, "");

	mtx_init(&sc->rl_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
	callout_init_mtx(&sc->rl_stat_callout, &sc->rl_mtx, 0);

	pci_enable_busmaster(dev);


	/*
	 * Map control/status registers.
	 * Default to using PIO access for this driver. On SMP systems,
	 * there appear to be problems with memory mapped mode: it looks
	 * like doing too many memory mapped access back to back in rapid
	 * succession can hang the bus. I'm inclined to blame this on
	 * crummy design/construction on the part of RealTek. Memory
	 * mapped mode does appear to work on uniprocessor systems though.
	 */
	prefer_iomap = 1;
	snprintf(tn, sizeof(tn), "dev.rl.%d.prefer_iomap", unit);
	TUNABLE_INT_FETCH(tn, &prefer_iomap);
	if (prefer_iomap) {
		sc->rl_res_id = PCIR_BAR(0);
		sc->rl_res_type = SYS_RES_IOPORT;
		sc->rl_res = bus_alloc_resource_any(dev, sc->rl_res_type,
		    &sc->rl_res_id, RF_ACTIVE);
	}
	if (prefer_iomap == 0 || sc->rl_res == NULL) {
		sc->rl_res_id = PCIR_BAR(1);
		sc->rl_res_type = SYS_RES_MEMORY;
		sc->rl_res = bus_alloc_resource_any(dev, sc->rl_res_type,
		    &sc->rl_res_id, RF_ACTIVE);
	}
	if (sc->rl_res == NULL) {
		device_printf(dev, "couldn't map ports/memory\n");
		error = ENXIO;
		goto fail;
	}

#ifdef notdef
	/*
	 * Detect the Realtek 8139B. For some reason, this chip is very
	 * unstable when left to autoselect the media
	 * The best workaround is to set the device to the required
	 * media type or to set it to the 10 Meg speed.
	 */
	if ((rman_get_end(sc->rl_res) - rman_get_start(sc->rl_res)) == 0xFF)
		device_printf(dev,
"Realtek 8139B detected. Warning, this may be unstable in autoselect mode\n");
#endif

	sc->rl_btag = rman_get_bustag(sc->rl_res);
	sc->rl_bhandle = rman_get_bushandle(sc->rl_res);

	/* Allocate interrupt */
	rid = 0;
	sc->rl_irq[0] = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_SHAREABLE | RF_ACTIVE);

	if (sc->rl_irq[0] == NULL) {
		device_printf(dev, "couldn't map interrupt\n");
		error = ENXIO;
		goto fail;
	}

	sc->rl_cfg0 = RL_8139_CFG0;
	sc->rl_cfg1 = RL_8139_CFG1;
	sc->rl_cfg2 = 0;
	sc->rl_cfg3 = RL_8139_CFG3;
	sc->rl_cfg4 = RL_8139_CFG4;
	sc->rl_cfg5 = RL_8139_CFG5;

	/*
	 * Reset the adapter. Only take the lock here as it's needed in
	 * order to call rl_reset().
	 */
	RL_LOCK(sc);
	rl_reset(sc);
	RL_UNLOCK(sc);

	sc->rl_eecmd_read = RL_EECMD_READ_6BIT;
	rl_read_eeprom(sc, (uint8_t *)&rl_did, 0, 1, 0);
	if (rl_did != 0x8129)
		sc->rl_eecmd_read = RL_EECMD_READ_8BIT;

	/*
	 * Get station address from the EEPROM.
	 */
	rl_read_eeprom(sc, (uint8_t *)as, RL_EE_EADDR, 3, 0);
	for (i = 0; i < 3; i++) {
		eaddr[(i * 2) + 0] = as[i] & 0xff;
		eaddr[(i * 2) + 1] = as[i] >> 8;
	}

	/*
	 * Now read the exact device type from the EEPROM to find
	 * out if it's an 8129 or 8139.
	 */
	rl_read_eeprom(sc, (uint8_t *)&rl_did, RL_EE_PCI_DID, 1, 0);

	t = rl_devs;
	sc->rl_type = 0;
	while(t->rl_name != NULL) {
		if (rl_did == t->rl_did) {
			sc->rl_type = t->rl_basetype;
			break;
		}
		t++;
	}

	if (sc->rl_type == 0) {
		device_printf(dev, "unknown device ID: %x assuming 8139\n",
		    rl_did);
		sc->rl_type = RL_8139;
		/*
		 * Read RL_IDR register to get ethernet address as accessing
		 * EEPROM may not extract correct address.
		 */
		for (i = 0; i < ETHER_ADDR_LEN; i++)
			eaddr[i] = CSR_READ_1(sc, RL_IDR0 + i);
	}

	if ((error = rl_dma_alloc(sc)) != 0)
		goto fail;

	ifp = sc->rl_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "can not if_alloc()\n");
		error = ENOSPC;
		goto fail;
	}

#define	RL_PHYAD_INTERNAL	0

	/* Do MII setup */
	phy = MII_PHY_ANY;
	if (sc->rl_type == RL_8139)
		phy = RL_PHYAD_INTERNAL;
	error = mii_attach(dev, &sc->rl_miibus, ifp, rl_ifmedia_upd,
	    rl_ifmedia_sts, BMSR_DEFCAPMASK, phy, MII_OFFSET_ANY, 0);
	if (error != 0) {
		device_printf(dev, "attaching PHYs failed\n");
		goto fail;
	}

	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_mtu = ETHERMTU;
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_ioctl = rl_ioctl;
	ifp->if_start = rl_start;
	ifp->if_init = rl_init;
	ifp->if_capabilities = IFCAP_VLAN_MTU;
	/* Check WOL for RTL8139B or newer controllers. */
	if (sc->rl_type == RL_8139 &&
	    pci_find_cap(sc->rl_dev, PCIY_PMG, &pmc) == 0) {
		hwrev = CSR_READ_4(sc, RL_TXCFG) & RL_TXCFG_HWREV;
		switch (hwrev) {
		case RL_HWREV_8139B:
		case RL_HWREV_8130:
		case RL_HWREV_8139C:
		case RL_HWREV_8139D:
		case RL_HWREV_8101:
		case RL_HWREV_8100:
			ifp->if_capabilities |= IFCAP_WOL;
			/* Disable WOL. */
			rl_clrwol(sc);
			break;
		default:
			break;
		}
	}
	ifp->if_capenable = ifp->if_capabilities;
	ifp->if_capenable &= ~(IFCAP_WOL_UCAST | IFCAP_WOL_MCAST);
#ifdef DEVICE_POLLING
	ifp->if_capabilities |= IFCAP_POLLING;
#endif
	IFQ_SET_MAXLEN(&ifp->if_snd, ifqmaxlen);
	ifp->if_snd.ifq_drv_maxlen = ifqmaxlen;
	IFQ_SET_READY(&ifp->if_snd);

	/*
	 * Call MI attach routine.
	 */
	ether_ifattach(ifp, eaddr);

	/* Hook interrupt last to avoid having to lock softc */
	error = bus_setup_intr(dev, sc->rl_irq[0], INTR_TYPE_NET | INTR_MPSAFE,
	    NULL, rl_intr, sc, &sc->rl_intrhand[0]);
	if (error) {
		device_printf(sc->rl_dev, "couldn't set up irq\n");
		ether_ifdetach(ifp);
	}

fail:
	if (error)
		rl_detach(dev);

	return (error);
}