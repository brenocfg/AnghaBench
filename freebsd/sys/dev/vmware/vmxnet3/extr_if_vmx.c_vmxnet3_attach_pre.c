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
typedef  int uint32_t ;
struct vmxnet3_txdesc {int dummy; } ;
struct vmxnet3_txcompdesc {int dummy; } ;
struct vmxnet3_softc {int vmx_intr_mask_mode; int /*<<< orphan*/  vmx_lladdr; TYPE_1__* vmx_scctx; int /*<<< orphan*/  vmx_media; int /*<<< orphan*/  vmx_ifp; int /*<<< orphan*/  vmx_sctx; int /*<<< orphan*/  vmx_ctx; int /*<<< orphan*/  vmx_dev; } ;
struct vmxnet3_rxdesc {int dummy; } ;
struct vmxnet3_rxcompdesc {int dummy; } ;
typedef  TYPE_1__* if_softc_ctx_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {scalar_t__ isc_nrxqsets; scalar_t__ isc_ntxqsets; int* isc_ntxd; int* isc_txqsizes; int* isc_nrxd; int* isc_rxqsizes; int isc_msix_bar; int isc_disable_msix; int isc_capabilities; int isc_capenable; int /*<<< orphan*/  isc_tx_csum_flags; int /*<<< orphan*/  isc_rss_table_size; void* isc_ntxqsets_max; void* isc_nrxqsets_max; int /*<<< orphan*/ * isc_txrx; int /*<<< orphan*/  isc_tx_tso_segsize_max; int /*<<< orphan*/  isc_tx_tso_size_max; void* isc_tx_tso_segments_max; void* isc_tx_nsegments; } ;

/* Variables and functions */
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
 int /*<<< orphan*/  UPT1_RSS_MAX_IND_TABLE_SIZE ; 
 int /*<<< orphan*/  VMXNET3_CMD_GET_INTRCFG ; 
 int /*<<< orphan*/  VMXNET3_CSUM_ALL_OFFLOAD ; 
 scalar_t__ VMXNET3_DEF_RX_QUEUES ; 
 scalar_t__ VMXNET3_DEF_TX_QUEUES ; 
