#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int mask; int max_desc; TYPE_1__* info; int /*<<< orphan*/  dmat; int /*<<< orphan*/ * seg_list; void* req_bytes; int /*<<< orphan*/ * req_list; } ;
struct TYPE_14__ {int mask; int /*<<< orphan*/  extra_map; int /*<<< orphan*/  dmat; TYPE_5__* info; void* shadow; } ;
struct TYPE_12__ {int mask; int /*<<< orphan*/  extra_map; int /*<<< orphan*/  dmat; TYPE_3__* info; void* shadow; } ;
struct TYPE_10__ {int mask; } ;
struct mxge_slice_state {TYPE_7__ tx; TYPE_8__* sc; TYPE_6__ rx_big; TYPE_4__ rx_small; TYPE_2__ rx_done; } ;
struct TYPE_16__ {int tx_boundary; int /*<<< orphan*/  dev; int /*<<< orphan*/  parent_dmat; struct mxge_slice_state* ss; } ;
typedef  TYPE_8__ mxge_softc_t ;
typedef  int /*<<< orphan*/  mcp_kreq_ether_send_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;
struct TYPE_13__ {int /*<<< orphan*/  map; } ;
struct TYPE_11__ {int /*<<< orphan*/  map; } ;
struct TYPE_9__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int MHLEN ; 
 int MIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MJUM9BYTES ; 
 int /*<<< orphan*/  MXGE_MAX_SEND_DESC ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,...) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 void* malloc (size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mxge_alloc_slice_rings(struct mxge_slice_state *ss, int rx_ring_entries,
		       int tx_ring_entries)
{
	mxge_softc_t *sc = ss->sc;
	size_t bytes;
	int err, i;

	/* allocate per-slice receive resources */

	ss->rx_small.mask = ss->rx_big.mask = rx_ring_entries - 1;
	ss->rx_done.mask = (2 * rx_ring_entries) - 1;

	/* allocate the rx shadow rings */
	bytes = rx_ring_entries * sizeof (*ss->rx_small.shadow);
	ss->rx_small.shadow = malloc(bytes, M_DEVBUF, M_ZERO|M_WAITOK);

	bytes = rx_ring_entries * sizeof (*ss->rx_big.shadow);
	ss->rx_big.shadow = malloc(bytes, M_DEVBUF, M_ZERO|M_WAITOK);

	/* allocate the rx host info rings */
	bytes = rx_ring_entries * sizeof (*ss->rx_small.info);
	ss->rx_small.info = malloc(bytes, M_DEVBUF, M_ZERO|M_WAITOK);

	bytes = rx_ring_entries * sizeof (*ss->rx_big.info);
	ss->rx_big.info = malloc(bytes, M_DEVBUF, M_ZERO|M_WAITOK);

	/* allocate the rx busdma resources */
	err = bus_dma_tag_create(sc->parent_dmat,	/* parent */
				 1,			/* alignment */
				 4096,			/* boundary */
				 BUS_SPACE_MAXADDR,	/* low */
				 BUS_SPACE_MAXADDR,	/* high */
				 NULL, NULL,		/* filter */
				 MHLEN,			/* maxsize */
				 1,			/* num segs */
				 MHLEN,			/* maxsegsize */
				 BUS_DMA_ALLOCNOW,	/* flags */
				 NULL, NULL,		/* lock */
				 &ss->rx_small.dmat);	/* tag */
	if (err != 0) {
		device_printf(sc->dev, "Err %d allocating rx_small dmat\n",
			      err);
		return err;
	}

	err = bus_dma_tag_create(sc->parent_dmat,	/* parent */
				 1,			/* alignment */
#if MXGE_VIRT_JUMBOS
				 4096,			/* boundary */
#else
				 0,			/* boundary */
#endif
				 BUS_SPACE_MAXADDR,	/* low */
				 BUS_SPACE_MAXADDR,	/* high */
				 NULL, NULL,		/* filter */
				 3*4096,		/* maxsize */
#if MXGE_VIRT_JUMBOS
				 3,			/* num segs */
				 4096,			/* maxsegsize*/
#else
				 1,			/* num segs */
				 MJUM9BYTES,		/* maxsegsize*/
#endif
				 BUS_DMA_ALLOCNOW,	/* flags */
				 NULL, NULL,		/* lock */
				 &ss->rx_big.dmat);	/* tag */
	if (err != 0) {
		device_printf(sc->dev, "Err %d allocating rx_big dmat\n",
			      err);
		return err;
	}
	for (i = 0; i <= ss->rx_small.mask; i++) {
		err = bus_dmamap_create(ss->rx_small.dmat, 0,
					&ss->rx_small.info[i].map);
		if (err != 0) {
			device_printf(sc->dev, "Err %d  rx_small dmamap\n",
				      err);
			return err;
		}
	}
	err = bus_dmamap_create(ss->rx_small.dmat, 0,
				&ss->rx_small.extra_map);
	if (err != 0) {
		device_printf(sc->dev, "Err %d extra rx_small dmamap\n",
			      err);
		return err;
	}

	for (i = 0; i <= ss->rx_big.mask; i++) {
		err = bus_dmamap_create(ss->rx_big.dmat, 0,
					&ss->rx_big.info[i].map);
		if (err != 0) {
			device_printf(sc->dev, "Err %d  rx_big dmamap\n",
				      err);
			return err;
		}
	}
	err = bus_dmamap_create(ss->rx_big.dmat, 0,
				&ss->rx_big.extra_map);
	if (err != 0) {
		device_printf(sc->dev, "Err %d extra rx_big dmamap\n",
			      err);
		return err;
	}

	/* now allocate TX resources */

#ifndef IFNET_BUF_RING
	/* only use a single TX ring for now */
	if (ss != ss->sc->ss)
		return 0;
#endif

	ss->tx.mask = tx_ring_entries - 1;
	ss->tx.max_desc = MIN(MXGE_MAX_SEND_DESC, tx_ring_entries / 4);

	
	/* allocate the tx request copy block */
	bytes = 8 +
		sizeof (*ss->tx.req_list) * (ss->tx.max_desc + 4);
	ss->tx.req_bytes = malloc(bytes, M_DEVBUF, M_WAITOK);
	/* ensure req_list entries are aligned to 8 bytes */
	ss->tx.req_list = (mcp_kreq_ether_send_t *)
		((unsigned long)(ss->tx.req_bytes + 7) & ~7UL);

	/* allocate the tx busdma segment list */
	bytes = sizeof (*ss->tx.seg_list) * ss->tx.max_desc;
	ss->tx.seg_list = (bus_dma_segment_t *)
		malloc(bytes, M_DEVBUF, M_WAITOK);

	/* allocate the tx host info ring */
	bytes = tx_ring_entries * sizeof (*ss->tx.info);
	ss->tx.info = malloc(bytes, M_DEVBUF, M_ZERO|M_WAITOK);
	
	/* allocate the tx busdma resources */
	err = bus_dma_tag_create(sc->parent_dmat,	/* parent */
				 1,			/* alignment */
				 sc->tx_boundary,	/* boundary */
				 BUS_SPACE_MAXADDR,	/* low */
				 BUS_SPACE_MAXADDR,	/* high */
				 NULL, NULL,		/* filter */
				 65536 + 256,		/* maxsize */
				 ss->tx.max_desc - 2,	/* num segs */
				 sc->tx_boundary,	/* maxsegsz */
				 BUS_DMA_ALLOCNOW,	/* flags */
				 NULL, NULL,		/* lock */
				 &ss->tx.dmat);		/* tag */
	
	if (err != 0) {
		device_printf(sc->dev, "Err %d allocating tx dmat\n",
			      err);
		return err;
	}

	/* now use these tags to setup dmamaps for each slot
	   in the ring */
	for (i = 0; i <= ss->tx.mask; i++) {
		err = bus_dmamap_create(ss->tx.dmat, 0,
					&ss->tx.info[i].map);
		if (err != 0) {
			device_printf(sc->dev, "Err %d  tx dmamap\n",
				      err);
			return err;
		}
	}
	return 0;

}