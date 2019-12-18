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
typedef  int /*<<< orphan*/  uint8_t ;
struct sge_softc {int sge_res_id; int sge_flags; int /*<<< orphan*/  sge_intrhand; int /*<<< orphan*/ * sge_irq; int /*<<< orphan*/  sge_miibus; struct ifnet* sge_ifp; int /*<<< orphan*/  sge_rev; int /*<<< orphan*/ * sge_res; int /*<<< orphan*/  sge_res_type; int /*<<< orphan*/  sge_mtx; int /*<<< orphan*/  sge_stat_ch; int /*<<< orphan*/  sge_dev; } ;
struct TYPE_3__ {scalar_t__ ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_capabilities; int if_hwassist; int if_capenable; int if_hdrlen; TYPE_1__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_ioctl; struct sge_softc* if_softc; } ;
struct ether_vlan_header {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int CSUM_TSO ; 
 int ENOSPC ; 
 int ENXIO ; 
 int ETHER_ADDR_LEN ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_VLAN_HWCSUM ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_VLAN_HWTSO ; 
 int IFCAP_VLAN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_1__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MII_PHY_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int SGE_CSUM_FEATURES ; 
 int SGE_FLAG_FASTETHER ; 
 int SGE_FLAG_SIS190 ; 
 scalar_t__ SGE_TX_RING_CNT ; 
 scalar_t__ SIS_DEVICEID_190 ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sge_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct sge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_revid (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sge_detach (int /*<<< orphan*/ ) ; 
 int sge_dma_alloc (struct sge_softc*) ; 
 int /*<<< orphan*/  sge_get_mac_addr_apc (struct sge_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sge_get_mac_addr_eeprom (struct sge_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sge_ifmedia_sts ; 
 int /*<<< orphan*/  sge_ifmedia_upd ; 
 int /*<<< orphan*/  sge_init ; 
 int /*<<< orphan*/  sge_intr ; 
 int /*<<< orphan*/  sge_ioctl ; 
 int /*<<< orphan*/  sge_reset (struct sge_softc*) ; 
 int /*<<< orphan*/  sge_start ; 

__attribute__((used)) static int
sge_attach(device_t dev)
{
	struct sge_softc *sc;
	struct ifnet *ifp;
	uint8_t eaddr[ETHER_ADDR_LEN];
	int error = 0, rid;

	sc = device_get_softc(dev);
	sc->sge_dev = dev;

	mtx_init(&sc->sge_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
        callout_init_mtx(&sc->sge_stat_ch, &sc->sge_mtx, 0);

	/*
	 * Map control/status registers.
	 */
	pci_enable_busmaster(dev);

	/* Allocate resources. */
	sc->sge_res_id = PCIR_BAR(0);
	sc->sge_res_type = SYS_RES_MEMORY;
	sc->sge_res = bus_alloc_resource_any(dev, sc->sge_res_type,
	    &sc->sge_res_id, RF_ACTIVE);
	if (sc->sge_res == NULL) {
		device_printf(dev, "couldn't allocate resource\n");
		error = ENXIO;
		goto fail;
	}

	rid = 0;
	sc->sge_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_SHAREABLE | RF_ACTIVE);
	if (sc->sge_irq == NULL) {
		device_printf(dev, "couldn't allocate IRQ resources\n");
		error = ENXIO;
		goto fail;
	}
	sc->sge_rev = pci_get_revid(dev);
	if (pci_get_device(dev) == SIS_DEVICEID_190)
		sc->sge_flags |= SGE_FLAG_FASTETHER | SGE_FLAG_SIS190;
	/* Reset the adapter. */
	sge_reset(sc);

	/* Get MAC address from the EEPROM. */
	if ((pci_read_config(dev, 0x73, 1) & 0x01) != 0)
		sge_get_mac_addr_apc(sc, eaddr);
	else
		sge_get_mac_addr_eeprom(sc, eaddr);

	if ((error = sge_dma_alloc(sc)) != 0)
		goto fail;

	ifp = sc->sge_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "cannot allocate ifnet structure.\n");
		error = ENOSPC;
		goto fail;
	}
	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_ioctl = sge_ioctl;
	ifp->if_start = sge_start;
	ifp->if_init = sge_init;
	ifp->if_snd.ifq_drv_maxlen = SGE_TX_RING_CNT - 1;
	IFQ_SET_MAXLEN(&ifp->if_snd, ifp->if_snd.ifq_drv_maxlen);
	IFQ_SET_READY(&ifp->if_snd);
	ifp->if_capabilities = IFCAP_TXCSUM | IFCAP_RXCSUM | IFCAP_TSO4;
	ifp->if_hwassist = SGE_CSUM_FEATURES | CSUM_TSO;
	ifp->if_capenable = ifp->if_capabilities;
	/*
	 * Do MII setup.
	 */
	error = mii_attach(dev, &sc->sge_miibus, ifp, sge_ifmedia_upd,
	    sge_ifmedia_sts, BMSR_DEFCAPMASK, MII_PHY_ANY, MII_OFFSET_ANY, 0);
	if (error != 0) {
		device_printf(dev, "attaching PHYs failed\n");
		goto fail;
	}

	/*
	 * Call MI attach routine.
	 */
	ether_ifattach(ifp, eaddr);

	/* VLAN setup. */
	ifp->if_capabilities |= IFCAP_VLAN_HWTAGGING | IFCAP_VLAN_HWCSUM |
	    IFCAP_VLAN_HWTSO | IFCAP_VLAN_MTU;
	ifp->if_capenable = ifp->if_capabilities;
	/* Tell the upper layer(s) we support long frames. */
	ifp->if_hdrlen = sizeof(struct ether_vlan_header);

	/* Hook interrupt last to avoid having to lock softc */
	error = bus_setup_intr(dev, sc->sge_irq, INTR_TYPE_NET | INTR_MPSAFE,
	    NULL, sge_intr, sc, &sc->sge_intrhand);
	if (error) {
		device_printf(dev, "couldn't set up irq\n");
		ether_ifdetach(ifp);
		goto fail;
	}

fail:
	if (error)
		sge_detach(dev);

	return (error);
}