#define  VMXNET3_IT_AUTO 131 
#define  VMXNET3_IT_LEGACY 130 
#define  VMXNET3_IT_MSI 129 
#define  VMXNET3_IT_MSIX 128 
 int /*<<< orphan*/  VMXNET3_MAX_RX_QUEUES ; 
 int /*<<< orphan*/  VMXNET3_MAX_TX_QUEUES ; 
 int /*<<< orphan*/  VMXNET3_TSO_MAXSIZE ; 
 void* VMXNET3_TX_MAXSEGS ; 
 int /*<<< orphan*/  VMXNET3_TX_MAXSEGSIZE ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_ifp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_media (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_sctx (int /*<<< orphan*/ ) ; 
 struct vmxnet3_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 TYPE_1__* iflib_get_softc_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_set_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_ncpus ; 
 int pci_msix_table_bar (int /*<<< orphan*/ ) ; 
 int vmxnet3_alloc_resources (struct vmxnet3_softc*) ; 
 int vmxnet3_check_version (struct vmxnet3_softc*) ; 
 int /*<<< orphan*/  vmxnet3_free_resources (struct vmxnet3_softc*) ; 
 int /*<<< orphan*/  vmxnet3_get_lladdr (struct vmxnet3_softc*) ; 
 int vmxnet3_read_cmd (struct vmxnet3_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmxnet3_txrx ; 

__attribute__((used)) static int
vmxnet3_attach_pre(if_ctx_t ctx)
{
	device_t dev;
	if_softc_ctx_t scctx;
	struct vmxnet3_softc *sc;
	uint32_t intr_config;
	int error;

	dev = iflib_get_dev(ctx);
	sc = iflib_get_softc(ctx);
	sc->vmx_dev = dev;
	sc->vmx_ctx = ctx;
	sc->vmx_sctx = iflib_get_sctx(ctx);
	sc->vmx_scctx = iflib_get_softc_ctx(ctx);
	sc->vmx_ifp = iflib_get_ifp(ctx);
	sc->vmx_media = iflib_get_media(ctx);
	scctx = sc->vmx_scctx;

	scctx->isc_tx_nsegments = VMXNET3_TX_MAXSEGS;
	scctx->isc_tx_tso_segments_max = VMXNET3_TX_MAXSEGS;
	/* isc_tx_tso_size_max doesn't include possible vlan header */
	scctx->isc_tx_tso_size_max = VMXNET3_TSO_MAXSIZE;
	scctx->isc_tx_tso_segsize_max = VMXNET3_TX_MAXSEGSIZE;
	scctx->isc_txrx = &vmxnet3_txrx;

	/* If 0, the iflib tunable was not set, so set to the default */
	if (scctx->isc_nrxqsets == 0)
		scctx->isc_nrxqsets = VMXNET3_DEF_RX_QUEUES;
	scctx->isc_nrxqsets_max = min(VMXNET3_MAX_RX_QUEUES, mp_ncpus);

	/* If 0, the iflib tunable was not set, so set to the default */
	if (scctx->isc_ntxqsets == 0)
		scctx->isc_ntxqsets = VMXNET3_DEF_TX_QUEUES;
	scctx->isc_ntxqsets_max = min(VMXNET3_MAX_TX_QUEUES, mp_ncpus);

	/*
	 * Enforce that the transmit completion queue descriptor count is
	 * the same as the transmit command queue descriptor count.
	 */
	scctx->isc_ntxd[0] = scctx->isc_ntxd[1];
	scctx->isc_txqsizes[0] =
	    sizeof(struct vmxnet3_txcompdesc) * scctx->isc_ntxd[0];
	scctx->isc_txqsizes[1] =
	    sizeof(struct vmxnet3_txdesc) * scctx->isc_ntxd[1];

	/*
	 * Enforce that the receive completion queue descriptor count is the
	 * sum of the receive command queue descriptor counts, and that the
	 * second receive command queue descriptor count is the same as the
	 * first one.
	 */
	scctx->isc_nrxd[2] = scctx->isc_nrxd[1];
	scctx->isc_nrxd[0] = scctx->isc_nrxd[1] + scctx->isc_nrxd[2];
	scctx->isc_rxqsizes[0] =
	    sizeof(struct vmxnet3_rxcompdesc) * scctx->isc_nrxd[0];
	scctx->isc_rxqsizes[1] =
	    sizeof(struct vmxnet3_rxdesc) * scctx->isc_nrxd[1];
	scctx->isc_rxqsizes[2] =
	    sizeof(struct vmxnet3_rxdesc) * scctx->isc_nrxd[2];

	scctx->isc_rss_table_size = UPT1_RSS_MAX_IND_TABLE_SIZE;

	/* Map PCI BARs */
	error = vmxnet3_alloc_resources(sc);
	if (error)
		goto fail;

	/* Check device versions */
	error = vmxnet3_check_version(sc);
	if (error)
		goto fail;

	/* 
	 * The interrupt mode can be set in the hypervisor configuration via
	 * the parameter ethernet<N>.intrMode.
	 */
	intr_config = vmxnet3_read_cmd(sc, VMXNET3_CMD_GET_INTRCFG);
	sc->vmx_intr_mask_mode = (intr_config >> 2) & 0x03;

	/*
	 * Configure the softc context to attempt to configure the interrupt
	 * mode now indicated by intr_config.  iflib will follow the usual
	 * fallback path MSI-X -> MSI -> LEGACY, starting at the configured
	 * starting mode.
	 */
	switch (intr_config & 0x03) {
	case VMXNET3_IT_AUTO:
	case VMXNET3_IT_MSIX:
		scctx->isc_msix_bar = pci_msix_table_bar(dev);
		break;
	case VMXNET3_IT_MSI:
		scctx->isc_msix_bar = -1;
		scctx->isc_disable_msix = 1;
		break;
	case VMXNET3_IT_LEGACY:
		scctx->isc_msix_bar = 0;
		break;
	}

	scctx->isc_tx_csum_flags = VMXNET3_CSUM_ALL_OFFLOAD;
	scctx->isc_capabilities = scctx->isc_capenable =
	    IFCAP_TXCSUM | IFCAP_TXCSUM_IPV6 |
	    IFCAP_TSO4 | IFCAP_TSO6 |
	    IFCAP_RXCSUM | IFCAP_RXCSUM_IPV6 |
	    IFCAP_VLAN_MTU | IFCAP_VLAN_HWTAGGING |
	    IFCAP_VLAN_HWCSUM | IFCAP_VLAN_HWTSO |
	    IFCAP_JUMBO_MTU;

	/* These capabilities are not enabled by default. */
	scctx->isc_capabilities |= IFCAP_LRO | IFCAP_VLAN_HWFILTER;

	vmxnet3_get_lladdr(sc);
	iflib_set_mac(ctx, sc->vmx_lladdr);

	return (0);
fail:
	/*
	 * We must completely clean up anything allocated above as iflib
	 * will not invoke any other driver entry points as a result of this
	 * failure.
	 */
	vmxnet3_free_resources(sc);

	return (error);
}