#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rt_softc_rx_ring {int qid; int /*<<< orphan*/  desc_dma_map; int /*<<< orphan*/  desc_dma_tag; int /*<<< orphan*/  spare_dma_map; int /*<<< orphan*/  data_dma_tag; struct rt_softc_rx_data* data; struct rt_rxdesc* desc; int /*<<< orphan*/  desc_phys_addr; } ;
struct rt_softc_rx_data {TYPE_3__* m; int /*<<< orphan*/  dma_map; } ;
struct rt_softc {int /*<<< orphan*/  dev; } ;
struct rt_rxdesc {void* sdl0; void* sdp0; } ;
struct TYPE_7__ {scalar_t__ ds_len; scalar_t__ ds_addr; } ;
typedef  TYPE_2__ bus_dma_segment_t ;
struct TYPE_6__ {int len; } ;
struct TYPE_8__ {int m_len; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int BUS_DMA_NOWAIT ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MJUMPAGESIZE ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int RT_SOFTC_RX_RING_DATA_COUNT ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rt_rxdesc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_dmamap_load_mbuf_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,TYPE_2__*,int*,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 void* htole32 (scalar_t__) ; 
 TYPE_3__* m_getjcl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt_dma_map_addr ; 
 int /*<<< orphan*/  rt_free_rx_ring (struct rt_softc*,struct rt_softc_rx_ring*) ; 

__attribute__((used)) static int
rt_alloc_rx_ring(struct rt_softc *sc, struct rt_softc_rx_ring *ring, int qid)
{
	struct rt_rxdesc *desc;
	struct rt_softc_rx_data *data;
	bus_dma_segment_t segs[1];
	int i, nsegs, error;

	error = bus_dma_tag_create(bus_get_dma_tag(sc->dev), PAGE_SIZE, 0,
		BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL,
		RT_SOFTC_RX_RING_DATA_COUNT * sizeof(struct rt_rxdesc), 1,
		RT_SOFTC_RX_RING_DATA_COUNT * sizeof(struct rt_rxdesc),
		0, NULL, NULL, &ring->desc_dma_tag);
	if (error != 0)	{
		device_printf(sc->dev,
		    "could not create Rx desc DMA tag\n");
		goto fail;
	}

	error = bus_dmamem_alloc(ring->desc_dma_tag, (void **) &ring->desc,
	    BUS_DMA_NOWAIT | BUS_DMA_ZERO, &ring->desc_dma_map);
	if (error != 0) {
		device_printf(sc->dev,
		    "could not allocate Rx desc DMA memory\n");
		goto fail;
	}

	error = bus_dmamap_load(ring->desc_dma_tag, ring->desc_dma_map,
		ring->desc,
		RT_SOFTC_RX_RING_DATA_COUNT * sizeof(struct rt_rxdesc),
		rt_dma_map_addr, &ring->desc_phys_addr, 0);
	if (error != 0) {
		device_printf(sc->dev, "could not load Rx desc DMA map\n");
		goto fail;
	}

	error = bus_dma_tag_create(bus_get_dma_tag(sc->dev), PAGE_SIZE, 0,
	    BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL,
		MJUMPAGESIZE, 1, MJUMPAGESIZE, 0, NULL, NULL,
		&ring->data_dma_tag);
	if (error != 0)	{
		device_printf(sc->dev,
		    "could not create Rx data DMA tag\n");
		goto fail;
	}

	for (i = 0; i < RT_SOFTC_RX_RING_DATA_COUNT; i++) {
		desc = &ring->desc[i];
		data = &ring->data[i];

		error = bus_dmamap_create(ring->data_dma_tag, 0,
		    &data->dma_map);
		if (error != 0)	{
			device_printf(sc->dev, "could not create Rx data DMA "
			    "map\n");
			goto fail;
		}

		data->m = m_getjcl(M_NOWAIT, MT_DATA, M_PKTHDR,
		    MJUMPAGESIZE);
		if (data->m == NULL) {
			device_printf(sc->dev, "could not allocate Rx mbuf\n");
			error = ENOMEM;
			goto fail;
		}

		data->m->m_len = data->m->m_pkthdr.len = MJUMPAGESIZE;

		error = bus_dmamap_load_mbuf_sg(ring->data_dma_tag,
		    data->dma_map, data->m, segs, &nsegs, BUS_DMA_NOWAIT);
		if (error != 0)	{
			device_printf(sc->dev,
			    "could not load Rx mbuf DMA map\n");
			goto fail;
		}

		KASSERT(nsegs == 1, ("%s: too many DMA segments",
			device_get_nameunit(sc->dev)));

		/* Add 2 for proper align of RX IP header */
		desc->sdp0 = htole32(segs[0].ds_addr+2);
		desc->sdl0 = htole32(segs[0].ds_len-2);
	}

	error = bus_dmamap_create(ring->data_dma_tag, 0,
	    &ring->spare_dma_map);
	if (error != 0) {
		device_printf(sc->dev,
		    "could not create Rx spare DMA map\n");
		goto fail;
	}

	bus_dmamap_sync(ring->desc_dma_tag, ring->desc_dma_map,
		BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
	ring->qid = qid;
	return (0);

fail:
	rt_free_rx_ring(sc, ring);
	return (error);
}