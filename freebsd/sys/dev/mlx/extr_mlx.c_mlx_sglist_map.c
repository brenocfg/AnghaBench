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
struct mlx_softc {int /*<<< orphan*/ * mlx_sgtable; int /*<<< orphan*/  mlx_sg_dmamap; int /*<<< orphan*/ * mlx_sg_dmat; int /*<<< orphan*/  mlx_dev; int /*<<< orphan*/  mlx_parent_dmat; TYPE_1__* mlx_enq2; scalar_t__ mlx_sgbusaddr; } ;
struct mlx_sgentry {int dummy; } ;
struct TYPE_2__ {int me_max_commands; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int ENOMEM ; 
 int MLX_NSEG ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,struct mlx_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlx_dma_map_sg ; 

__attribute__((used)) static int
mlx_sglist_map(struct mlx_softc *sc)
{
    size_t	segsize;
    int		error, ncmd;

    debug_called(1);

    /* destroy any existing mappings */
    if (sc->mlx_sgbusaddr)
	bus_dmamap_unload(sc->mlx_sg_dmat, sc->mlx_sg_dmamap);
    if (sc->mlx_sgtable)
	bus_dmamem_free(sc->mlx_sg_dmat, sc->mlx_sgtable, sc->mlx_sg_dmamap);
    if (sc->mlx_sg_dmat)
	bus_dma_tag_destroy(sc->mlx_sg_dmat);
    sc->mlx_sgbusaddr = 0;
    sc->mlx_sgtable = NULL;
    sc->mlx_sg_dmat = NULL;

    /*
     * Create a single tag describing a region large enough to hold all of
     * the s/g lists we will need.  If we're called early on, we don't know how
     * many commands we're going to be asked to support, so only allocate enough
     * for a couple.
     */
    if (sc->mlx_enq2 == NULL) {
	ncmd = 2;
    } else {
	ncmd = sc->mlx_enq2->me_max_commands;
    }
    segsize = sizeof(struct mlx_sgentry) * MLX_NSEG * ncmd;
    error = bus_dma_tag_create(sc->mlx_parent_dmat, 	/* parent */
			       1, 0, 			/* alignment,boundary */
			       BUS_SPACE_MAXADDR,	/* lowaddr */
			       BUS_SPACE_MAXADDR, 	/* highaddr */
			       NULL, NULL, 		/* filter, filterarg */
			       segsize, 1,		/* maxsize, nsegments */
			       BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
			       0,			/* flags */
			       NULL, NULL,		/* lockfunc, lockarg */
			       &sc->mlx_sg_dmat);
    if (error != 0) {
	device_printf(sc->mlx_dev, "can't allocate scatter/gather DMA tag\n");
	return(ENOMEM);
    }

    /*
     * Allocate enough s/g maps for all commands and permanently map them into
     * controller-visible space.
     *	
     * XXX this assumes we can get enough space for all the s/g maps in one 
     * contiguous slab.  We may need to switch to a more complex arrangement
     * where we allocate in smaller chunks and keep a lookup table from slot
     * to bus address.
     */
    error = bus_dmamem_alloc(sc->mlx_sg_dmat, (void **)&sc->mlx_sgtable,
			     BUS_DMA_NOWAIT, &sc->mlx_sg_dmamap);
    if (error) {
	device_printf(sc->mlx_dev, "can't allocate s/g table\n");
	return(ENOMEM);
    }
    (void)bus_dmamap_load(sc->mlx_sg_dmat, sc->mlx_sg_dmamap, sc->mlx_sgtable,
			  segsize, mlx_dma_map_sg, sc, 0);
    return(0);
}