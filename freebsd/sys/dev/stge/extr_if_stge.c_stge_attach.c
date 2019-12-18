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
typedef  void* uint32_t ;
typedef  int uint16_t ;
struct stge_softc {scalar_t__ sc_spec; int sc_rev; int sc_usefiber; int sc_led; int sc_stge1023; int sc_PhyCtrl; int sc_txthresh; struct ifnet* sc_ifp; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_ih; int /*<<< orphan*/ * sc_res; int /*<<< orphan*/  sc_DMACtrl; int /*<<< orphan*/  sc_miibus; void* sc_rxint_dmawait; void* sc_rxint_nframe; int /*<<< orphan*/  sc_link_task; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_tick_ch; int /*<<< orphan*/  sc_mii_mtx; } ;
struct TYPE_3__ {scalar_t__ ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_capabilities; int if_capenable; int if_hdrlen; scalar_t__ if_hwassist; TYPE_1__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_ioctl; struct stge_softc* if_softc; } ;
struct ether_vlan_header {int dummy; } ;
typedef  int /*<<< orphan*/  enaddr ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AC_PhyMedia ; 
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int CSR_READ_1 (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int CSR_READ_2 (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int CSR_READ_4 (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 scalar_t__ DEVICEID_SUNDANCETI_ST1023 ; 
 int /*<<< orphan*/  DMAC_MWIDisable ; 
 int ENXIO ; 
 int ETHER_ADDR_LEN ; 
 int IFCAP_HWCSUM ; 
 int IFCAP_POLLING ; 
 int IFCAP_VLAN_HWCSUM ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_VLAN_MTU ; 
 int IFCAP_WOL_MAGIC ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_1__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int MIIF_DOPAUSE ; 
 int MIIF_MACPRIV0 ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MII_PHY_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/ * MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int PCIM_CMD_MWRICEN ; 
 int /*<<< orphan*/  PCIR_BAR (int) ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 scalar_t__ PCI_BAR_IO (void*) ; 
 int PC_PhyDuplexPolarity ; 
 int PC_PhyLnkPolarity ; 
 int /*<<< orphan*/  STGE_AsicCtrl ; 
 scalar_t__ STGE_CSUM_FEATURES ; 
 scalar_t__ STGE_EEPROM_LEDMode ; 
 scalar_t__ STGE_EEPROM_StationAddress0 ; 
 int /*<<< orphan*/  STGE_LOCK (struct stge_softc*) ; 
 int /*<<< orphan*/  STGE_PhyCtrl ; 
 int /*<<< orphan*/  STGE_RESET_FULL ; 
 void* STGE_RXINT_DMAWAIT_DEFAULT ; 
 void* STGE_RXINT_DMAWAIT_MAX ; 
 void* STGE_RXINT_DMAWAIT_MIN ; 
 void* STGE_RXINT_NFRAME_DEFAULT ; 
 void* STGE_RXINT_NFRAME_MAX ; 
 void* STGE_RXINT_NFRAME_MIN ; 
 int /*<<< orphan*/  STGE_StationAddress0 ; 
 int /*<<< orphan*/  STGE_StationAddress1 ; 
 int /*<<< orphan*/  STGE_StationAddress2 ; 
 scalar_t__ STGE_TX_RING_CNT ; 
 int /*<<< orphan*/  STGE_UNLOCK (struct stge_softc*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stge_softc*) ; 
 int /*<<< orphan*/  bcopy (int*,int*,int) ; 
 int bus_alloc_resources (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct stge_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct stge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int*) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le16toh (int) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_get_revid (int /*<<< orphan*/ ) ; 
 void* pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void**) ; 
 int /*<<< orphan*/  stge_detach (int /*<<< orphan*/ ) ; 
 int stge_dma_alloc (struct stge_softc*) ; 
 int /*<<< orphan*/  stge_init ; 
 int /*<<< orphan*/  stge_intr ; 
 int /*<<< orphan*/  stge_ioctl ; 
 int /*<<< orphan*/  stge_link_task ; 
 int /*<<< orphan*/  stge_mediachange ; 
 int /*<<< orphan*/  stge_mediastatus ; 
 int /*<<< orphan*/  stge_read_eeprom (struct stge_softc*,scalar_t__,int*) ; 
 scalar_t__ stge_res_spec_io ; 
 scalar_t__ stge_res_spec_mem ; 
 int /*<<< orphan*/  stge_reset (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stge_start ; 
 int /*<<< orphan*/  sysctl_hw_stge_rxint_dmawait ; 
 int /*<<< orphan*/  sysctl_hw_stge_rxint_nframe ; 

__attribute__((used)) static int
stge_attach(device_t dev)
{
	struct stge_softc *sc;
	struct ifnet *ifp;
	uint8_t enaddr[ETHER_ADDR_LEN];
	int error, flags, i;
	uint16_t cmd;
	uint32_t val;

	error = 0;
	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
	mtx_init(&sc->sc_mii_mtx, "stge_mii_mutex", NULL, MTX_DEF);
	callout_init_mtx(&sc->sc_tick_ch, &sc->sc_mtx, 0);
	TASK_INIT(&sc->sc_link_task, 0, stge_link_task, sc);

	/*
	 * Map the device.
	 */
	pci_enable_busmaster(dev);
	cmd = pci_read_config(dev, PCIR_COMMAND, 2);
	val = pci_read_config(dev, PCIR_BAR(1), 4);
	if (PCI_BAR_IO(val))
		sc->sc_spec = stge_res_spec_mem;
	else {
		val = pci_read_config(dev, PCIR_BAR(0), 4);
		if (!PCI_BAR_IO(val)) {
			device_printf(sc->sc_dev, "couldn't locate IO BAR\n");
			error = ENXIO;
			goto fail;
		}
		sc->sc_spec = stge_res_spec_io;
	}
	error = bus_alloc_resources(dev, sc->sc_spec, sc->sc_res);
	if (error != 0) {
		device_printf(dev, "couldn't allocate %s resources\n",
		    sc->sc_spec == stge_res_spec_mem ? "memory" : "I/O");
		goto fail;
	}
	sc->sc_rev = pci_get_revid(dev);

	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO,
	    "rxint_nframe", CTLTYPE_INT|CTLFLAG_RW, &sc->sc_rxint_nframe, 0,
	    sysctl_hw_stge_rxint_nframe, "I", "stge rx interrupt nframe");

	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO,
	    "rxint_dmawait", CTLTYPE_INT|CTLFLAG_RW, &sc->sc_rxint_dmawait, 0,
	    sysctl_hw_stge_rxint_dmawait, "I", "stge rx interrupt dmawait");

	/* Pull in device tunables. */
	sc->sc_rxint_nframe = STGE_RXINT_NFRAME_DEFAULT;
	error = resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "rxint_nframe", &sc->sc_rxint_nframe);
	if (error == 0) {
		if (sc->sc_rxint_nframe < STGE_RXINT_NFRAME_MIN ||
		    sc->sc_rxint_nframe > STGE_RXINT_NFRAME_MAX) {
			device_printf(dev, "rxint_nframe value out of range; "
			    "using default: %d\n", STGE_RXINT_NFRAME_DEFAULT);
			sc->sc_rxint_nframe = STGE_RXINT_NFRAME_DEFAULT;
		}
	}

	sc->sc_rxint_dmawait = STGE_RXINT_DMAWAIT_DEFAULT;
	error = resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "rxint_dmawait", &sc->sc_rxint_dmawait);
	if (error == 0) {
		if (sc->sc_rxint_dmawait < STGE_RXINT_DMAWAIT_MIN ||
		    sc->sc_rxint_dmawait > STGE_RXINT_DMAWAIT_MAX) {
			device_printf(dev, "rxint_dmawait value out of range; "
			    "using default: %d\n", STGE_RXINT_DMAWAIT_DEFAULT);
			sc->sc_rxint_dmawait = STGE_RXINT_DMAWAIT_DEFAULT;
		}
	}

	if ((error = stge_dma_alloc(sc)) != 0)
		goto fail;

	/*
	 * Determine if we're copper or fiber.  It affects how we
	 * reset the card.
	 */
	if (CSR_READ_4(sc, STGE_AsicCtrl) & AC_PhyMedia)
		sc->sc_usefiber = 1;
	else
		sc->sc_usefiber = 0;

	/* Load LED configuration from EEPROM. */
	stge_read_eeprom(sc, STGE_EEPROM_LEDMode, &sc->sc_led);

	/*
	 * Reset the chip to a known state.
	 */
	STGE_LOCK(sc);
	stge_reset(sc, STGE_RESET_FULL);
	STGE_UNLOCK(sc);

	/*
	 * Reading the station address from the EEPROM doesn't seem
	 * to work, at least on my sample boards.  Instead, since
	 * the reset sequence does AutoInit, read it from the station
	 * address registers. For Sundance 1023 you can only read it
	 * from EEPROM.
	 */
	if (pci_get_device(dev) != DEVICEID_SUNDANCETI_ST1023) {
		uint16_t v;

		v = CSR_READ_2(sc, STGE_StationAddress0);
		enaddr[0] = v & 0xff;
		enaddr[1] = v >> 8;
		v = CSR_READ_2(sc, STGE_StationAddress1);
		enaddr[2] = v & 0xff;
		enaddr[3] = v >> 8;
		v = CSR_READ_2(sc, STGE_StationAddress2);
		enaddr[4] = v & 0xff;
		enaddr[5] = v >> 8;
		sc->sc_stge1023 = 0;
	} else {
		uint16_t myaddr[ETHER_ADDR_LEN / 2];
		for (i = 0; i <ETHER_ADDR_LEN / 2; i++) {
			stge_read_eeprom(sc, STGE_EEPROM_StationAddress0 + i,
			    &myaddr[i]);
			myaddr[i] = le16toh(myaddr[i]);
		}
		bcopy(myaddr, enaddr, sizeof(enaddr));
		sc->sc_stge1023 = 1;
	}

	ifp = sc->sc_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(sc->sc_dev, "failed to if_alloc()\n");
		error = ENXIO;
		goto fail;
	}

	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_ioctl = stge_ioctl;
	ifp->if_start = stge_start;
	ifp->if_init = stge_init;
	ifp->if_snd.ifq_drv_maxlen = STGE_TX_RING_CNT - 1;
	IFQ_SET_MAXLEN(&ifp->if_snd, ifp->if_snd.ifq_drv_maxlen);
	IFQ_SET_READY(&ifp->if_snd);
	/* Revision B3 and earlier chips have checksum bug. */
	if (sc->sc_rev >= 0x0c) {
		ifp->if_hwassist = STGE_CSUM_FEATURES;
		ifp->if_capabilities = IFCAP_HWCSUM;
	} else {
		ifp->if_hwassist = 0;
		ifp->if_capabilities = 0;
	}
	ifp->if_capabilities |= IFCAP_WOL_MAGIC;
	ifp->if_capenable = ifp->if_capabilities;

	/*
	 * Read some important bits from the PhyCtrl register.
	 */
	sc->sc_PhyCtrl = CSR_READ_1(sc, STGE_PhyCtrl) &
	    (PC_PhyDuplexPolarity | PC_PhyLnkPolarity);

	/* Set up MII bus. */
	flags = MIIF_DOPAUSE;
	if (sc->sc_rev >= 0x40 && sc->sc_rev <= 0x4e)
		flags |= MIIF_MACPRIV0;
	error = mii_attach(sc->sc_dev, &sc->sc_miibus, ifp, stge_mediachange,
	    stge_mediastatus, BMSR_DEFCAPMASK, MII_PHY_ANY, MII_OFFSET_ANY,
	    flags);
	if (error != 0) {
		device_printf(sc->sc_dev, "attaching PHYs failed\n");
		goto fail;
	}

	ether_ifattach(ifp, enaddr);

	/* VLAN capability setup */
	ifp->if_capabilities |= IFCAP_VLAN_MTU | IFCAP_VLAN_HWTAGGING;
	if (sc->sc_rev >= 0x0c)
		ifp->if_capabilities |= IFCAP_VLAN_HWCSUM;
	ifp->if_capenable = ifp->if_capabilities;
