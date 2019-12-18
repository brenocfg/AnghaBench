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
typedef  int /*<<< orphan*/  uint32_t ;
struct mii_data {int /*<<< orphan*/  mii_media; } ;
struct mgb_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/ * pba; int /*<<< orphan*/  miibus; int /*<<< orphan*/  ctx; } ;
struct mgb_ring_desc {int dummy; } ;
struct ether_addr {int /*<<< orphan*/  octet; } ;
typedef  TYPE_1__* if_softc_ctx_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
struct TYPE_3__ {int* isc_txqsizes; int* isc_ntxd; int* isc_rxqsizes; int* isc_nrxd; int isc_nrxqsets; int isc_ntxqsets; int isc_capabilities; int isc_capenable; int isc_msix_bar; int /*<<< orphan*/ * isc_media; scalar_t__ isc_tx_csum_flags; int /*<<< orphan*/  isc_tx_nsegments; int /*<<< orphan*/ * isc_txrx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int /*<<< orphan*/  CSR_WRITE_REG (struct mgb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 scalar_t__ ETHER_IS_BROADCAST (int /*<<< orphan*/ ) ; 
 scalar_t__ ETHER_IS_MULTICAST (int /*<<< orphan*/ ) ; 
 scalar_t__ ETHER_IS_ZERO (int /*<<< orphan*/ ) ; 
 int IFCAP_JUMBO_MTU ; 
 int IFCAP_LRO ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_RXCSUM_IPV6 ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TSO6 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_TXCSUM_IPV6 ; 
 int IFCAP_VLAN_HWCSUM ; 
 int IFCAP_VLAN_HWFILTER ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_VLAN_HWTSO ; 
 int IFCAP_VLAN_MTU ; 
 int /*<<< orphan*/  MGB_DMA_MAXSEGS ; 
 int /*<<< orphan*/  MGB_INTR_VEC_OTHER_MAP ; 
 int /*<<< orphan*/  MGB_INTR_VEC_RX_MAP ; 
 int /*<<< orphan*/  MGB_INTR_VEC_TX_MAP ; 
#define  MGB_LAN7430_DEVICE_ID 129 
#define  MGB_LAN7431_DEVICE_ID 128 
 int /*<<< orphan*/  MIIF_DOPAUSE ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int MII_PHY_ANY ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ether_gen_addr (int /*<<< orphan*/ ,struct ether_addr*) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct mgb_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 TYPE_1__* iflib_get_softc_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_set_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mgb_alloc_regs (struct mgb_softc*) ; 
 int /*<<< orphan*/  mgb_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgb_get_ethaddr (struct mgb_softc*,struct ether_addr*) ; 
 int mgb_hw_init (struct mgb_softc*) ; 
 int /*<<< orphan*/  mgb_media_change ; 
 int /*<<< orphan*/  mgb_media_status ; 
 int mgb_test_bar (struct mgb_softc*) ; 
 int /*<<< orphan*/  mgb_txrx ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_msix_pba_bar (int /*<<< orphan*/ ) ; 
 int pci_msix_table_bar (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mgb_attach_pre(if_ctx_t ctx)
{
	struct mgb_softc *sc;
	if_softc_ctx_t scctx;
	int error, phyaddr, rid;
	struct ether_addr hwaddr;
	struct mii_data *miid;

	sc = iflib_get_softc(ctx);
	sc->ctx = ctx;
	sc->dev = iflib_get_dev(ctx);
	scctx = iflib_get_softc_ctx(ctx);

	/* IFLIB required setup */
	scctx->isc_txrx = &mgb_txrx;
	scctx->isc_tx_nsegments = MGB_DMA_MAXSEGS;
	/* Ring desc queues */
	scctx->isc_txqsizes[0] = sizeof(struct mgb_ring_desc) *
	    scctx->isc_ntxd[0];
	scctx->isc_rxqsizes[0] = sizeof(struct mgb_ring_desc) *
	    scctx->isc_nrxd[0];

	/* Head WB queues */
	scctx->isc_txqsizes[1] = sizeof(uint32_t) * scctx->isc_ntxd[1];
	scctx->isc_rxqsizes[1] = sizeof(uint32_t) * scctx->isc_nrxd[1];

	/* XXX: Must have 1 txqset, but can have up to 4 rxqsets */
	scctx->isc_nrxqsets = 1;
	scctx->isc_ntxqsets = 1;

	/* scctx->isc_tx_csum_flags = (CSUM_TCP | CSUM_UDP) |
	    (CSUM_TCP_IPV6 | CSUM_UDP_IPV6) | CSUM_TSO */
	scctx->isc_tx_csum_flags = 0;
	scctx->isc_capabilities = scctx->isc_capenable = 0;
#if 0
	/*
	 * CSUM, TSO and VLAN support are TBD
	 */
	    IFCAP_TXCSUM | IFCAP_TXCSUM_IPV6 |
	    IFCAP_TSO4 | IFCAP_TSO6 |
	    IFCAP_RXCSUM | IFCAP_RXCSUM_IPV6 |
	    IFCAP_VLAN_MTU | IFCAP_VLAN_HWTAGGING |
	    IFCAP_VLAN_HWCSUM | IFCAP_VLAN_HWTSO |
	    IFCAP_JUMBO_MTU;
	scctx->isc_capabilities |= IFCAP_LRO | IFCAP_VLAN_HWFILTER;
#endif

	/* get the BAR */
	error = mgb_alloc_regs(sc);
	if (error != 0) {
		device_printf(sc->dev,
		    "Unable to allocate bus resource: registers.\n");
		goto fail;
	}

	error = mgb_test_bar(sc);
	if (error != 0)
		goto fail;

	error = mgb_hw_init(sc);
	if (error != 0) {
		device_printf(sc->dev,
		    "MGB device init failed. (err: %d)\n", error);
		goto fail;
	}

	switch (pci_get_device(sc->dev))
	{
	case MGB_LAN7430_DEVICE_ID:
		phyaddr = 1;
		break;
	case MGB_LAN7431_DEVICE_ID:
	default:
		phyaddr = MII_PHY_ANY;
		break;
	}

	/* XXX: Would be nice(r) if locked methods were here */
	error = mii_attach(sc->dev, &sc->miibus, iflib_get_ifp(ctx),
	    mgb_media_change, mgb_media_status,
	    BMSR_DEFCAPMASK, phyaddr, MII_OFFSET_ANY, MIIF_DOPAUSE);
	if (error != 0) {
		device_printf(sc->dev, "Failed to attach MII interface\n");
		goto fail;
	}

	miid = device_get_softc(sc->miibus);
	scctx->isc_media = &miid->mii_media;

	scctx->isc_msix_bar = pci_msix_table_bar(sc->dev);
	/** Setup PBA BAR **/
	rid = pci_msix_pba_bar(sc->dev);
	if (rid != scctx->isc_msix_bar) {
		sc->pba = bus_alloc_resource_any(sc->dev, SYS_RES_MEMORY,
		    &rid, RF_ACTIVE);
		if (sc->pba == NULL) {
			error = ENXIO;
			device_printf(sc->dev, "Failed to setup PBA BAR\n");
			goto fail;
		}
	}

	mgb_get_ethaddr(sc, &hwaddr);
	if (ETHER_IS_BROADCAST(hwaddr.octet) ||
	    ETHER_IS_MULTICAST(hwaddr.octet) ||
	    ETHER_IS_ZERO(hwaddr.octet))
		ether_gen_addr(iflib_get_ifp(ctx), &hwaddr);

	/*
	 * XXX: if the MAC address was generated the linux driver
	 * writes it back to the device.
	 */
	iflib_set_mac(ctx, hwaddr.octet);

	/* Map all vectors to vector 0 (admin interrupts) by default. */
	CSR_WRITE_REG(sc, MGB_INTR_VEC_RX_MAP, 0);
	CSR_WRITE_REG(sc, MGB_INTR_VEC_TX_MAP, 0);
	CSR_WRITE_REG(sc, MGB_INTR_VEC_OTHER_MAP, 0);

	return (0);

fail:
	mgb_detach(ctx);
	return (error);
}