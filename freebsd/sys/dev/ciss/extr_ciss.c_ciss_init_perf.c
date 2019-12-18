#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct ciss_softc {int ciss_max_requests; int ciss_cycle; int /*<<< orphan*/  ciss_reply_phys; scalar_t__ ciss_rqidx; int /*<<< orphan*/  ciss_reply; int /*<<< orphan*/  ciss_reply_map; int /*<<< orphan*/  ciss_reply_dmat; int /*<<< orphan*/  ciss_parent_dmat; struct ciss_perf_config* ciss_perf; } ;
struct ciss_sg_entry {int dummy; } ;
struct ciss_perf_config {int* fetch_count; int rq_size; int rq_count; TYPE_1__* rq; scalar_t__ rq_bank_lo; scalar_t__ rq_bank_hi; } ;
struct ciss_command {int dummy; } ;
struct TYPE_2__ {int rq_addr_hi; int /*<<< orphan*/  rq_addr_lo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int CISS_COMMAND_ALLOC_SIZE ; 
 size_t CISS_SG_FETCH_1 ; 
 size_t CISS_SG_FETCH_16 ; 
 size_t CISS_SG_FETCH_2 ; 
 size_t CISS_SG_FETCH_32 ; 
 size_t CISS_SG_FETCH_4 ; 
 size_t CISS_SG_FETCH_8 ; 
 size_t CISS_SG_FETCH_MAX ; 
 size_t CISS_SG_FETCH_NONE ; 
 int ENOMEM ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ciss_command_map_helper ; 
 int /*<<< orphan*/  ciss_printf (struct ciss_softc*,char*) ; 

__attribute__((used)) static int
ciss_init_perf(struct ciss_softc *sc)
{
    struct ciss_perf_config *pc = sc->ciss_perf;
    int reply_size;

    /*
     * Create the DMA tag for the reply queue.
     */
    reply_size = sizeof(uint64_t) * sc->ciss_max_requests;
    if (bus_dma_tag_create(sc->ciss_parent_dmat,	/* parent */
			   1, 0, 			/* alignment, boundary */
			   BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
			   BUS_SPACE_MAXADDR, 		/* highaddr */
			   NULL, NULL, 			/* filter, filterarg */
			   reply_size, 1,		/* maxsize, nsegments */
			   BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
			   0,				/* flags */
			   NULL, NULL,			/* lockfunc, lockarg */
			   &sc->ciss_reply_dmat)) {
	ciss_printf(sc, "can't allocate reply DMA tag\n");
	return(ENOMEM);
    }
    /*
     * Allocate memory and make it available for DMA.
     */
    if (bus_dmamem_alloc(sc->ciss_reply_dmat, (void **)&sc->ciss_reply,
			 BUS_DMA_NOWAIT, &sc->ciss_reply_map)) {
	ciss_printf(sc, "can't allocate reply memory\n");
	return(ENOMEM);
    }
    bus_dmamap_load(sc->ciss_reply_dmat, sc->ciss_reply_map, sc->ciss_reply,
		    reply_size, ciss_command_map_helper, &sc->ciss_reply_phys, 0);
    bzero(sc->ciss_reply, reply_size);

    sc->ciss_cycle = 0x1;
    sc->ciss_rqidx = 0;

    /*
     * Preload the fetch table with common command sizes.  This allows the
     * hardware to not waste bus cycles for typical i/o commands, but also not
     * tax the driver to be too exact in choosing sizes.  The table is optimized
     * for page-aligned i/o's, but since most i/o comes from the various pagers,
     * it's a reasonable assumption to make.
     */
    pc->fetch_count[CISS_SG_FETCH_NONE] = (sizeof(struct ciss_command) + 15) / 16;
    pc->fetch_count[CISS_SG_FETCH_1] =
	(sizeof(struct ciss_command) + sizeof(struct ciss_sg_entry) * 1 + 15) / 16;
    pc->fetch_count[CISS_SG_FETCH_2] =
	(sizeof(struct ciss_command) + sizeof(struct ciss_sg_entry) * 2 + 15) / 16;
    pc->fetch_count[CISS_SG_FETCH_4] =
	(sizeof(struct ciss_command) + sizeof(struct ciss_sg_entry) * 4 + 15) / 16;
    pc->fetch_count[CISS_SG_FETCH_8] =
	(sizeof(struct ciss_command) + sizeof(struct ciss_sg_entry) * 8 + 15) / 16;
    pc->fetch_count[CISS_SG_FETCH_16] =
	(sizeof(struct ciss_command) + sizeof(struct ciss_sg_entry) * 16 + 15) / 16;
    pc->fetch_count[CISS_SG_FETCH_32] =
	(sizeof(struct ciss_command) + sizeof(struct ciss_sg_entry) * 32 + 15) / 16;
    pc->fetch_count[CISS_SG_FETCH_MAX] = (CISS_COMMAND_ALLOC_SIZE + 15) / 16;

    pc->rq_size = sc->ciss_max_requests; /* XXX less than the card supports? */
    pc->rq_count = 1;	/* XXX Hardcode for a single queue */
    pc->rq_bank_hi = 0;
    pc->rq_bank_lo = 0;
    pc->rq[0].rq_addr_hi = 0x0;
    pc->rq[0].rq_addr_lo = sc->ciss_reply_phys;

    return(0);
}