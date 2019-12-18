#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u_int32_t ;
struct mrsas_softc {int max_num_sge; int io_frames_alloc_sz; int chain_frames_alloc_sz; scalar_t__ msix_vectors; int reply_alloc_sz; int max_fw_cmds; int /*<<< orphan*/  mrsas_dev; int /*<<< orphan*/ * data_tag; int /*<<< orphan*/  io_lock; int /*<<< orphan*/ * mrsas_parent_tag; int /*<<< orphan*/  pd_info_phys_addr; int /*<<< orphan*/  pd_info_mem; int /*<<< orphan*/  pd_info_dmamap; int /*<<< orphan*/ * pd_info_tag; int /*<<< orphan*/  evt_detail_phys_addr; int /*<<< orphan*/  evt_detail_mem; int /*<<< orphan*/  evt_detail_dmamap; int /*<<< orphan*/ * evt_detail_tag; int /*<<< orphan*/  sense_phys_addr; int /*<<< orphan*/  sense_mem; int /*<<< orphan*/  sense_dmamap; int /*<<< orphan*/ * sense_tag; int /*<<< orphan*/  reply_desc_phys_addr; int /*<<< orphan*/  reply_desc_mem; int /*<<< orphan*/  reply_desc_dmamap; int /*<<< orphan*/ * reply_desc_tag; int /*<<< orphan*/  chain_frame_phys_addr; int /*<<< orphan*/  chain_frame_mem; int /*<<< orphan*/  chain_frame_dmamap; int /*<<< orphan*/ * chain_frame_tag; int /*<<< orphan*/  io_request_phys_addr; int /*<<< orphan*/  io_request_mem; int /*<<< orphan*/  io_request_dmamap; int /*<<< orphan*/ * io_request_tag; int /*<<< orphan*/  verbuf_phys_addr; int /*<<< orphan*/  verbuf_mem; int /*<<< orphan*/  verbuf_dmamap; int /*<<< orphan*/ * verbuf_tag; } ;
struct mrsas_pd_info {int dummy; } ;
struct mrsas_evt_detail {int dummy; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int ENOMEM ; 
 int MAXPHYS ; 
 int MRSAS_MAX_NAME_LENGTH ; 
 int MRSAS_SENSE_LEN ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ bus_dmamap_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * busdma_lock_mutex ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrsas_addr_cb ; 

__attribute__((used)) static int
mrsas_alloc_mem(struct mrsas_softc *sc)
{
	u_int32_t verbuf_size, io_req_size, reply_desc_size, sense_size, chain_frame_size,
		evt_detail_size, count, pd_info_size;

	/*
	 * Allocate parent DMA tag
	 */
	if (bus_dma_tag_create(NULL,	/* parent */
	    1,				/* alignment */
	    0,				/* boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MAXPHYS,			/* maxsize */
	    sc->max_num_sge,		/* nsegments */
	    MAXPHYS,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->mrsas_parent_tag	/* tag */
	    )) {
		device_printf(sc->mrsas_dev, "Cannot allocate parent DMA tag\n");
		return (ENOMEM);
	}
	/*
	 * Allocate for version buffer
	 */
	verbuf_size = MRSAS_MAX_NAME_LENGTH * (sizeof(bus_addr_t));
	if (bus_dma_tag_create(sc->mrsas_parent_tag,
	    1, 0,
	    BUS_SPACE_MAXADDR_32BIT,
	    BUS_SPACE_MAXADDR,
	    NULL, NULL,
	    verbuf_size,
	    1,
	    verbuf_size,
	    BUS_DMA_ALLOCNOW,
	    NULL, NULL,
	    &sc->verbuf_tag)) {
		device_printf(sc->mrsas_dev, "Cannot allocate verbuf DMA tag\n");
		return (ENOMEM);
	}
	if (bus_dmamem_alloc(sc->verbuf_tag, (void **)&sc->verbuf_mem,
	    BUS_DMA_NOWAIT, &sc->verbuf_dmamap)) {
		device_printf(sc->mrsas_dev, "Cannot allocate verbuf memory\n");
		return (ENOMEM);
	}
	bzero(sc->verbuf_mem, verbuf_size);
	if (bus_dmamap_load(sc->verbuf_tag, sc->verbuf_dmamap, sc->verbuf_mem,
	    verbuf_size, mrsas_addr_cb, &sc->verbuf_phys_addr,
	    BUS_DMA_NOWAIT)) {
		device_printf(sc->mrsas_dev, "Cannot load verbuf DMA map\n");
		return (ENOMEM);
	}
	/*
	 * Allocate IO Request Frames
	 */
	io_req_size = sc->io_frames_alloc_sz;
	if (bus_dma_tag_create(sc->mrsas_parent_tag,
	    16, 0,
	    BUS_SPACE_MAXADDR_32BIT,
	    BUS_SPACE_MAXADDR,
	    NULL, NULL,
	    io_req_size,
	    1,
	    io_req_size,
	    BUS_DMA_ALLOCNOW,
	    NULL, NULL,
	    &sc->io_request_tag)) {
		device_printf(sc->mrsas_dev, "Cannot create IO request tag\n");
		return (ENOMEM);
	}
	if (bus_dmamem_alloc(sc->io_request_tag, (void **)&sc->io_request_mem,
	    BUS_DMA_NOWAIT, &sc->io_request_dmamap)) {
		device_printf(sc->mrsas_dev, "Cannot alloc IO request memory\n");
		return (ENOMEM);
	}
	bzero(sc->io_request_mem, io_req_size);
	if (bus_dmamap_load(sc->io_request_tag, sc->io_request_dmamap,
	    sc->io_request_mem, io_req_size, mrsas_addr_cb,
	    &sc->io_request_phys_addr, BUS_DMA_NOWAIT)) {
		device_printf(sc->mrsas_dev, "Cannot load IO request memory\n");
		return (ENOMEM);
	}
	/*
	 * Allocate Chain Frames
	 */
	chain_frame_size = sc->chain_frames_alloc_sz;
	if (bus_dma_tag_create(sc->mrsas_parent_tag,
	    4, 0,
	    BUS_SPACE_MAXADDR_32BIT,
	    BUS_SPACE_MAXADDR,
	    NULL, NULL,
	    chain_frame_size,
	    1,
	    chain_frame_size,
	    BUS_DMA_ALLOCNOW,
	    NULL, NULL,
	    &sc->chain_frame_tag)) {
		device_printf(sc->mrsas_dev, "Cannot create chain frame tag\n");
		return (ENOMEM);
	}
	if (bus_dmamem_alloc(sc->chain_frame_tag, (void **)&sc->chain_frame_mem,
	    BUS_DMA_NOWAIT, &sc->chain_frame_dmamap)) {
		device_printf(sc->mrsas_dev, "Cannot alloc chain frame memory\n");
		return (ENOMEM);
	}
	bzero(sc->chain_frame_mem, chain_frame_size);
	if (bus_dmamap_load(sc->chain_frame_tag, sc->chain_frame_dmamap,
	    sc->chain_frame_mem, chain_frame_size, mrsas_addr_cb,
	    &sc->chain_frame_phys_addr, BUS_DMA_NOWAIT)) {
		device_printf(sc->mrsas_dev, "Cannot load chain frame memory\n");
		return (ENOMEM);
	}
	count = sc->msix_vectors > 0 ? sc->msix_vectors : 1;
	/*
	 * Allocate Reply Descriptor Array
	 */
	reply_desc_size = sc->reply_alloc_sz * count;
	if (bus_dma_tag_create(sc->mrsas_parent_tag,
	    16, 0,
	    BUS_SPACE_MAXADDR_32BIT,
	    BUS_SPACE_MAXADDR,
	    NULL, NULL,
	    reply_desc_size,
	    1,
	    reply_desc_size,
	    BUS_DMA_ALLOCNOW,
	    NULL, NULL,
	    &sc->reply_desc_tag)) {
		device_printf(sc->mrsas_dev, "Cannot create reply descriptor tag\n");
		return (ENOMEM);
	}
	if (bus_dmamem_alloc(sc->reply_desc_tag, (void **)&sc->reply_desc_mem,
	    BUS_DMA_NOWAIT, &sc->reply_desc_dmamap)) {
		device_printf(sc->mrsas_dev, "Cannot alloc reply descriptor memory\n");
		return (ENOMEM);
	}
	if (bus_dmamap_load(sc->reply_desc_tag, sc->reply_desc_dmamap,
	    sc->reply_desc_mem, reply_desc_size, mrsas_addr_cb,
	    &sc->reply_desc_phys_addr, BUS_DMA_NOWAIT)) {
		device_printf(sc->mrsas_dev, "Cannot load reply descriptor memory\n");
		return (ENOMEM);
	}
	/*
	 * Allocate Sense Buffer Array.  Keep in lower 4GB
	 */
	sense_size = sc->max_fw_cmds * MRSAS_SENSE_LEN;
	if (bus_dma_tag_create(sc->mrsas_parent_tag,
	    64, 0,
	    BUS_SPACE_MAXADDR_32BIT,
	    BUS_SPACE_MAXADDR,
	    NULL, NULL,
	    sense_size,
	    1,
	    sense_size,
	    BUS_DMA_ALLOCNOW,
	    NULL, NULL,
	    &sc->sense_tag)) {
		device_printf(sc->mrsas_dev, "Cannot allocate sense buf tag\n");
		return (ENOMEM);
	}
	if (bus_dmamem_alloc(sc->sense_tag, (void **)&sc->sense_mem,
	    BUS_DMA_NOWAIT, &sc->sense_dmamap)) {
		device_printf(sc->mrsas_dev, "Cannot allocate sense buf memory\n");
		return (ENOMEM);
	}
	if (bus_dmamap_load(sc->sense_tag, sc->sense_dmamap,
	    sc->sense_mem, sense_size, mrsas_addr_cb, &sc->sense_phys_addr,
	    BUS_DMA_NOWAIT)) {
		device_printf(sc->mrsas_dev, "Cannot load sense buf memory\n");
		return (ENOMEM);
	}

	/*
	 * Allocate for Event detail structure
	 */
	evt_detail_size = sizeof(struct mrsas_evt_detail);
	if (bus_dma_tag_create(sc->mrsas_parent_tag,
	    1, 0,
	    BUS_SPACE_MAXADDR_32BIT,
	    BUS_SPACE_MAXADDR,
	    NULL, NULL,
	    evt_detail_size,
	    1,
	    evt_detail_size,
	    BUS_DMA_ALLOCNOW,
	    NULL, NULL,
	    &sc->evt_detail_tag)) {
		device_printf(sc->mrsas_dev, "Cannot create Event detail tag\n");
		return (ENOMEM);
	}
	if (bus_dmamem_alloc(sc->evt_detail_tag, (void **)&sc->evt_detail_mem,
	    BUS_DMA_NOWAIT, &sc->evt_detail_dmamap)) {
		device_printf(sc->mrsas_dev, "Cannot alloc Event detail buffer memory\n");
		return (ENOMEM);
	}
	bzero(sc->evt_detail_mem, evt_detail_size);
	if (bus_dmamap_load(sc->evt_detail_tag, sc->evt_detail_dmamap,
	    sc->evt_detail_mem, evt_detail_size, mrsas_addr_cb,
	    &sc->evt_detail_phys_addr, BUS_DMA_NOWAIT)) {
		device_printf(sc->mrsas_dev, "Cannot load Event detail buffer memory\n");
		return (ENOMEM);
	}

	/*
	 * Allocate for PD INFO structure
	 */
	pd_info_size = sizeof(struct mrsas_pd_info);
	if (bus_dma_tag_create(sc->mrsas_parent_tag,
	    1, 0,
	    BUS_SPACE_MAXADDR_32BIT,
	    BUS_SPACE_MAXADDR,
	    NULL, NULL,
	    pd_info_size,
	    1,
	    pd_info_size,
	    BUS_DMA_ALLOCNOW,
	    NULL, NULL,
	    &sc->pd_info_tag)) {
		device_printf(sc->mrsas_dev, "Cannot create PD INFO tag\n");
		return (ENOMEM);
	}
	if (bus_dmamem_alloc(sc->pd_info_tag, (void **)&sc->pd_info_mem,
	    BUS_DMA_NOWAIT, &sc->pd_info_dmamap)) {
		device_printf(sc->mrsas_dev, "Cannot alloc PD INFO buffer memory\n");
		return (ENOMEM);
	}
	bzero(sc->pd_info_mem, pd_info_size);
	if (bus_dmamap_load(sc->pd_info_tag, sc->pd_info_dmamap,
	    sc->pd_info_mem, pd_info_size, mrsas_addr_cb,
	    &sc->pd_info_phys_addr, BUS_DMA_NOWAIT)) {
		device_printf(sc->mrsas_dev, "Cannot load PD INFO buffer memory\n");
		return (ENOMEM);
	}

	/*
	 * Create a dma tag for data buffers; size will be the maximum
	 * possible I/O size (280kB).
	 */
	if (bus_dma_tag_create(sc->mrsas_parent_tag,
	    1,
	    0,
	    BUS_SPACE_MAXADDR,
	    BUS_SPACE_MAXADDR,
	    NULL, NULL,
	    MAXPHYS,
	    sc->max_num_sge,		/* nsegments */
	    MAXPHYS,
	    BUS_DMA_ALLOCNOW,
	    busdma_lock_mutex,
	    &sc->io_lock,
	    &sc->data_tag)) {
		device_printf(sc->mrsas_dev, "Cannot create data dma tag\n");
		return (ENOMEM);
	}
	return (0);
}