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
struct mlx_softc {int mlx_iftype; int /*<<< orphan*/  mlx_parent_dmat; int /*<<< orphan*/  mlx_dev; int /*<<< orphan*/ * mlx_mem; void* mlx_mem_rid; void* mlx_mem_type; int /*<<< orphan*/  mlx_io_lock; int /*<<< orphan*/  mlx_timeout; int /*<<< orphan*/  mlx_config_lock; } ;
struct mlx_ident {int iftype; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_UNRESTRICTED ; 
 int ENOMEM ; 
 int ENXIO ; 
 void* MLX_CFG_BASE0 ; 
 void* MLX_CFG_BASE1 ; 
#define  MLX_IFTYPE_2 131 
#define  MLX_IFTYPE_3 130 
#define  MLX_IFTYPE_4 129 
#define  MLX_IFTYPE_5 128 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 void* SYS_RES_IOPORT ; 
 void* SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,void*,void**,int /*<<< orphan*/ ) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 struct mlx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int mlx_attach (struct mlx_softc*) ; 
 int /*<<< orphan*/  mlx_free (struct mlx_softc*) ; 
 struct mlx_ident* mlx_pci_match (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx_startup (struct mlx_softc*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
mlx_pci_attach(device_t dev)
{
    struct mlx_softc	*sc;
    struct mlx_ident	*m;
    int			error;

    debug_called(1);

    pci_enable_busmaster(dev);

    sc = device_get_softc(dev);
    sc->mlx_dev = dev;

    /*
     * Work out what sort of adapter this is (we need to know this in order
     * to map the appropriate interface resources).
     */
    m = mlx_pci_match(dev);
    if (m == NULL)		/* shouldn't happen */
	return(ENXIO);
    sc->mlx_iftype = m->iftype;

    mtx_init(&sc->mlx_io_lock, "mlx I/O", NULL, MTX_DEF);
    sx_init(&sc->mlx_config_lock, "mlx config");
    callout_init_mtx(&sc->mlx_timeout, &sc->mlx_io_lock, 0);

    /*
     * Allocate the PCI register window.
     */
    
    /* type 2/3 adapters have an I/O region we don't prefer at base 0 */
    switch(sc->mlx_iftype) {
    case MLX_IFTYPE_2:
    case MLX_IFTYPE_3:
	sc->mlx_mem_type = SYS_RES_MEMORY;
	sc->mlx_mem_rid = MLX_CFG_BASE1;
	sc->mlx_mem = bus_alloc_resource_any(dev, sc->mlx_mem_type,
		&sc->mlx_mem_rid, RF_ACTIVE);
	if (sc->mlx_mem == NULL) {
	    sc->mlx_mem_type = SYS_RES_IOPORT;
	    sc->mlx_mem_rid = MLX_CFG_BASE0;
	    sc->mlx_mem = bus_alloc_resource_any(dev, sc->mlx_mem_type,
		&sc->mlx_mem_rid, RF_ACTIVE);
	}
	break;
    case MLX_IFTYPE_4:
    case MLX_IFTYPE_5:
	sc->mlx_mem_type = SYS_RES_MEMORY;
	sc->mlx_mem_rid = MLX_CFG_BASE0;
	sc->mlx_mem = bus_alloc_resource_any(dev, sc->mlx_mem_type,
		&sc->mlx_mem_rid, RF_ACTIVE);
	break;
    }
    if (sc->mlx_mem == NULL) {
	device_printf(sc->mlx_dev, "couldn't allocate mailbox window\n");
	mlx_free(sc);
	return(ENXIO);
    }

    /*
     * Allocate the parent bus DMA tag appropriate for PCI.
     */
    error = bus_dma_tag_create(bus_get_dma_tag(dev),	/* PCI parent */
			       1, 0, 			/* alignment, boundary */
			       BUS_SPACE_MAXADDR_32BIT, /* lowaddr */
			       BUS_SPACE_MAXADDR, 	/* highaddr */
			       NULL, NULL, 		/* filter, filterarg */
			       BUS_SPACE_MAXSIZE_32BIT, /* maxsize */
			       BUS_SPACE_UNRESTRICTED,	/* nsegments */
			       BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
			       BUS_DMA_ALLOCNOW,	/* flags */
			       NULL,			/* lockfunc */
			       NULL,			/* lockarg */
			       &sc->mlx_parent_dmat);
    if (error != 0) {
	device_printf(dev, "can't allocate parent DMA tag\n");
	mlx_free(sc);
	return(ENOMEM);
    }

    /*
     * Do bus-independant initialisation.
     */
    error = mlx_attach(sc);
    if (error != 0) {
	mlx_free(sc);
	return(error);
    }
    
    /*
     * Start the controller.
     */
    mlx_startup(sc);
    return(0);
}