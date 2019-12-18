#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct mbuf {int dummy; } ;
struct ether_vlan_header {int dummy; } ;
typedef  TYPE_2__* iflib_txq_t ;
typedef  TYPE_3__* if_softc_ctx_t ;
typedef  TYPE_4__* if_shared_ctx_t ;
typedef  TYPE_5__* if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bus_size_t ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
struct TYPE_10__ {int isc_tx_nsegments; int isc_tx_tso_segments_max; scalar_t__ isc_tx_tso_size_max; int* isc_ntxd; } ;
struct TYPE_12__ {int /*<<< orphan*/  ifc_ifp; int /*<<< orphan*/  ifc_dev; TYPE_3__ ifc_softc_ctx; TYPE_4__* ifc_sctx; } ;
struct TYPE_11__ {scalar_t__ isc_tso_maxsize; scalar_t__ isc_tx_maxsize; scalar_t__ isc_tso_maxsegsize; scalar_t__ isc_tx_maxsegsize; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ifsd_tso_map; int /*<<< orphan*/ * ifsd_map; struct mbuf** ifsd_m; } ;
struct TYPE_9__ {size_t ift_br_offset; TYPE_1__ ift_sds; int /*<<< orphan*/  ift_tso_buf_tag; int /*<<< orphan*/  ift_buf_tag; TYPE_5__* ift_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int ENOMEM ; 
 int IFCAP_TSO ; 
 int IFCAP_VLAN_MTU ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_IFLIB ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int if_getcapabilities (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_tx_structures_free (TYPE_5__*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iflib_txsd_alloc(iflib_txq_t txq)
{
	if_ctx_t ctx = txq->ift_ctx;
	if_shared_ctx_t sctx = ctx->ifc_sctx;
	if_softc_ctx_t scctx = &ctx->ifc_softc_ctx;
	device_t dev = ctx->ifc_dev;
	bus_size_t tsomaxsize;
	int err, nsegments, ntsosegments;
	bool tso;

	nsegments = scctx->isc_tx_nsegments;
	ntsosegments = scctx->isc_tx_tso_segments_max;
	tsomaxsize = scctx->isc_tx_tso_size_max;
	if (if_getcapabilities(ctx->ifc_ifp) & IFCAP_VLAN_MTU)
		tsomaxsize += sizeof(struct ether_vlan_header);
	MPASS(scctx->isc_ntxd[0] > 0);
	MPASS(scctx->isc_ntxd[txq->ift_br_offset] > 0);
	MPASS(nsegments > 0);
	if (if_getcapabilities(ctx->ifc_ifp) & IFCAP_TSO) {
		MPASS(ntsosegments > 0);
		MPASS(sctx->isc_tso_maxsize >= tsomaxsize);
	}

	/*
	 * Set up DMA tags for TX buffers.
	 */
	if ((err = bus_dma_tag_create(bus_get_dma_tag(dev),
			       1, 0,			/* alignment, bounds */
			       BUS_SPACE_MAXADDR,	/* lowaddr */
			       BUS_SPACE_MAXADDR,	/* highaddr */
			       NULL, NULL,		/* filter, filterarg */
			       sctx->isc_tx_maxsize,		/* maxsize */
			       nsegments,	/* nsegments */
			       sctx->isc_tx_maxsegsize,	/* maxsegsize */
			       0,			/* flags */
			       NULL,			/* lockfunc */
			       NULL,			/* lockfuncarg */
			       &txq->ift_buf_tag))) {
		device_printf(dev,"Unable to allocate TX DMA tag: %d\n", err);
		device_printf(dev,"maxsize: %ju nsegments: %d maxsegsize: %ju\n",
		    (uintmax_t)sctx->isc_tx_maxsize, nsegments, (uintmax_t)sctx->isc_tx_maxsegsize);
		goto fail;
	}
	tso = (if_getcapabilities(ctx->ifc_ifp) & IFCAP_TSO) != 0;
	if (tso && (err = bus_dma_tag_create(bus_get_dma_tag(dev),
			       1, 0,			/* alignment, bounds */
			       BUS_SPACE_MAXADDR,	/* lowaddr */
			       BUS_SPACE_MAXADDR,	/* highaddr */
			       NULL, NULL,		/* filter, filterarg */
			       tsomaxsize,		/* maxsize */
			       ntsosegments,	/* nsegments */
			       sctx->isc_tso_maxsegsize,/* maxsegsize */
			       0,			/* flags */
			       NULL,			/* lockfunc */
			       NULL,			/* lockfuncarg */
			       &txq->ift_tso_buf_tag))) {
		device_printf(dev, "Unable to allocate TSO TX DMA tag: %d\n",
		    err);
		goto fail;
	}

	/* Allocate memory for the TX mbuf map. */
	if (!(txq->ift_sds.ifsd_m =
	    (struct mbuf **) malloc(sizeof(struct mbuf *) *
	    scctx->isc_ntxd[txq->ift_br_offset], M_IFLIB, M_NOWAIT | M_ZERO))) {
		device_printf(dev, "Unable to allocate TX mbuf map memory\n");
		err = ENOMEM;
		goto fail;
	}

	/*
	 * Create the DMA maps for TX buffers.
	 */
	if ((txq->ift_sds.ifsd_map = (bus_dmamap_t *)malloc(
	    sizeof(bus_dmamap_t) * scctx->isc_ntxd[txq->ift_br_offset],
	    M_IFLIB, M_NOWAIT | M_ZERO)) == NULL) {
		device_printf(dev,
		    "Unable to allocate TX buffer DMA map memory\n");
		err = ENOMEM;
		goto fail;
	}
	if (tso && (txq->ift_sds.ifsd_tso_map = (bus_dmamap_t *)malloc(
	    sizeof(bus_dmamap_t) * scctx->isc_ntxd[txq->ift_br_offset],
	    M_IFLIB, M_NOWAIT | M_ZERO)) == NULL) {
		device_printf(dev,
		    "Unable to allocate TSO TX buffer map memory\n");
		err = ENOMEM;
		goto fail;
	}
	for (int i = 0; i < scctx->isc_ntxd[txq->ift_br_offset]; i++) {
		err = bus_dmamap_create(txq->ift_buf_tag, 0,
		    &txq->ift_sds.ifsd_map[i]);
		if (err != 0) {
			device_printf(dev, "Unable to create TX DMA map\n");
			goto fail;
		}
		if (!tso)
			continue;
		err = bus_dmamap_create(txq->ift_tso_buf_tag, 0,
		    &txq->ift_sds.ifsd_tso_map[i]);
		if (err != 0) {
			device_printf(dev, "Unable to create TSO TX DMA map\n");
			goto fail;
		}
	}
	return (0);
fail:
	/* We free all, it handles case where we are in the middle */
	iflib_tx_structures_free(ctx);
	return (err);
}