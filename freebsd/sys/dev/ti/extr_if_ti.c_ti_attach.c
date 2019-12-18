#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u_char ;
struct ti_softc {int ti_copper; int /*<<< orphan*/  ti_intrhand; int /*<<< orphan*/ * ti_irq; TYPE_1__* dev; int /*<<< orphan*/  ifmedia; int /*<<< orphan*/ * ti_membuf2; int /*<<< orphan*/ * ti_membuf; int /*<<< orphan*/ * ti_res; int /*<<< orphan*/  ti_bhandle; int /*<<< orphan*/  ti_btag; struct ifnet* ti_ifp; int /*<<< orphan*/  ti_mtx; int /*<<< orphan*/  ti_watchdog; int /*<<< orphan*/  ti_dev; } ;
struct TYPE_5__ {scalar_t__ ifq_drv_maxlen; } ;
struct ifnet {int if_capabilities; int if_capenable; int if_flags; int if_hdrlen; TYPE_2__ if_snd; int /*<<< orphan*/  if_baudrate; int /*<<< orphan*/  if_get_counter; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_ioctl; struct ti_softc* if_softc; int /*<<< orphan*/  if_hwassist; } ;
struct ether_vlan_header {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {struct ti_softc* si_drv1; } ;

/* Variables and functions */
 scalar_t__ ALT_DEVICEID_ACENIC_COPPER ; 
 scalar_t__ ALT_VENDORID ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int ENXIO ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  GID_OPERATOR ; 
 int IFCAP_LINKSTATE ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_VLAN_HWCSUM ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_VLAN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int IFM_1000_SX ; 
 int IFM_1000_T ; 
 int IFM_100_TX ; 
 int IFM_10_T ; 
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int IFM_FDX ; 
 int /*<<< orphan*/  IFM_IMASK ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_2__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  IF_Gbps (unsigned long) ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 scalar_t__ NG_DEVICEID_GA620T ; 
 scalar_t__ NG_VENDORID ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TI_CSUM_FEATURES ; 
 scalar_t__ TI_EE_MAC_OFFSET ; 
 scalar_t__ TI_TX_RING_CNT ; 
 int TI_WINLEN ; 
 int /*<<< orphan*/  UID_ROOT ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ti_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct ti_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ *) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_add (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ti_cdevsw ; 
 scalar_t__ ti_chipinit (struct ti_softc*) ; 
 int /*<<< orphan*/  ti_detach (int /*<<< orphan*/ ) ; 
 int ti_dma_alloc (struct ti_softc*) ; 
 int /*<<< orphan*/  ti_get_counter ; 
 int /*<<< orphan*/  ti_ifmedia_sts ; 
 int /*<<< orphan*/  ti_ifmedia_upd ; 
 int /*<<< orphan*/  ti_init ; 
 int /*<<< orphan*/  ti_intr ; 
 int /*<<< orphan*/  ti_ioctl ; 
 int /*<<< orphan*/  ti_mem_zero (struct ti_softc*,int,int) ; 
 scalar_t__ ti_read_eeprom (struct ti_softc*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_start ; 
 int /*<<< orphan*/  ti_sysctl_node (struct ti_softc*) ; 

__attribute__((used)) static int
ti_attach(device_t dev)
{
	struct ifnet *ifp;
	struct ti_softc *sc;
	int error = 0, rid;
	u_char eaddr[6];

	sc = device_get_softc(dev);
	sc->ti_dev = dev;

	mtx_init(&sc->ti_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
	callout_init_mtx(&sc->ti_watchdog, &sc->ti_mtx, 0);
	ifmedia_init(&sc->ifmedia, IFM_IMASK, ti_ifmedia_upd, ti_ifmedia_sts);
	ifp = sc->ti_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "can not if_alloc()\n");
		error = ENOSPC;
		goto fail;
	}
	sc->ti_ifp->if_hwassist = TI_CSUM_FEATURES;
	sc->ti_ifp->if_capabilities = IFCAP_TXCSUM | IFCAP_RXCSUM;
	sc->ti_ifp->if_capenable = sc->ti_ifp->if_capabilities;

	/*
	 * Map control/status registers.
	 */
	pci_enable_busmaster(dev);

	rid = PCIR_BAR(0);
	sc->ti_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);

	if (sc->ti_res == NULL) {
		device_printf(dev, "couldn't map memory\n");
		error = ENXIO;
		goto fail;
	}

	sc->ti_btag = rman_get_bustag(sc->ti_res);
	sc->ti_bhandle = rman_get_bushandle(sc->ti_res);

	/* Allocate interrupt */
	rid = 0;

	sc->ti_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_SHAREABLE | RF_ACTIVE);

	if (sc->ti_irq == NULL) {
		device_printf(dev, "couldn't map interrupt\n");
		error = ENXIO;
		goto fail;
	}

	if (ti_chipinit(sc)) {
		device_printf(dev, "chip initialization failed\n");
		error = ENXIO;
		goto fail;
	}

	/* Zero out the NIC's on-board SRAM. */
	ti_mem_zero(sc, 0x2000, 0x100000 - 0x2000);

	/* Init again -- zeroing memory may have clobbered some registers. */
	if (ti_chipinit(sc)) {
		device_printf(dev, "chip initialization failed\n");
		error = ENXIO;
		goto fail;
	}

	/*
	 * Get station address from the EEPROM. Note: the manual states
	 * that the MAC address is at offset 0x8c, however the data is
	 * stored as two longwords (since that's how it's loaded into
	 * the NIC). This means the MAC address is actually preceded
	 * by two zero bytes. We need to skip over those.
	 */
	if (ti_read_eeprom(sc, eaddr, TI_EE_MAC_OFFSET + 2, ETHER_ADDR_LEN)) {
		device_printf(dev, "failed to read station address\n");
		error = ENXIO;
		goto fail;
	}

	/* Allocate working area for memory dump. */
	sc->ti_membuf = malloc(sizeof(uint8_t) * TI_WINLEN, M_DEVBUF, M_NOWAIT);
	sc->ti_membuf2 = malloc(sizeof(uint8_t) * TI_WINLEN, M_DEVBUF,
	    M_NOWAIT);
	if (sc->ti_membuf == NULL || sc->ti_membuf2 == NULL) {
		device_printf(dev, "cannot allocate memory buffer\n");
		error = ENOMEM;
		goto fail;
	}
	if ((error = ti_dma_alloc(sc)) != 0)
		goto fail;

	/*
	 * We really need a better way to tell a 1000baseTX card
	 * from a 1000baseSX one, since in theory there could be
	 * OEMed 1000baseTX cards from lame vendors who aren't
	 * clever enough to change the PCI ID. For the moment
	 * though, the AceNIC is the only copper card available.
	 */
	if (pci_get_vendor(dev) == ALT_VENDORID &&
	    pci_get_device(dev) == ALT_DEVICEID_ACENIC_COPPER)
		sc->ti_copper = 1;
	/* Ok, it's not the only copper card available. */
	if (pci_get_vendor(dev) == NG_VENDORID &&
	    pci_get_device(dev) == NG_DEVICEID_GA620T)
		sc->ti_copper = 1;

	/* Set default tunable values. */
	ti_sysctl_node(sc);

	/* Set up ifnet structure */
	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_ioctl = ti_ioctl;
	ifp->if_start = ti_start;
	ifp->if_init = ti_init;
	ifp->if_get_counter = ti_get_counter;
	ifp->if_baudrate = IF_Gbps(1UL);
	ifp->if_snd.ifq_drv_maxlen = TI_TX_RING_CNT - 1;
	IFQ_SET_MAXLEN(&ifp->if_snd, ifp->if_snd.ifq_drv_maxlen);
	IFQ_SET_READY(&ifp->if_snd);

	/* Set up ifmedia support. */
	if (sc->ti_copper) {
		/*
		 * Copper cards allow manual 10/100 mode selection,
		 * but not manual 1000baseTX mode selection. Why?
		 * Because currently there's no way to specify the
		 * master/slave setting through the firmware interface,
		 * so Alteon decided to just bag it and handle it
		 * via autonegotiation.
		 */
		ifmedia_add(&sc->ifmedia, IFM_ETHER|IFM_10_T, 0, NULL);
		ifmedia_add(&sc->ifmedia,
		    IFM_ETHER|IFM_10_T|IFM_FDX, 0, NULL);
		ifmedia_add(&sc->ifmedia, IFM_ETHER|IFM_100_TX, 0, NULL);
		ifmedia_add(&sc->ifmedia,
		    IFM_ETHER|IFM_100_TX|IFM_FDX, 0, NULL);
		ifmedia_add(&sc->ifmedia, IFM_ETHER|IFM_1000_T, 0, NULL);
		ifmedia_add(&sc->ifmedia,
		    IFM_ETHER|IFM_1000_T|IFM_FDX, 0, NULL);
	} else {
		/* Fiber cards don't support 10/100 modes. */
		ifmedia_add(&sc->ifmedia, IFM_ETHER|IFM_1000_SX, 0, NULL);
		ifmedia_add(&sc->ifmedia,
		    IFM_ETHER|IFM_1000_SX|IFM_FDX, 0, NULL);
	}
	ifmedia_add(&sc->ifmedia, IFM_ETHER|IFM_AUTO, 0, NULL);
	ifmedia_set(&sc->ifmedia, IFM_ETHER|IFM_AUTO);

	/*
	 * We're assuming here that card initialization is a sequential
	 * thing.  If it isn't, multiple cards probing at the same time
	 * could stomp on the list of softcs here.
	 */

	/* Register the device */
	sc->dev = make_dev(&ti_cdevsw, device_get_unit(dev), UID_ROOT,
	    GID_OPERATOR, 0600, "ti%d", device_get_unit(dev));
	sc->dev->si_drv1 = sc;

	/*
	 * Call MI attach routine.
	 */
	ether_ifattach(ifp, eaddr);

	/* VLAN capability setup. */
	ifp->if_capabilities |= IFCAP_VLAN_MTU | IFCAP_VLAN_HWCSUM |
	    IFCAP_VLAN_HWTAGGING;
	ifp->if_capenable = ifp->if_capabilities;
	/* Tell the upper layer we support VLAN over-sized frames. */
	ifp->if_hdrlen = sizeof(struct ether_vlan_header);

	/* Driver supports link state tracking. */
	ifp->if_capabilities |= IFCAP_LINKSTATE;
	ifp->if_capenable |= IFCAP_LINKSTATE;

	/* Hook interrupt last to avoid having to lock softc */
	error = bus_setup_intr(dev, sc->ti_irq, INTR_TYPE_NET|INTR_MPSAFE,
	   NULL, ti_intr, sc, &sc->ti_intrhand);

	if (error) {
		device_printf(dev, "couldn't set up irq\n");
		goto fail;
	}

fail:
	if (error)
		ti_detach(dev);

	return (error);
}