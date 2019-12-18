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
typedef  int uint16_t ;
typedef  int u_char ;
struct fxp_tx {int /*<<< orphan*/  tx_map; struct fxp_cb_tx* tx_cb; } ;
struct fxp_stats {int dummy; } ;
struct TYPE_3__ {struct fxp_rx* rx_list; int /*<<< orphan*/ * rx_tail; int /*<<< orphan*/  rx_head; struct fxp_cb_tx* cbl_list; struct fxp_tx* tx_list; int /*<<< orphan*/  cbl_addr; } ;
struct fxp_softc {scalar_t__ fxp_spec; scalar_t__ revision; int* eeprom; int flags; int eeprom_size; int rfa_size; int maxtxseg; int maxsegsize; void* ifp; int /*<<< orphan*/  ih; int /*<<< orphan*/ * fxp_res; int /*<<< orphan*/  miibus; int /*<<< orphan*/  sc_media; int /*<<< orphan*/  fxp_rxmtag; TYPE_1__ fxp_desc; int /*<<< orphan*/  spare_map; int /*<<< orphan*/  fxp_txmtag; int /*<<< orphan*/  mcs_addr; struct fxp_cb_tx* mcsp; int /*<<< orphan*/  mcs_map; int /*<<< orphan*/  mcs_tag; int /*<<< orphan*/  cbl_map; int /*<<< orphan*/  cbl_tag; int /*<<< orphan*/  stats_addr; struct fxp_cb_tx* fxp_stats; int /*<<< orphan*/  fxp_smap; int /*<<< orphan*/  fxp_stag; int /*<<< orphan*/  tx_cmd; TYPE_2__* ident; int /*<<< orphan*/  dev; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  stat_ch; } ;
struct fxp_rx {int /*<<< orphan*/  rx_map; } ;
struct fxp_rfa {int dummy; } ;
struct fxp_cb_tx {int dummy; } ;
struct fxp_cb_mcs {int dummy; } ;
struct ether_vlan_header {int dummy; } ;
typedef  int /*<<< orphan*/  ifm_stat_cb_t ;
typedef  int /*<<< orphan*/  ifm_change_cb_t ;
typedef  void* if_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int ich; int device; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_NOWAIT ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  CSR_READ_1 (struct fxp_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct fxp_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct fxp_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CSUM_TSO ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int ENXIO ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  FXP_CB_COMMAND_IPCBXMIT ; 
 int /*<<< orphan*/  FXP_CB_COMMAND_XMIT ; 
 int /*<<< orphan*/  FXP_CSR_PMDR ; 
 int /*<<< orphan*/  FXP_CSR_PORT ; 
 int /*<<< orphan*/  FXP_CSR_SCB_INTRCNTL ; 
 int FXP_CSUM_FEATURES ; 
 size_t FXP_EEPROM_MAP_CNTR ; 
 size_t FXP_EEPROM_MAP_COMPAT ; 
 size_t FXP_EEPROM_MAP_IA0 ; 
 size_t FXP_EEPROM_MAP_IA1 ; 
 size_t FXP_EEPROM_MAP_IA2 ; 
 size_t FXP_EEPROM_MAP_ID ; 
 size_t FXP_EEPROM_MAP_PRI_PHY ; 
 int FXP_FLAG_82559_RXCSUM ; 
 int FXP_FLAG_CU_RESUME_BUG ; 
 int FXP_FLAG_EXT_RFA ; 
 int FXP_FLAG_EXT_TXCB ; 
 int FXP_FLAG_LONG_PKT_EN ; 
 int FXP_FLAG_MWI_ENABLE ; 
 int FXP_FLAG_NO_UCODE ; 
 int FXP_FLAG_RXBUG ; 
 int FXP_FLAG_SAVE_BAD ; 
 int FXP_FLAG_SERIAL_MEDIA ; 
 int FXP_FLAG_WOLCAP ; 
 int /*<<< orphan*/  FXP_LOCK (struct fxp_softc*) ; 
 int FXP_NRFABUFS ; 
 int FXP_NTXCB ; 
 int FXP_NTXSEG ; 
 int FXP_PHY_DEVICE_MASK ; 
 int FXP_PHY_SERIAL_ONLY ; 
 int /*<<< orphan*/  FXP_PORT_SELECTIVE_RESET ; 
 int /*<<< orphan*/  FXP_PORT_SOFTWARE_RESET ; 
 scalar_t__ FXP_REV_82550 ; 
 scalar_t__ FXP_REV_82550_C ; 
 scalar_t__ FXP_REV_82551_10 ; 
 scalar_t__ FXP_REV_82551_E ; 
 scalar_t__ FXP_REV_82551_F ; 
 scalar_t__ FXP_REV_82557 ; 
 scalar_t__ FXP_REV_82558_A4 ; 
 scalar_t__ FXP_REV_82559S_A ; 
 scalar_t__ FXP_REV_82559_A0 ; 
 int FXP_RFAX_LEN ; 
 int /*<<< orphan*/  FXP_SCB_INTR_DISABLE ; 
 int FXP_TSO_SEGSIZE ; 
 int FXP_TXCB_SZ ; 
 int /*<<< orphan*/  FXP_UNLOCK (struct fxp_softc*) ; 
 int /*<<< orphan*/  Giant ; 
 int IFCAP_HWCSUM ; 
 int IFCAP_POLLING ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_TSO4 ; 
 int IFCAP_VLAN_HWCSUM ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_VLAN_HWTSO ; 
 int IFCAP_VLAN_MTU ; 
 int IFCAP_WOL_MAGIC ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int IFM_ETHER ; 
 int IFM_MANUAL ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int MCLBYTES ; 
 int MIIF_DOPAUSE ; 
 int MIIF_NOISOLATE ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MII_PHY_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int PCIM_CMD_MWRICEN ; 
 int /*<<< orphan*/  PCIR_CACHELNSZ ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int /*<<< orphan*/  PCIY_PMG ; 
 scalar_t__ bootverbose ; 
 int bus_alloc_resources (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fxp_cb_tx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct fxp_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  busdma_lock_mutex ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct fxp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ether_ifattach (void*,int*) ; 
 int /*<<< orphan*/  ether_ifdetach (void*) ; 
 int /*<<< orphan*/  fxp_add_rfabuf (struct fxp_softc*,struct fxp_rx*) ; 
 int /*<<< orphan*/  fxp_autosize_eeprom (struct fxp_softc*) ; 
 int /*<<< orphan*/  fxp_dma_map_addr ; 
 TYPE_2__* fxp_find_ident (int /*<<< orphan*/ ) ; 
 scalar_t__ fxp_ifmedia_sts ; 
 scalar_t__ fxp_ifmedia_upd ; 
 int /*<<< orphan*/  fxp_init ; 
 int /*<<< orphan*/  fxp_init_body (struct fxp_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fxp_intr ; 
 int /*<<< orphan*/  fxp_ioctl ; 
 int /*<<< orphan*/  fxp_load_eeprom (struct fxp_softc*) ; 
 scalar_t__ fxp_new_rfabuf (struct fxp_softc*,struct fxp_rx*) ; 
 int /*<<< orphan*/  fxp_release (struct fxp_softc*) ; 
 void* fxp_res_spec_io ; 
 scalar_t__ fxp_res_spec_mem ; 
 int /*<<< orphan*/  fxp_serial_ifmedia_sts ; 
 int /*<<< orphan*/  fxp_serial_ifmedia_upd ; 
 int /*<<< orphan*/  fxp_start ; 
 int /*<<< orphan*/  fxp_stop (struct fxp_softc*) ; 
 int /*<<< orphan*/  fxp_sysctl_node (struct fxp_softc*) ; 
 int /*<<< orphan*/  fxp_write_eeprom (struct fxp_softc*,int*,int,int) ; 
 void* if_gethandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapabilities (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapabilitiesbit (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapenable (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapenablebit (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setdev (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setflags (void*,int) ; 
 int /*<<< orphan*/  if_sethwassist (void*,int) ; 
 int /*<<< orphan*/  if_setifheaderlen (void*,int) ; 
 int /*<<< orphan*/  if_setinitfn (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setioctlfn (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setsendqlen (void*,int) ; 
 int /*<<< orphan*/  if_setsendqready (void*) ; 
 int /*<<< orphan*/  if_setsoftc (void*,struct fxp_softc*) ; 
 int /*<<< orphan*/  if_setstartfn (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_add (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (int /*<<< orphan*/ *,int) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_revid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_subdevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_subvendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_vendor (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static int
fxp_attach(device_t dev)
{
	struct fxp_softc *sc;
	struct fxp_cb_tx *tcbp;
	struct fxp_tx *txp;
	struct fxp_rx *rxp;
	if_t ifp;
	uint32_t val;
	uint16_t data;
	u_char eaddr[ETHER_ADDR_LEN];
	int error, flags, i, pmc, prefer_iomap;

	error = 0;
	sc = device_get_softc(dev);
	sc->dev = dev;
	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
	callout_init_mtx(&sc->stat_ch, &sc->sc_mtx, 0);
	ifmedia_init(&sc->sc_media, 0, fxp_serial_ifmedia_upd,
	    fxp_serial_ifmedia_sts);

	ifp = sc->ifp = if_gethandle(IFT_ETHER);
	if (ifp == (void *)NULL) {
		device_printf(dev, "can not if_alloc()\n");
		error = ENOSPC;
		goto fail;
	}

	/*
	 * Enable bus mastering.
	 */
	pci_enable_busmaster(dev);

	/*
	 * Figure out which we should try first - memory mapping or i/o mapping?
	 * We default to memory mapping. Then we accept an override from the
	 * command line. Then we check to see which one is enabled.
	 */
	prefer_iomap = 0;
	resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "prefer_iomap", &prefer_iomap);
	if (prefer_iomap)
		sc->fxp_spec = fxp_res_spec_io;
	else
		sc->fxp_spec = fxp_res_spec_mem;

	error = bus_alloc_resources(dev, sc->fxp_spec, sc->fxp_res);
	if (error) {
		if (sc->fxp_spec == fxp_res_spec_mem)
			sc->fxp_spec = fxp_res_spec_io;
		else
			sc->fxp_spec = fxp_res_spec_mem;
		error = bus_alloc_resources(dev, sc->fxp_spec, sc->fxp_res);
	}
	if (error) {
		device_printf(dev, "could not allocate resources\n");
		error = ENXIO;
		goto fail;
	}

	if (bootverbose) {
		device_printf(dev, "using %s space register mapping\n",
		   sc->fxp_spec == fxp_res_spec_mem ? "memory" : "I/O");
	}

	/*
	 * Put CU/RU idle state and prepare full reset.
	 */
	CSR_WRITE_4(sc, FXP_CSR_PORT, FXP_PORT_SELECTIVE_RESET);
	DELAY(10);
	/* Full reset and disable interrupts. */
	CSR_WRITE_4(sc, FXP_CSR_PORT, FXP_PORT_SOFTWARE_RESET);
	DELAY(10);
	CSR_WRITE_1(sc, FXP_CSR_SCB_INTRCNTL, FXP_SCB_INTR_DISABLE);

	/*
	 * Find out how large of an SEEPROM we have.
	 */
	fxp_autosize_eeprom(sc);
	fxp_load_eeprom(sc);

	/*
	 * Find out the chip revision; lump all 82557 revs together.
	 */
	sc->ident = fxp_find_ident(dev);
	if (sc->ident->ich > 0) {
		/* Assume ICH controllers are 82559. */
		sc->revision = FXP_REV_82559_A0;
	} else {
		data = sc->eeprom[FXP_EEPROM_MAP_CNTR];
		if ((data >> 8) == 1)
			sc->revision = FXP_REV_82557;
		else
			sc->revision = pci_get_revid(dev);
	}

	/*
	 * Check availability of WOL. 82559ER does not support WOL.
	 */
	if (sc->revision >= FXP_REV_82558_A4 &&
	    sc->revision != FXP_REV_82559S_A) {
		data = sc->eeprom[FXP_EEPROM_MAP_ID];
		if ((data & 0x20) != 0 &&
		    pci_find_cap(sc->dev, PCIY_PMG, &pmc) == 0)
			sc->flags |= FXP_FLAG_WOLCAP;
	}

	if (sc->revision == FXP_REV_82550_C) {
		/*
		 * 82550C with server extension requires microcode to
		 * receive fragmented UDP datagrams.  However if the
		 * microcode is used for client-only featured 82550C
		 * it locks up controller.
		 */
		data = sc->eeprom[FXP_EEPROM_MAP_COMPAT];
		if ((data & 0x0400) == 0)
			sc->flags |= FXP_FLAG_NO_UCODE;
	}

	/* Receiver lock-up workaround detection. */
	if (sc->revision < FXP_REV_82558_A4) {
		data = sc->eeprom[FXP_EEPROM_MAP_COMPAT];
		if ((data & 0x03) != 0x03) {
			sc->flags |= FXP_FLAG_RXBUG;
			device_printf(dev, "Enabling Rx lock-up workaround\n");
		}
	}

	/*
	 * Determine whether we must use the 503 serial interface.
	 */
	data = sc->eeprom[FXP_EEPROM_MAP_PRI_PHY];
	if (sc->revision == FXP_REV_82557 && (data & FXP_PHY_DEVICE_MASK) != 0
	    && (data & FXP_PHY_SERIAL_ONLY))
		sc->flags |= FXP_FLAG_SERIAL_MEDIA;

	fxp_sysctl_node(sc);
	/*
	 * Enable workarounds for certain chip revision deficiencies.
	 *
	 * Systems based on the ICH2/ICH2-M chip from Intel, and possibly
	 * some systems based a normal 82559 design, have a defect where
	 * the chip can cause a PCI protocol violation if it receives
	 * a CU_RESUME command when it is entering the IDLE state.  The
	 * workaround is to disable Dynamic Standby Mode, so the chip never
	 * deasserts CLKRUN#, and always remains in an active state.
	 *
	 * See Intel 82801BA/82801BAM Specification Update, Errata #30.
	 */
	if ((sc->ident->ich >= 2 && sc->ident->ich <= 3) ||
	    (sc->ident->ich == 0 && sc->revision >= FXP_REV_82559_A0)) {
		data = sc->eeprom[FXP_EEPROM_MAP_ID];
		if (data & 0x02) {			/* STB enable */
			uint16_t cksum;
			int i;

			device_printf(dev,
			    "Disabling dynamic standby mode in EEPROM\n");
			data &= ~0x02;
			sc->eeprom[FXP_EEPROM_MAP_ID] = data;
			fxp_write_eeprom(sc, &data, FXP_EEPROM_MAP_ID, 1);
			device_printf(dev, "New EEPROM ID: 0x%x\n", data);
			cksum = 0;
			for (i = 0; i < (1 << sc->eeprom_size) - 1; i++)
				cksum += sc->eeprom[i];
			i = (1 << sc->eeprom_size) - 1;
			cksum = 0xBABA - cksum;
			fxp_write_eeprom(sc, &cksum, i, 1);
			device_printf(dev,
			    "EEPROM checksum @ 0x%x: 0x%x -> 0x%x\n",
			    i, sc->eeprom[i], cksum);
			sc->eeprom[i] = cksum;
			/*
			 * If the user elects to continue, try the software
			 * workaround, as it is better than nothing.
			 */
			sc->flags |= FXP_FLAG_CU_RESUME_BUG;
		}
	}

	/*
	 * If we are not a 82557 chip, we can enable extended features.
	 */
	if (sc->revision != FXP_REV_82557) {
		/*
		 * If MWI is enabled in the PCI configuration, and there
		 * is a valid cacheline size (8 or 16 dwords), then tell
		 * the board to turn on MWI.
		 */
		val = pci_read_config(dev, PCIR_COMMAND, 2);
		if (val & PCIM_CMD_MWRICEN &&
		    pci_read_config(dev, PCIR_CACHELNSZ, 1) != 0)
			sc->flags |= FXP_FLAG_MWI_ENABLE;

		/* turn on the extended TxCB feature */
		sc->flags |= FXP_FLAG_EXT_TXCB;

		/* enable reception of long frames for VLAN */
		sc->flags |= FXP_FLAG_LONG_PKT_EN;
	} else {
		/* a hack to get long VLAN frames on a 82557 */
		sc->flags |= FXP_FLAG_SAVE_BAD;
	}

	/* For 82559 or later chips, Rx checksum offload is supported. */
	if (sc->revision >= FXP_REV_82559_A0) {
		/* 82559ER does not support Rx checksum offloading. */
		if (sc->ident->device != 0x1209)
			sc->flags |= FXP_FLAG_82559_RXCSUM;
	}
	/*
	 * Enable use of extended RFDs and TCBs for 82550
	 * and later chips. Note: we need extended TXCB support
	 * too, but that's already enabled by the code above.
	 * Be careful to do this only on the right devices.
	 */
	if (sc->revision == FXP_REV_82550 || sc->revision == FXP_REV_82550_C ||
	    sc->revision == FXP_REV_82551_E || sc->revision == FXP_REV_82551_F
	    || sc->revision == FXP_REV_82551_10) {
		sc->rfa_size = sizeof (struct fxp_rfa);
		sc->tx_cmd = FXP_CB_COMMAND_IPCBXMIT;
		sc->flags |= FXP_FLAG_EXT_RFA;
		/* Use extended RFA instead of 82559 checksum mode. */
		sc->flags &= ~FXP_FLAG_82559_RXCSUM;
	} else {
		sc->rfa_size = sizeof (struct fxp_rfa) - FXP_RFAX_LEN;
		sc->tx_cmd = FXP_CB_COMMAND_XMIT;
	}

	/*
	 * Allocate DMA tags and DMA safe memory.
	 */
	sc->maxtxseg = FXP_NTXSEG;
	sc->maxsegsize = MCLBYTES;
	if (sc->flags & FXP_FLAG_EXT_RFA) {
		sc->maxtxseg--;
		sc->maxsegsize = FXP_TSO_SEGSIZE;
	}
	error = bus_dma_tag_create(bus_get_dma_tag(dev), 2, 0,
	    BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL,
	    sc->maxsegsize * sc->maxtxseg + sizeof(struct ether_vlan_header),
	    sc->maxtxseg, sc->maxsegsize, 0,
	    busdma_lock_mutex, &Giant, &sc->fxp_txmtag);
	if (error) {
		device_printf(dev, "could not create TX DMA tag\n");
		goto fail;
	}

	error = bus_dma_tag_create(bus_get_dma_tag(dev), 2, 0,
	    BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL,
	    MCLBYTES, 1, MCLBYTES, 0,
	    busdma_lock_mutex, &Giant, &sc->fxp_rxmtag);
	if (error) {
		device_printf(dev, "could not create RX DMA tag\n");
		goto fail;
	}

	error = bus_dma_tag_create(bus_get_dma_tag(dev), 4, 0,
	    BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL,
	    sizeof(struct fxp_stats), 1, sizeof(struct fxp_stats), 0,
	    busdma_lock_mutex, &Giant, &sc->fxp_stag);
	if (error) {
		device_printf(dev, "could not create stats DMA tag\n");
		goto fail;
	}

	error = bus_dmamem_alloc(sc->fxp_stag, (void **)&sc->fxp_stats,
	    BUS_DMA_NOWAIT | BUS_DMA_COHERENT | BUS_DMA_ZERO, &sc->fxp_smap);
	if (error) {
		device_printf(dev, "could not allocate stats DMA memory\n");
		goto fail;
	}
	error = bus_dmamap_load(sc->fxp_stag, sc->fxp_smap, sc->fxp_stats,
	    sizeof(struct fxp_stats), fxp_dma_map_addr, &sc->stats_addr,
	    BUS_DMA_NOWAIT);
	if (error) {
		device_printf(dev, "could not load the stats DMA buffer\n");
		goto fail;
	}

	error = bus_dma_tag_create(bus_get_dma_tag(dev), 4, 0,
	    BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL,
	    FXP_TXCB_SZ, 1, FXP_TXCB_SZ, 0,
	    busdma_lock_mutex, &Giant, &sc->cbl_tag);
	if (error) {
		device_printf(dev, "could not create TxCB DMA tag\n");
		goto fail;
	}

	error = bus_dmamem_alloc(sc->cbl_tag, (void **)&sc->fxp_desc.cbl_list,
	    BUS_DMA_NOWAIT | BUS_DMA_COHERENT | BUS_DMA_ZERO, &sc->cbl_map);
	if (error) {
		device_printf(dev, "could not allocate TxCB DMA memory\n");
		goto fail;
	}

	error = bus_dmamap_load(sc->cbl_tag, sc->cbl_map,
	    sc->fxp_desc.cbl_list, FXP_TXCB_SZ, fxp_dma_map_addr,
	    &sc->fxp_desc.cbl_addr, BUS_DMA_NOWAIT);
	if (error) {
		device_printf(dev, "could not load TxCB DMA buffer\n");
		goto fail;
	}

	error = bus_dma_tag_create(bus_get_dma_tag(dev), 4, 0,
	    BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL,
	    sizeof(struct fxp_cb_mcs), 1, sizeof(struct fxp_cb_mcs), 0,
	    busdma_lock_mutex, &Giant, &sc->mcs_tag);
	if (error) {
		device_printf(dev,
		    "could not create multicast setup DMA tag\n");
		goto fail;
	}

	error = bus_dmamem_alloc(sc->mcs_tag, (void **)&sc->mcsp,
	    BUS_DMA_NOWAIT | BUS_DMA_COHERENT | BUS_DMA_ZERO, &sc->mcs_map);
	if (error) {
		device_printf(dev,
		    "could not allocate multicast setup DMA memory\n");
		goto fail;
	}
	error = bus_dmamap_load(sc->mcs_tag, sc->mcs_map, sc->mcsp,
	    sizeof(struct fxp_cb_mcs), fxp_dma_map_addr, &sc->mcs_addr,
	    BUS_DMA_NOWAIT);
	if (error) {
		device_printf(dev,
		    "can't load the multicast setup DMA buffer\n");
		goto fail;
	}

	/*
	 * Pre-allocate the TX DMA maps and setup the pointers to
	 * the TX command blocks.
	 */
	txp = sc->fxp_desc.tx_list;
	tcbp = sc->fxp_desc.cbl_list;
	for (i = 0; i < FXP_NTXCB; i++) {
		txp[i].tx_cb = tcbp + i;
		error = bus_dmamap_create(sc->fxp_txmtag, 0, &txp[i].tx_map);
		if (error) {
			device_printf(dev, "can't create DMA map for TX\n");
			goto fail;
		}
	}
	error = bus_dmamap_create(sc->fxp_rxmtag, 0, &sc->spare_map);
	if (error) {
		device_printf(dev, "can't create spare DMA map\n");
		goto fail;
	}

	/*
	 * Pre-allocate our receive buffers.
	 */
	sc->fxp_desc.rx_head = sc->fxp_desc.rx_tail = NULL;
	for (i = 0; i < FXP_NRFABUFS; i++) {
		rxp = &sc->fxp_desc.rx_list[i];
		error = bus_dmamap_create(sc->fxp_rxmtag, 0, &rxp->rx_map);
		if (error) {
			device_printf(dev, "can't create DMA map for RX\n");
			goto fail;
		}
		if (fxp_new_rfabuf(sc, rxp) != 0) {
			error = ENOMEM;
			goto fail;
		}
		fxp_add_rfabuf(sc, rxp);
	}

	/*
	 * Read MAC address.
	 */
	eaddr[0] = sc->eeprom[FXP_EEPROM_MAP_IA0] & 0xff;
	eaddr[1] = sc->eeprom[FXP_EEPROM_MAP_IA0] >> 8;
	eaddr[2] = sc->eeprom[FXP_EEPROM_MAP_IA1] & 0xff;
	eaddr[3] = sc->eeprom[FXP_EEPROM_MAP_IA1] >> 8;
	eaddr[4] = sc->eeprom[FXP_EEPROM_MAP_IA2] & 0xff;
	eaddr[5] = sc->eeprom[FXP_EEPROM_MAP_IA2] >> 8;
	if (bootverbose) {
		device_printf(dev, "PCI IDs: %04x %04x %04x %04x %04x\n",
		    pci_get_vendor(dev), pci_get_device(dev),
		    pci_get_subvendor(dev), pci_get_subdevice(dev),
		    pci_get_revid(dev));
		device_printf(dev, "Dynamic Standby mode is %s\n",
		    sc->eeprom[FXP_EEPROM_MAP_ID] & 0x02 ? "enabled" :
		    "disabled");
	}

	/*
	 * If this is only a 10Mbps device, then there is no MII, and
	 * the PHY will use a serial interface instead.
	 *
	 * The Seeq 80c24 AutoDUPLEX(tm) Ethernet Interface Adapter
	 * doesn't have a programming interface of any sort.  The
	 * media is sensed automatically based on how the link partner
	 * is configured.  This is, in essence, manual configuration.
	 */
	if (sc->flags & FXP_FLAG_SERIAL_MEDIA) {
		ifmedia_add(&sc->sc_media, IFM_ETHER|IFM_MANUAL, 0, NULL);
		ifmedia_set(&sc->sc_media, IFM_ETHER|IFM_MANUAL);
	} else {
		/*
		 * i82557 wedge when isolating all of their PHYs.
		 */
		flags = MIIF_NOISOLATE;
		if (sc->revision >= FXP_REV_82558_A4)
			flags |= MIIF_DOPAUSE;
		error = mii_attach(dev, &sc->miibus, ifp,
		    (ifm_change_cb_t)fxp_ifmedia_upd,
		    (ifm_stat_cb_t)fxp_ifmedia_sts, BMSR_DEFCAPMASK,
		    MII_PHY_ANY, MII_OFFSET_ANY, flags);
		if (error != 0) {
			device_printf(dev, "attaching PHYs failed\n");
			goto fail;
		}
	}

	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	if_setdev(ifp, dev);
	if_setinitfn(ifp, fxp_init);
	if_setsoftc(ifp, sc);
	if_setflags(ifp, IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST);
	if_setioctlfn(ifp, fxp_ioctl);
	if_setstartfn(ifp, fxp_start);

	if_setcapabilities(ifp, 0);
	if_setcapenable(ifp, 0);

	/* Enable checksum offload/TSO for 82550 or better chips */
	if (sc->flags & FXP_FLAG_EXT_RFA) {
		if_sethwassist(ifp, FXP_CSUM_FEATURES | CSUM_TSO);
		if_setcapabilitiesbit(ifp, IFCAP_HWCSUM | IFCAP_TSO4, 0);
		if_setcapenablebit(ifp, IFCAP_HWCSUM | IFCAP_TSO4, 0);
	}

	if (sc->flags & FXP_FLAG_82559_RXCSUM) {
		if_setcapabilitiesbit(ifp, IFCAP_RXCSUM, 0);
		if_setcapenablebit(ifp, IFCAP_RXCSUM, 0);
	}

	if (sc->flags & FXP_FLAG_WOLCAP) {
		if_setcapabilitiesbit(ifp, IFCAP_WOL_MAGIC, 0);
		if_setcapenablebit(ifp, IFCAP_WOL_MAGIC, 0);
	}

#ifdef DEVICE_POLLING
	/* Inform the world we support polling. */
	if_setcapabilitiesbit(ifp, IFCAP_POLLING, 0);
#endif

	/*
	 * Attach the interface.
	 */
	ether_ifattach(ifp, eaddr);

	/*
	 * Tell the upper layer(s) we support long frames.
	 * Must appear after the call to ether_ifattach() because
	 * ether_ifattach() sets ifi_hdrlen to the default value.
	 */
	if_setifheaderlen(ifp, sizeof(struct ether_vlan_header));
	if_setcapabilitiesbit(ifp, IFCAP_VLAN_MTU, 0);
	if_setcapenablebit(ifp, IFCAP_VLAN_MTU, 0);
	if ((sc->flags & FXP_FLAG_EXT_RFA) != 0) {
		if_setcapabilitiesbit(ifp, IFCAP_VLAN_HWTAGGING |
		    IFCAP_VLAN_HWCSUM | IFCAP_VLAN_HWTSO, 0);
		if_setcapenablebit(ifp, IFCAP_VLAN_HWTAGGING |
		    IFCAP_VLAN_HWCSUM | IFCAP_VLAN_HWTSO, 0);
	}

	/*
	 * Let the system queue as many packets as we have available
	 * TX descriptors.
	 */
	if_setsendqlen(ifp, FXP_NTXCB - 1);
	if_setsendqready(ifp);

	/*
	 * Hook our interrupt after all initialization is complete.
	 */
	error = bus_setup_intr(dev, sc->fxp_res[1], INTR_TYPE_NET | INTR_MPSAFE,
			       NULL, fxp_intr, sc, &sc->ih);
	if (error) {
		device_printf(dev, "could not setup irq\n");
		ether_ifdetach(sc->ifp);
		goto fail;
	}

	/*
	 * Configure hardware to reject magic frames otherwise
	 * system will hang on recipt of magic frames.
	 */
	if ((sc->flags & FXP_FLAG_WOLCAP) != 0) {
		FXP_LOCK(sc);
		/* Clear wakeup events. */
		CSR_WRITE_1(sc, FXP_CSR_PMDR, CSR_READ_1(sc, FXP_CSR_PMDR));
		fxp_init_body(sc, 0);
		fxp_stop(sc);
		FXP_UNLOCK(sc);
	}

fail:
	if (error)
		fxp_release(sc);
	return (error);
}