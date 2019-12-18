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
typedef  int uint32_t ;
struct TYPE_5__ {int ifq_drv_maxlen; } ;
struct ifnet {int if_flags; void* sc_control_data; scalar_t__ sc_cddma; int sc_rxdptr; int sc_flags; scalar_t__ sc_variant; int if_hdrlen; int /*<<< orphan*/ * sc_tq; int /*<<< orphan*/  sc_pdmatag; int /*<<< orphan*/  sc_rdmatag; int /*<<< orphan*/  sc_tdmatag; int /*<<< orphan*/  sc_cdmatag; int /*<<< orphan*/  sc_cddmamap; struct cas_txsoft* sc_txsoft; TYPE_1__* sc_rxdsoft; int /*<<< orphan*/  if_capabilities; int /*<<< orphan*/  if_capenable; int /*<<< orphan*/  if_hwassist; int /*<<< orphan*/  sc_enaddr; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_miibus; int /*<<< orphan*/  sc_mii; int /*<<< orphan*/  sc_txfreeq; int /*<<< orphan*/  sc_txdirtyq; int /*<<< orphan*/  sc_tx_task; int /*<<< orphan*/  sc_intr_task; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_rx_ch; int /*<<< orphan*/  sc_tick_ch; TYPE_2__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_start; struct ifnet* if_softc; struct ifnet* sc_ifp; } ;
struct ether_vlan_header {int dummy; } ;
struct cas_txsoft {int /*<<< orphan*/ * txs_dmamap; scalar_t__ txs_ndescs; int /*<<< orphan*/ * txs_mbuf; } ;
struct cas_softc {int if_flags; void* sc_control_data; scalar_t__ sc_cddma; int sc_rxdptr; int sc_flags; scalar_t__ sc_variant; int if_hdrlen; int /*<<< orphan*/ * sc_tq; int /*<<< orphan*/  sc_pdmatag; int /*<<< orphan*/  sc_rdmatag; int /*<<< orphan*/  sc_tdmatag; int /*<<< orphan*/  sc_cdmatag; int /*<<< orphan*/  sc_cddmamap; struct cas_txsoft* sc_txsoft; TYPE_1__* sc_rxdsoft; int /*<<< orphan*/  if_capabilities; int /*<<< orphan*/  if_capenable; int /*<<< orphan*/  if_hwassist; int /*<<< orphan*/  sc_enaddr; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_miibus; int /*<<< orphan*/  sc_mii; int /*<<< orphan*/  sc_txfreeq; int /*<<< orphan*/  sc_txdirtyq; int /*<<< orphan*/  sc_tx_task; int /*<<< orphan*/  sc_intr_task; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_rx_ch; int /*<<< orphan*/  sc_tick_ch; TYPE_2__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_start; struct cas_softc* if_softc; struct cas_softc* sc_ifp; } ;
struct cas_control_data {int dummy; } ;
struct TYPE_4__ {void* rxds_buf; scalar_t__ rxds_paddr; int /*<<< orphan*/  rxds_dmamap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int BUS_SPACE_MAXSIZE ; 
 int /*<<< orphan*/  CAS_BARRIER (struct ifnet*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CAS_CSUM_FEATURES ; 
 int /*<<< orphan*/  CAS_MIF_CONF ; 
 int CAS_MIF_CONF_MDI0 ; 
 int CAS_MIF_CONF_MDI1 ; 
 int CAS_MIF_CONF_PHY_SELECT ; 
 int CAS_NO_CSUM ; 
 int CAS_NRXDESC ; 
 int CAS_NTXSEGS ; 
 int CAS_PAGE_SIZE ; 
 int /*<<< orphan*/  CAS_PCS_CONF ; 
 int CAS_PCS_CONF_EN ; 
 int /*<<< orphan*/  CAS_PCS_DATAPATH ; 
 int CAS_PCS_DATAPATH_MII ; 
 int CAS_PCS_DATAPATH_SERDES ; 
 int /*<<< orphan*/  CAS_PCS_SERDES_CTRL ; 
 int CAS_PCS_SERDES_CTRL_ESD ; 
 int /*<<< orphan*/  CAS_PHYAD_EXTERNAL ; 
 int CAS_READ_4 (struct ifnet*,int /*<<< orphan*/ ) ; 
 int CAS_RX_FIFO_SIZE ; 
 scalar_t__ CAS_SATURN ; 
 int /*<<< orphan*/  CAS_SATURN_PCFG ; 
 int CAS_SATURN_PCFG_FSI ; 
 int CAS_SERDES ; 
 int CAS_TXQUEUELEN ; 
 int CAS_TX_DESC_ALIGN ; 
 int /*<<< orphan*/  CAS_TX_FIFO_SIZE ; 
 int /*<<< orphan*/  CAS_WRITE_4 (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int ENXIO ; 
 int /*<<< orphan*/  IFCAP_HWCSUM ; 
 int /*<<< orphan*/  IFCAP_VLAN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_2__*,int) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_2__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int MCLBYTES ; 
 int /*<<< orphan*/  MIIF_DOPAUSE ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MII_PHY_ANY ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cas_txsoft*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct ifnet*) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cas_cddma_callback ; 
 int /*<<< orphan*/  cas_init ; 
 int /*<<< orphan*/  cas_intr_task ; 
 int /*<<< orphan*/  cas_ioctl ; 
 int /*<<< orphan*/  cas_mediachange ; 
 int /*<<< orphan*/  cas_mediastatus ; 
 int /*<<< orphan*/  cas_mifinit (struct ifnet*) ; 
 int /*<<< orphan*/  cas_reset (struct ifnet*) ; 
 int /*<<< orphan*/  cas_rxdma_callback ; 
 int /*<<< orphan*/  cas_start ; 
 int /*<<< orphan*/  cas_tx_task ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ ) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * taskqueue_create_fast (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 
 int taskqueue_start_threads (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 
 int /*<<< orphan*/  txs_q ; 

__attribute__((used)) static int
cas_attach(struct cas_softc *sc)
{
	struct cas_txsoft *txs;
	struct ifnet *ifp;
	int error, i;
	uint32_t v;

	/* Set up ifnet structure. */
	ifp = sc->sc_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL)
		return (ENOSPC);
	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(sc->sc_dev),
	    device_get_unit(sc->sc_dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_start = cas_start;
	ifp->if_ioctl = cas_ioctl;
	ifp->if_init = cas_init;
	IFQ_SET_MAXLEN(&ifp->if_snd, CAS_TXQUEUELEN);
	ifp->if_snd.ifq_drv_maxlen = CAS_TXQUEUELEN;
	IFQ_SET_READY(&ifp->if_snd);

	callout_init_mtx(&sc->sc_tick_ch, &sc->sc_mtx, 0);
	callout_init_mtx(&sc->sc_rx_ch, &sc->sc_mtx, 0);
	/* Create local taskq. */
	TASK_INIT(&sc->sc_intr_task, 0, cas_intr_task, sc);
	TASK_INIT(&sc->sc_tx_task, 1, cas_tx_task, ifp);
	sc->sc_tq = taskqueue_create_fast("cas_taskq", M_WAITOK,
	    taskqueue_thread_enqueue, &sc->sc_tq);
	if (sc->sc_tq == NULL) {
		device_printf(sc->sc_dev, "could not create taskqueue\n");
		error = ENXIO;
		goto fail_ifnet;
	}
	error = taskqueue_start_threads(&sc->sc_tq, 1, PI_NET, "%s taskq",
	    device_get_nameunit(sc->sc_dev));
	if (error != 0) {
		device_printf(sc->sc_dev, "could not start threads\n");
		goto fail_taskq;
	}

	/* Make sure the chip is stopped. */
	cas_reset(sc);

	error = bus_dma_tag_create(bus_get_dma_tag(sc->sc_dev), 1, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL,
	    BUS_SPACE_MAXSIZE, 0, BUS_SPACE_MAXSIZE, 0, NULL, NULL,
	    &sc->sc_pdmatag);
	if (error != 0)
		goto fail_taskq;

	error = bus_dma_tag_create(sc->sc_pdmatag, 1, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL,
	    CAS_PAGE_SIZE, 1, CAS_PAGE_SIZE, 0, NULL, NULL, &sc->sc_rdmatag);
	if (error != 0)
		goto fail_ptag;

	error = bus_dma_tag_create(sc->sc_pdmatag, 1, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL,
	    MCLBYTES * CAS_NTXSEGS, CAS_NTXSEGS, MCLBYTES,
	    BUS_DMA_ALLOCNOW, NULL, NULL, &sc->sc_tdmatag);
	if (error != 0)
		goto fail_rtag;

	error = bus_dma_tag_create(sc->sc_pdmatag, CAS_TX_DESC_ALIGN, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL,
	    sizeof(struct cas_control_data), 1,
	    sizeof(struct cas_control_data), 0,
	    NULL, NULL, &sc->sc_cdmatag);
	if (error != 0)
		goto fail_ttag;

	/*
	 * Allocate the control data structures, create and load the
	 * DMA map for it.
	 */
	if ((error = bus_dmamem_alloc(sc->sc_cdmatag,
	    (void **)&sc->sc_control_data,
	    BUS_DMA_WAITOK | BUS_DMA_COHERENT | BUS_DMA_ZERO,
	    &sc->sc_cddmamap)) != 0) {
		device_printf(sc->sc_dev,
		    "unable to allocate control data, error = %d\n", error);
		goto fail_ctag;
	}

	sc->sc_cddma = 0;
	if ((error = bus_dmamap_load(sc->sc_cdmatag, sc->sc_cddmamap,
	    sc->sc_control_data, sizeof(struct cas_control_data),
	    cas_cddma_callback, sc, 0)) != 0 || sc->sc_cddma == 0) {
		device_printf(sc->sc_dev,
		    "unable to load control data DMA map, error = %d\n",
		    error);
		goto fail_cmem;
	}

	/*
	 * Initialize the transmit job descriptors.
	 */
	STAILQ_INIT(&sc->sc_txfreeq);
	STAILQ_INIT(&sc->sc_txdirtyq);

	/*
	 * Create the transmit buffer DMA maps.
	 */
	error = ENOMEM;
	for (i = 0; i < CAS_TXQUEUELEN; i++) {
		txs = &sc->sc_txsoft[i];
		txs->txs_mbuf = NULL;
		txs->txs_ndescs = 0;
		if ((error = bus_dmamap_create(sc->sc_tdmatag, 0,
		    &txs->txs_dmamap)) != 0) {
			device_printf(sc->sc_dev,
			    "unable to create TX DMA map %d, error = %d\n",
			    i, error);
			goto fail_txd;
		}
		STAILQ_INSERT_TAIL(&sc->sc_txfreeq, txs, txs_q);
	}

	/*
	 * Allocate the receive buffers, create and load the DMA maps
	 * for them.
	 */
	for (i = 0; i < CAS_NRXDESC; i++) {
		if ((error = bus_dmamem_alloc(sc->sc_rdmatag,
		    &sc->sc_rxdsoft[i].rxds_buf, BUS_DMA_WAITOK,
		    &sc->sc_rxdsoft[i].rxds_dmamap)) != 0) {
			device_printf(sc->sc_dev,
			    "unable to allocate RX buffer %d, error = %d\n",
			    i, error);
			goto fail_rxmem;
		}

		sc->sc_rxdptr = i;
		sc->sc_rxdsoft[i].rxds_paddr = 0;
		if ((error = bus_dmamap_load(sc->sc_rdmatag,
		    sc->sc_rxdsoft[i].rxds_dmamap, sc->sc_rxdsoft[i].rxds_buf,
		    CAS_PAGE_SIZE, cas_rxdma_callback, sc, 0)) != 0 ||
		    sc->sc_rxdsoft[i].rxds_paddr == 0) {
			device_printf(sc->sc_dev,
			    "unable to load RX DMA map %d, error = %d\n",
			    i, error);
			goto fail_rxmap;
		}
	}

	if ((sc->sc_flags & CAS_SERDES) == 0) {
		CAS_WRITE_4(sc, CAS_PCS_DATAPATH, CAS_PCS_DATAPATH_MII);
		CAS_BARRIER(sc, CAS_PCS_DATAPATH, 4,
		    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
		cas_mifinit(sc);
		/*
		 * Look for an external PHY.
		 */
		error = ENXIO;
		v = CAS_READ_4(sc, CAS_MIF_CONF);
		if ((v & CAS_MIF_CONF_MDI1) != 0) {
			v |= CAS_MIF_CONF_PHY_SELECT;
			CAS_WRITE_4(sc, CAS_MIF_CONF, v);
			CAS_BARRIER(sc, CAS_MIF_CONF, 4,
			    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
			/* Enable/unfreeze the GMII pins of Saturn. */
			if (sc->sc_variant == CAS_SATURN) {
				CAS_WRITE_4(sc, CAS_SATURN_PCFG,
				    CAS_READ_4(sc, CAS_SATURN_PCFG) &
				    ~CAS_SATURN_PCFG_FSI);
				CAS_BARRIER(sc, CAS_SATURN_PCFG, 4,
				    BUS_SPACE_BARRIER_READ |
				    BUS_SPACE_BARRIER_WRITE);
				DELAY(10000);
			}
			error = mii_attach(sc->sc_dev, &sc->sc_miibus, ifp,
			    cas_mediachange, cas_mediastatus, BMSR_DEFCAPMASK,
			    MII_PHY_ANY, MII_OFFSET_ANY, MIIF_DOPAUSE);
		}
		/*
		 * Fall back on an internal PHY if no external PHY was found.
		 */
		if (error != 0 && (v & CAS_MIF_CONF_MDI0) != 0) {
			v &= ~CAS_MIF_CONF_PHY_SELECT;
			CAS_WRITE_4(sc, CAS_MIF_CONF, v);
			CAS_BARRIER(sc, CAS_MIF_CONF, 4,
			    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
			/* Freeze the GMII pins of Saturn for saving power. */
			if (sc->sc_variant == CAS_SATURN) {
				CAS_WRITE_4(sc, CAS_SATURN_PCFG,
				    CAS_READ_4(sc, CAS_SATURN_PCFG) |
				    CAS_SATURN_PCFG_FSI);
				CAS_BARRIER(sc, CAS_SATURN_PCFG, 4,
				    BUS_SPACE_BARRIER_READ |
				    BUS_SPACE_BARRIER_WRITE);
				DELAY(10000);
			}
			error = mii_attach(sc->sc_dev, &sc->sc_miibus, ifp,
			    cas_mediachange, cas_mediastatus, BMSR_DEFCAPMASK,
			    MII_PHY_ANY, MII_OFFSET_ANY, MIIF_DOPAUSE);
		}
	} else {
		/*
		 * Use the external PCS SERDES.
		 */
		CAS_WRITE_4(sc, CAS_PCS_DATAPATH, CAS_PCS_DATAPATH_SERDES);
		CAS_BARRIER(sc, CAS_PCS_DATAPATH, 4, BUS_SPACE_BARRIER_WRITE);
		/* Enable/unfreeze the SERDES pins of Saturn. */
		if (sc->sc_variant == CAS_SATURN) {
			CAS_WRITE_4(sc, CAS_SATURN_PCFG, 0);
			CAS_BARRIER(sc, CAS_SATURN_PCFG, 4,
			    BUS_SPACE_BARRIER_WRITE);
		}
		CAS_WRITE_4(sc, CAS_PCS_SERDES_CTRL, CAS_PCS_SERDES_CTRL_ESD);
		CAS_BARRIER(sc, CAS_PCS_SERDES_CTRL, 4,
		    BUS_SPACE_BARRIER_WRITE);
		CAS_WRITE_4(sc, CAS_PCS_CONF, CAS_PCS_CONF_EN);
		CAS_BARRIER(sc, CAS_PCS_CONF, 4,
		    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
		error = mii_attach(sc->sc_dev, &sc->sc_miibus, ifp,
		    cas_mediachange, cas_mediastatus, BMSR_DEFCAPMASK,
		    CAS_PHYAD_EXTERNAL, MII_OFFSET_ANY, MIIF_DOPAUSE);
	}
	if (error != 0) {
		device_printf(sc->sc_dev, "attaching PHYs failed\n");
		goto fail_rxmap;
	}
	sc->sc_mii = device_get_softc(sc->sc_miibus);

	/*
	 * From this point forward, the attachment cannot fail.  A failure
	 * before this point releases all resources that may have been
	 * allocated.
	 */

	/* Announce FIFO sizes. */
	v = CAS_READ_4(sc, CAS_TX_FIFO_SIZE);
	device_printf(sc->sc_dev, "%ukB RX FIFO, %ukB TX FIFO\n",
	    CAS_RX_FIFO_SIZE / 1024, v / 16);

	/* Attach the interface. */
	ether_ifattach(ifp, sc->sc_enaddr);

	/*
	 * Tell the upper layer(s) we support long frames/checksum offloads.
	 */
	ifp->if_hdrlen = sizeof(struct ether_vlan_header);
	ifp->if_capabilities = IFCAP_VLAN_MTU;
	if ((sc->sc_flags & CAS_NO_CSUM) == 0) {
		ifp->if_capabilities |= IFCAP_HWCSUM;
		ifp->if_hwassist = CAS_CSUM_FEATURES;
	}
	ifp->if_capenable = ifp->if_capabilities;

	return (0);

	/*
	 * Free any resources we've allocated during the failed attach
	 * attempt.  Do this in reverse order and fall through.
	 */
 fail_rxmap:
	for (i = 0; i < CAS_NRXDESC; i++)
		if (sc->sc_rxdsoft[i].rxds_paddr != 0)
			bus_dmamap_unload(sc->sc_rdmatag,
			    sc->sc_rxdsoft[i].rxds_dmamap);
 fail_rxmem:
	for (i = 0; i < CAS_NRXDESC; i++)
		if (sc->sc_rxdsoft[i].rxds_buf != NULL)
			bus_dmamem_free(sc->sc_rdmatag,
			    sc->sc_rxdsoft[i].rxds_buf,
			    sc->sc_rxdsoft[i].rxds_dmamap);
 fail_txd:
	for (i = 0; i < CAS_TXQUEUELEN; i++)
		if (sc->sc_txsoft[i].txs_dmamap != NULL)
			bus_dmamap_destroy(sc->sc_tdmatag,
			    sc->sc_txsoft[i].txs_dmamap);
	bus_dmamap_unload(sc->sc_cdmatag, sc->sc_cddmamap);
 fail_cmem:
	bus_dmamem_free(sc->sc_cdmatag, sc->sc_control_data,
	    sc->sc_cddmamap);
 fail_ctag:
	bus_dma_tag_destroy(sc->sc_cdmatag);
 fail_ttag:
	bus_dma_tag_destroy(sc->sc_tdmatag);
 fail_rtag:
	bus_dma_tag_destroy(sc->sc_rdmatag);
 fail_ptag:
	bus_dma_tag_destroy(sc->sc_pdmatag);
 fail_taskq:
	taskqueue_free(sc->sc_tq);
 fail_ifnet:
	if_free(ifp);
	return (error);
}