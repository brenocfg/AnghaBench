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
typedef  scalar_t__ uint64_t ;
struct mpr_softc {int maxio; int prp_buffer_size; int /*<<< orphan*/  prp_pages_free_lowwater; scalar_t__ prp_page_busaddr; scalar_t__ prp_pages; struct mpr_prp_page* prps; int /*<<< orphan*/  prp_page_map; int /*<<< orphan*/  prp_page_dmat; int /*<<< orphan*/  mpr_parent_dmat; } ;
struct mpr_prp_page {scalar_t__ prp_page_busaddr; scalar_t__* prp_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MPR_ERROR ; 
 int /*<<< orphan*/  M_MPR ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int NVME_QDEPTH ; 
 int PAGE_SIZE ; 
 int PRP_ENTRY_SIZE ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (scalar_t__,int) ; 
 struct mpr_prp_page* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpr_dprint (struct mpr_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mpr_free_prp_page (struct mpr_softc*,struct mpr_prp_page*) ; 
 int /*<<< orphan*/  mpr_memaddr_cb ; 

__attribute__((used)) static int
mpr_alloc_nvme_prp_pages(struct mpr_softc *sc)
{
	int PRPs_per_page, PRPs_required, pages_required;
	int rsize, i;
	struct mpr_prp_page *prp_page;

	/*
	 * Assuming a MAX_IO_SIZE of 1MB and a PAGE_SIZE of 4k, the max number
	 * of PRPs (NVMe's Scatter/Gather Element) needed per I/O is:
	 * MAX_IO_SIZE / PAGE_SIZE = 256
	 * 
	 * 1 PRP entry in main frame for PRP list pointer still leaves 255 PRPs
	 * required for the remainder of the 1MB I/O. 512 PRPs can fit into one
	 * page (4096 / 8 = 512), so only one page is required for each I/O.
	 *
	 * Each of these buffers will need to be contiguous. For simplicity,
	 * only one buffer is allocated here, which has all of the space
	 * required for the NVMe Queue Depth. If there are problems allocating
	 * this one buffer, this function will need to change to allocate
	 * individual, contiguous NVME_QDEPTH buffers.
	 *
	 * The real calculation will use the real max io size. Above is just an
	 * example.
	 *
	 */
	PRPs_required = sc->maxio / PAGE_SIZE;
	PRPs_per_page = (PAGE_SIZE / PRP_ENTRY_SIZE) - 1;
	pages_required = (PRPs_required / PRPs_per_page) + 1;

	sc->prp_buffer_size = PAGE_SIZE * pages_required; 
	rsize = sc->prp_buffer_size * NVME_QDEPTH; 
	if (bus_dma_tag_create( sc->mpr_parent_dmat,	/* parent */
				4, 0,			/* algnmnt, boundary */
				BUS_SPACE_MAXADDR_32BIT,/* lowaddr */
				BUS_SPACE_MAXADDR,	/* highaddr */
				NULL, NULL,		/* filter, filterarg */
				rsize,			/* maxsize */
				1,			/* nsegments */
				rsize,			/* maxsegsize */
				0,			/* flags */
				NULL, NULL,		/* lockfunc, lockarg */
				&sc->prp_page_dmat)) {
		mpr_dprint(sc, MPR_ERROR, "Cannot allocate NVMe PRP DMA "
		    "tag\n");
		return (ENOMEM);
	}
	if (bus_dmamem_alloc(sc->prp_page_dmat, (void **)&sc->prp_pages,
	    BUS_DMA_NOWAIT, &sc->prp_page_map)) {
		mpr_dprint(sc, MPR_ERROR, "Cannot allocate NVMe PRP memory\n");
		return (ENOMEM);
	}
	bzero(sc->prp_pages, rsize);
	bus_dmamap_load(sc->prp_page_dmat, sc->prp_page_map, sc->prp_pages,
	    rsize, mpr_memaddr_cb, &sc->prp_page_busaddr, 0);

	sc->prps = malloc(sizeof(struct mpr_prp_page) * NVME_QDEPTH, M_MPR,
	    M_WAITOK | M_ZERO);
	for (i = 0; i < NVME_QDEPTH; i++) {
		prp_page = &sc->prps[i];
		prp_page->prp_page = (uint64_t *)(sc->prp_pages +
		    i * sc->prp_buffer_size);
		prp_page->prp_page_busaddr = (uint64_t)(sc->prp_page_busaddr +
		    i * sc->prp_buffer_size);
		mpr_free_prp_page(sc, prp_page);
		sc->prp_pages_free_lowwater++;
	}

	return (0);
}