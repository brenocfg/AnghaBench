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
struct twa_softc {int /*<<< orphan*/  dma_tag; struct tw_osli_req_context* req_ctx_buf; int /*<<< orphan*/  ioctl_map; int /*<<< orphan*/  ioctl_tag; int /*<<< orphan*/ * io_lock; int /*<<< orphan*/  alignment; int /*<<< orphan*/  parent_tag; int /*<<< orphan*/  dma_mem_phys; int /*<<< orphan*/  dma_mem; int /*<<< orphan*/  cmd_map; int /*<<< orphan*/  cmd_tag; int /*<<< orphan*/  bus_dev; int /*<<< orphan*/ * non_dma_mem; int /*<<< orphan*/  sg_size_factor; int /*<<< orphan*/  device_id; int /*<<< orphan*/  flags; int /*<<< orphan*/  ctlr_handle; } ;
struct tw_osli_req_context {int /*<<< orphan*/ * ioctl_wake_timeout_lock; int /*<<< orphan*/  ioctl_wake_timeout_lock_handle; int /*<<< orphan*/  dma_map; struct twa_softc* ctlr; } ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;
typedef  int TW_UINT32 ;
typedef  int TW_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int BUS_SPACE_MAXSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TW_CL_64BIT_ADDRESSES ; 
 int /*<<< orphan*/  TW_CL_64BIT_SG_LENGTH ; 
 int TW_CL_MAX_32BIT_SG_ELEMENTS ; 
 int TW_CL_MAX_64BIT_SG_ELEMENTS ; 
 int TW_CL_MAX_IO_SIZE ; 
 int /*<<< orphan*/  TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER ; 
 int /*<<< orphan*/  TW_CL_SEVERITY_ERROR_STRING ; 
 int /*<<< orphan*/  TW_OSLI_BUSY_Q ; 
 int /*<<< orphan*/  TW_OSLI_DMA_BOUNDARY ; 
 int /*<<< orphan*/  TW_OSLI_FREE_Q ; 
 int /*<<< orphan*/  TW_OSLI_MALLOC_CLASS ; 
 int /*<<< orphan*/  TW_OSLI_MAX_NUM_AENS ; 
 int TW_OSLI_MAX_NUM_REQUESTS ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct tw_osli_req_context*,int) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tw_cl_get_mem_requirements (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  tw_osli_dbg_dprintf (int,struct twa_softc*,char*) ; 
 int /*<<< orphan*/  tw_osli_printf (struct twa_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,...) ; 
 int /*<<< orphan*/  tw_osli_req_q_init (struct twa_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_osli_req_q_insert_tail (struct tw_osli_req_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * twa_busdma_lock ; 
 int /*<<< orphan*/  twa_map_load_callback ; 

__attribute__((used)) static TW_INT32
tw_osli_alloc_mem(struct twa_softc *sc)
{
	struct tw_osli_req_context	*req;
	TW_UINT32			max_sg_elements;
	TW_UINT32			non_dma_mem_size;
	TW_UINT32			dma_mem_size;
	TW_INT32			error;
	TW_INT32			i;

	tw_osli_dbg_dprintf(3, sc, "entered");

	sc->flags |= (sizeof(bus_addr_t) == 8) ? TW_CL_64BIT_ADDRESSES : 0;
	sc->flags |= (sizeof(bus_size_t) == 8) ? TW_CL_64BIT_SG_LENGTH : 0;

	max_sg_elements = (sizeof(bus_addr_t) == 8) ?
		TW_CL_MAX_64BIT_SG_ELEMENTS : TW_CL_MAX_32BIT_SG_ELEMENTS;

	if ((error = tw_cl_get_mem_requirements(&sc->ctlr_handle, sc->flags,
			sc->device_id, TW_OSLI_MAX_NUM_REQUESTS,  TW_OSLI_MAX_NUM_AENS,
			&(sc->alignment), &(sc->sg_size_factor),
			&non_dma_mem_size, &dma_mem_size
			))) {
		tw_osli_printf(sc, "error = %d",
			TW_CL_SEVERITY_ERROR_STRING,
			TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
			0x2008,
			"Can't get Common Layer's memory requirements",
			error);
		return(error);
	}

	if ((sc->non_dma_mem = malloc(non_dma_mem_size, TW_OSLI_MALLOC_CLASS,
				M_WAITOK)) == NULL) {
		tw_osli_printf(sc, "error = %d",
			TW_CL_SEVERITY_ERROR_STRING,
			TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
			0x2009,
			"Can't allocate non-dma memory",
			ENOMEM);
		return(ENOMEM);
	}

	/* Create the parent dma tag. */
	if (bus_dma_tag_create(bus_get_dma_tag(sc->bus_dev), /* parent */
				sc->alignment,		/* alignment */
				TW_OSLI_DMA_BOUNDARY,	/* boundary */
				BUS_SPACE_MAXADDR,	/* lowaddr */
				BUS_SPACE_MAXADDR, 	/* highaddr */
				NULL, NULL, 		/* filter, filterarg */
				TW_CL_MAX_IO_SIZE,	/* maxsize */
				max_sg_elements,	/* nsegments */
				TW_CL_MAX_IO_SIZE,	/* maxsegsize */
				0,			/* flags */
				NULL,			/* lockfunc */
				NULL,			/* lockfuncarg */
				&sc->parent_tag		/* tag */)) {
		tw_osli_printf(sc, "error = %d",
			TW_CL_SEVERITY_ERROR_STRING,
			TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
			0x200A,
			"Can't allocate parent DMA tag",
			ENOMEM);
		return(ENOMEM);
	}

	/* Create a dma tag for Common Layer's DMA'able memory (dma_mem). */
	if (bus_dma_tag_create(sc->parent_tag,		/* parent */
				sc->alignment,		/* alignment */
				0,			/* boundary */
				BUS_SPACE_MAXADDR,	/* lowaddr */
				BUS_SPACE_MAXADDR, 	/* highaddr */
				NULL, NULL, 		/* filter, filterarg */
				dma_mem_size,		/* maxsize */
				1,			/* nsegments */
				BUS_SPACE_MAXSIZE,	/* maxsegsize */
				0,			/* flags */
				NULL,			/* lockfunc */
				NULL,			/* lockfuncarg */
				&sc->cmd_tag		/* tag */)) {
		tw_osli_printf(sc, "error = %d",
			TW_CL_SEVERITY_ERROR_STRING,
			TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
			0x200B,
			"Can't allocate DMA tag for Common Layer's "
			"DMA'able memory",
			ENOMEM);
		return(ENOMEM);
	}

	if (bus_dmamem_alloc(sc->cmd_tag, &sc->dma_mem,
		BUS_DMA_NOWAIT, &sc->cmd_map)) {
		/* Try a second time. */
		if (bus_dmamem_alloc(sc->cmd_tag, &sc->dma_mem,
			BUS_DMA_NOWAIT, &sc->cmd_map)) {
			tw_osli_printf(sc, "error = %d",
				TW_CL_SEVERITY_ERROR_STRING,
				TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
				0x200C,
				"Can't allocate DMA'able memory for the"
				"Common Layer",
				ENOMEM);
			return(ENOMEM);
		}
	}

	bus_dmamap_load(sc->cmd_tag, sc->cmd_map, sc->dma_mem,
		dma_mem_size, twa_map_load_callback,
		&sc->dma_mem_phys, 0);

	/*
	 * Create a dma tag for data buffers; size will be the maximum
	 * possible I/O size (128kB).
	 */
	if (bus_dma_tag_create(sc->parent_tag,		/* parent */
				sc->alignment,		/* alignment */
				0,			/* boundary */
				BUS_SPACE_MAXADDR,	/* lowaddr */
				BUS_SPACE_MAXADDR, 	/* highaddr */
				NULL, NULL, 		/* filter, filterarg */
				TW_CL_MAX_IO_SIZE,	/* maxsize */
				max_sg_elements,	/* nsegments */
				TW_CL_MAX_IO_SIZE,	/* maxsegsize */
				BUS_DMA_ALLOCNOW,	/* flags */
				twa_busdma_lock,	/* lockfunc */
				sc->io_lock,		/* lockfuncarg */
				&sc->dma_tag		/* tag */)) {
		tw_osli_printf(sc, "error = %d",
			TW_CL_SEVERITY_ERROR_STRING,
			TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
			0x200F,
			"Can't allocate DMA tag for data buffers",
			ENOMEM);
		return(ENOMEM);
	}

	/*
	 * Create a dma tag for ioctl data buffers; size will be the maximum
	 * possible I/O size (128kB).
	 */
	if (bus_dma_tag_create(sc->parent_tag,		/* parent */
				sc->alignment,		/* alignment */
				0,			/* boundary */
				BUS_SPACE_MAXADDR,	/* lowaddr */
				BUS_SPACE_MAXADDR, 	/* highaddr */
				NULL, NULL, 		/* filter, filterarg */
				TW_CL_MAX_IO_SIZE,	/* maxsize */
				max_sg_elements,	/* nsegments */
				TW_CL_MAX_IO_SIZE,	/* maxsegsize */
				BUS_DMA_ALLOCNOW,	/* flags */
				twa_busdma_lock,	/* lockfunc */
				sc->io_lock,		/* lockfuncarg */
				&sc->ioctl_tag		/* tag */)) {
		tw_osli_printf(sc, "error = %d",
			TW_CL_SEVERITY_ERROR_STRING,
			TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
			0x2010,
			"Can't allocate DMA tag for ioctl data buffers",
			ENOMEM);
		return(ENOMEM);
	}

	/* Create just one map for all ioctl request data buffers. */
	if (bus_dmamap_create(sc->ioctl_tag, 0, &sc->ioctl_map)) {
		tw_osli_printf(sc, "error = %d",
			TW_CL_SEVERITY_ERROR_STRING,
			TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
			0x2011,
			"Can't create ioctl map",
			ENOMEM);
		return(ENOMEM);
	}


	/* Initialize request queues. */
	tw_osli_req_q_init(sc, TW_OSLI_FREE_Q);
	tw_osli_req_q_init(sc, TW_OSLI_BUSY_Q);

	if ((sc->req_ctx_buf = (struct tw_osli_req_context *)
			malloc((sizeof(struct tw_osli_req_context) *
				TW_OSLI_MAX_NUM_REQUESTS),
				TW_OSLI_MALLOC_CLASS, M_WAITOK)) == NULL) {
		tw_osli_printf(sc, "error = %d",
			TW_CL_SEVERITY_ERROR_STRING,
			TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
			0x2012,
			"Failed to allocate request packets",
			ENOMEM);
		return(ENOMEM);
	}
	bzero(sc->req_ctx_buf,
		sizeof(struct tw_osli_req_context) * TW_OSLI_MAX_NUM_REQUESTS);

	for (i = 0; i < TW_OSLI_MAX_NUM_REQUESTS; i++) {
		req = &(sc->req_ctx_buf[i]);
		req->ctlr = sc;
		if (bus_dmamap_create(sc->dma_tag, 0, &req->dma_map)) {
			tw_osli_printf(sc, "request # = %d, error = %d",
				TW_CL_SEVERITY_ERROR_STRING,
				TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
				0x2013,
				"Can't create dma map",
				i, ENOMEM);
			return(ENOMEM);
		}

		/* Initialize the ioctl wakeup/ timeout mutex */
		req->ioctl_wake_timeout_lock = &(req->ioctl_wake_timeout_lock_handle);
		mtx_init(req->ioctl_wake_timeout_lock, "tw_ioctl_wake_timeout_lock", NULL, MTX_DEF);

		/* Insert request into the free queue. */
		tw_osli_req_q_insert_tail(req, TW_OSLI_FREE_Q);
	}

	return(0);
}