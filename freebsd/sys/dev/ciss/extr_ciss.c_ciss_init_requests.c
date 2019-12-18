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
struct ciss_softc {int ciss_max_requests; int /*<<< orphan*/  ciss_buffer_dmat; scalar_t__ ciss_command_phys; scalar_t__ ciss_command; struct ciss_request* ciss_request; int /*<<< orphan*/  ciss_command_map; int /*<<< orphan*/  ciss_command_dmat; int /*<<< orphan*/  ciss_parent_dmat; TYPE_1__* ciss_cfg; } ;
struct ciss_request {int cr_tag; int /*<<< orphan*/  cr_datamap; scalar_t__ cr_ccphys; struct ciss_command* cr_cc; struct ciss_softc* cr_sc; } ;
struct ciss_command {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_outstanding_commands; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int CISS_COMMAND_ALLOC_SIZE ; 
 int ENOMEM ; 
 scalar_t__ bootverbose ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (scalar_t__,int) ; 
 int /*<<< orphan*/  ciss_command_map_helper ; 
 int /*<<< orphan*/  ciss_enqueue_free (struct ciss_request*) ; 
 int /*<<< orphan*/  ciss_printf (struct ciss_softc*,char*,...) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static int
ciss_init_requests(struct ciss_softc *sc)
{
    struct ciss_request	*cr;
    int			i;

    debug_called(1);

    if (bootverbose)
	ciss_printf(sc, "using %d of %d available commands\n",
		    sc->ciss_max_requests, sc->ciss_cfg->max_outstanding_commands);

    /*
     * Create the DMA tag for commands.
     */
    if (bus_dma_tag_create(sc->ciss_parent_dmat,	/* parent */
			   32, 0, 			/* alignment, boundary */
			   BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
			   BUS_SPACE_MAXADDR, 		/* highaddr */
			   NULL, NULL, 			/* filter, filterarg */
			   CISS_COMMAND_ALLOC_SIZE *
			   sc->ciss_max_requests, 1,	/* maxsize, nsegments */
			   BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
			   0,				/* flags */
			   NULL, NULL,			/* lockfunc, lockarg */
			   &sc->ciss_command_dmat)) {
	ciss_printf(sc, "can't allocate command DMA tag\n");
	return(ENOMEM);
    }
    /*
     * Allocate memory and make it available for DMA.
     */
    if (bus_dmamem_alloc(sc->ciss_command_dmat, (void **)&sc->ciss_command,
			 BUS_DMA_NOWAIT, &sc->ciss_command_map)) {
	ciss_printf(sc, "can't allocate command memory\n");
	return(ENOMEM);
    }
    bus_dmamap_load(sc->ciss_command_dmat, sc->ciss_command_map,sc->ciss_command,
		    CISS_COMMAND_ALLOC_SIZE * sc->ciss_max_requests,
		    ciss_command_map_helper, &sc->ciss_command_phys, 0);
    bzero(sc->ciss_command, CISS_COMMAND_ALLOC_SIZE * sc->ciss_max_requests);

    /*
     * Set up the request and command structures, push requests onto
     * the free queue.
     */
    for (i = 1; i < sc->ciss_max_requests; i++) {
	cr = &sc->ciss_request[i];
	cr->cr_sc = sc;
	cr->cr_tag = i;
	cr->cr_cc = (struct ciss_command *)((uintptr_t)sc->ciss_command +
	    CISS_COMMAND_ALLOC_SIZE * i);
	cr->cr_ccphys = sc->ciss_command_phys + CISS_COMMAND_ALLOC_SIZE * i;
	bus_dmamap_create(sc->ciss_buffer_dmat, 0, &cr->cr_datamap);
	ciss_enqueue_free(cr);
    }
    return(0);
}