#ifdef DEVICE_POLLING
	ifp->if_capabilities |= IFCAP_POLLING;
#endif
	/*
	 * Tell the upper layer(s) we support long frames.
	 * Must appear after the call to ether_ifattach() because
	 * ether_ifattach() sets ifi_hdrlen to the default value.
	 */
	ifp->if_hdrlen = sizeof(struct ether_vlan_header);

	/*
	 * The manual recommends disabling early transmit, so we
	 * do.  It's disabled anyway, if using IP checksumming,
	 * since the entire packet must be in the FIFO in order
	 * for the chip to perform the checksum.
	 */
	sc->sc_txthresh = 0x0fff;

	/*
	 * Disable MWI if the PCI layer tells us to.
	 */
	sc->sc_DMACtrl = 0;
	if ((cmd & PCIM_CMD_MWRICEN) == 0)
		sc->sc_DMACtrl |= DMAC_MWIDisable;

	/*
	 * Hookup IRQ
	 */
	error = bus_setup_intr(dev, sc->sc_res[1], INTR_TYPE_NET | INTR_MPSAFE,
	    NULL, stge_intr, sc, &sc->sc_ih);
	if (error != 0) {
		ether_ifdetach(ifp);
		device_printf(sc->sc_dev, "couldn't set up IRQ\n");
		sc->sc_ifp = NULL;
		goto fail;
	}

fail:
	if (error != 0)
		stge_detach(dev);

	return (error);
}