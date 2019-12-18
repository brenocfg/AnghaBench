#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct twe_softc* ich_arg; int /*<<< orphan*/  ich_func; } ;
struct twe_softc {TYPE_2__ twe_ich; TYPE_1__* twe_dev_t; int /*<<< orphan*/  twe_dev; int /*<<< orphan*/  twe_immediate_map; int /*<<< orphan*/  twe_immediate; int /*<<< orphan*/  twe_immediate_dmat; int /*<<< orphan*/  twe_parent_dmat; int /*<<< orphan*/  twe_buffer_dmat; int /*<<< orphan*/  twe_io_lock; int /*<<< orphan*/  twe_cmd; int /*<<< orphan*/  twe_cmdmap; int /*<<< orphan*/  twe_cmd_dmat; int /*<<< orphan*/  twe_intr; int /*<<< orphan*/ * twe_irq; int /*<<< orphan*/ * twe_io; int /*<<< orphan*/  twe_config_lock; } ;
struct sysctl_oid {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {struct twe_softc* si_drv1; } ;
typedef  int /*<<< orphan*/  TWE_Command ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int BUS_SPACE_MAXSIZE_32BIT ; 
 int BUS_SPACE_UNRESTRICTED ; 
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int DFLTPHYS ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GID_OPERATOR ; 
 int INTR_ENTROPY ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int PAGE_SIZE ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_STRING (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  TWE_DRIVER_VERSION_STRING ; 
 int TWE_IO_CONFIG_REG ; 
 int TWE_MAX_SGL_LENGTH ; 
 int TWE_Q_LENGTH ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  _hw ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct twe_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct twe_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * busdma_lock_mutex ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 scalar_t__ config_intrhook_establish (TYPE_2__*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct twe_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 TYPE_1__* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  twe_cdevsw ; 
 int /*<<< orphan*/  twe_describe_controller (struct twe_softc*) ; 
 int /*<<< orphan*/  twe_free (struct twe_softc*) ; 
 int /*<<< orphan*/  twe_intrhook ; 
 int /*<<< orphan*/  twe_pci_intr ; 
 int /*<<< orphan*/  twe_printf (struct twe_softc*,char*) ; 
 int twe_setup (struct twe_softc*) ; 
 int /*<<< orphan*/  twe_setup_request_dmamap ; 

__attribute__((used)) static int
twe_attach(device_t dev)
{
    struct twe_softc	*sc;
    struct sysctl_oid	*sysctl_tree;
    int			rid, error;

    debug_called(4);

    /*
     * Initialise the softc structure.
     */
    sc = device_get_softc(dev);
    sc->twe_dev = dev;
    mtx_init(&sc->twe_io_lock, "twe I/O", NULL, MTX_DEF);
    sx_init(&sc->twe_config_lock, "twe config");

    /*
     * XXX: This sysctl tree must stay at hw.tweX rather than using
     * the device_get_sysctl_tree() created by new-bus because
     * existing 3rd party binary tools such as tw_cli and 3dm2 use the
     * existence of this sysctl node to discover controllers.
     */
    sysctl_tree = SYSCTL_ADD_NODE(device_get_sysctl_ctx(dev),
	SYSCTL_STATIC_CHILDREN(_hw), OID_AUTO,
	device_get_nameunit(dev), CTLFLAG_RD, 0, "");
    if (sysctl_tree == NULL) {
	twe_printf(sc, "cannot add sysctl tree node\n");
	return (ENXIO);
    }
    SYSCTL_ADD_STRING(device_get_sysctl_ctx(dev), SYSCTL_CHILDREN(sysctl_tree),
	OID_AUTO, "driver_version", CTLFLAG_RD, TWE_DRIVER_VERSION_STRING, 0,
	"TWE driver version");

    /*
     * Force the busmaster enable bit on, in case the BIOS forgot.
     */
    pci_enable_busmaster(dev);

    /*
     * Allocate the PCI register window.
     */
    rid = TWE_IO_CONFIG_REG;
    if ((sc->twe_io = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &rid, 
        RF_ACTIVE)) == NULL) {
	twe_printf(sc, "can't allocate register window\n");
	twe_free(sc);
	return(ENXIO);
    }

    /*
     * Allocate the parent bus DMA tag appropriate for PCI.
     */
    if (bus_dma_tag_create(bus_get_dma_tag(dev),		/* PCI parent */
			   1, 0, 				/* alignment, boundary */
			   BUS_SPACE_MAXADDR_32BIT, 		/* lowaddr */
			   BUS_SPACE_MAXADDR, 			/* highaddr */
			   NULL, NULL, 				/* filter, filterarg */
			   BUS_SPACE_MAXSIZE_32BIT,		/* maxsize */
			   BUS_SPACE_UNRESTRICTED,		/* nsegments */
			   BUS_SPACE_MAXSIZE_32BIT,		/* maxsegsize */
			   0,					/* flags */
			   NULL,				/* lockfunc */
			   NULL,				/* lockarg */
			   &sc->twe_parent_dmat)) {
	twe_printf(sc, "can't allocate parent DMA tag\n");
	twe_free(sc);
	return(ENOMEM);
    }

    /* 
     * Allocate and connect our interrupt.
     */
    rid = 0;
    if ((sc->twe_irq = bus_alloc_resource_any(sc->twe_dev, SYS_RES_IRQ,
        &rid, RF_SHAREABLE | RF_ACTIVE)) == NULL) {
	twe_printf(sc, "can't allocate interrupt\n");
	twe_free(sc);
	return(ENXIO);
    }
    if (bus_setup_intr(sc->twe_dev, sc->twe_irq, INTR_TYPE_BIO | INTR_ENTROPY | INTR_MPSAFE,  
		       NULL, twe_pci_intr, sc, &sc->twe_intr)) {
	twe_printf(sc, "can't set up interrupt\n");
	twe_free(sc);
	return(ENXIO);
    }

    /*
     * Create DMA tag for mapping command's into controller-addressable space.
     */
    if (bus_dma_tag_create(sc->twe_parent_dmat, 	/* parent */
			   1, 0, 			/* alignment, boundary */
			   BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
			   BUS_SPACE_MAXADDR, 		/* highaddr */
			   NULL, NULL, 			/* filter, filterarg */
			   sizeof(TWE_Command) *
			   TWE_Q_LENGTH, 1,		/* maxsize, nsegments */
			   BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
			   0,				/* flags */
			   NULL,			/* lockfunc */
			   NULL,			/* lockarg */
			   &sc->twe_cmd_dmat)) {
	twe_printf(sc, "can't allocate data buffer DMA tag\n");
	twe_free(sc);
	return(ENOMEM);
    }
    /*
     * Allocate memory and make it available for DMA.
     */
    if (bus_dmamem_alloc(sc->twe_cmd_dmat, (void **)&sc->twe_cmd,
			 BUS_DMA_NOWAIT, &sc->twe_cmdmap)) {
	twe_printf(sc, "can't allocate command memory\n");
	return(ENOMEM);
    }
    bus_dmamap_load(sc->twe_cmd_dmat, sc->twe_cmdmap, sc->twe_cmd,
		    sizeof(TWE_Command) * TWE_Q_LENGTH,
		    twe_setup_request_dmamap, sc, 0);
    bzero(sc->twe_cmd, sizeof(TWE_Command) * TWE_Q_LENGTH);

    /*
     * Create DMA tag for mapping objects into controller-addressable space.
     */
    if (bus_dma_tag_create(sc->twe_parent_dmat, 	/* parent */
			   1, 0, 			/* alignment, boundary */
			   BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
			   BUS_SPACE_MAXADDR, 		/* highaddr */
			   NULL, NULL, 			/* filter, filterarg */
			   (TWE_MAX_SGL_LENGTH - 1) * PAGE_SIZE,/* maxsize */
			   TWE_MAX_SGL_LENGTH,		/* nsegments */
			   BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
			   BUS_DMA_ALLOCNOW,		/* flags */
			   busdma_lock_mutex,		/* lockfunc */
			   &sc->twe_io_lock,		/* lockarg */
			   &sc->twe_buffer_dmat)) {
	twe_printf(sc, "can't allocate data buffer DMA tag\n");
	twe_free(sc);
	return(ENOMEM);
    }

    /*
     * Create DMA tag for mapping objects into controller-addressable space.
     */
    if (bus_dma_tag_create(sc->twe_parent_dmat, 	/* parent */
			   1, 0, 			/* alignment, boundary */
			   BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
			   BUS_SPACE_MAXADDR, 		/* highaddr */
			   NULL, NULL, 			/* filter, filterarg */
			   DFLTPHYS, 1,			/* maxsize, nsegments */
			   BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
			   0,				/* flags */
			   NULL,			/* lockfunc */
			   NULL,			/* lockarg */
			   &sc->twe_immediate_dmat)) {
	twe_printf(sc, "can't allocate data buffer DMA tag\n");
	twe_free(sc);
	return(ENOMEM);
    }
    /*
     * Allocate memory for requests which cannot sleep or support continuation.
     */
     if (bus_dmamem_alloc(sc->twe_immediate_dmat, (void **)&sc->twe_immediate,
			  BUS_DMA_NOWAIT, &sc->twe_immediate_map)) {
	twe_printf(sc, "can't allocate memory for immediate requests\n");
	return(ENOMEM);
     }

    /*
     * Initialise the controller and driver core.
     */
    if ((error = twe_setup(sc))) {
	twe_free(sc);
	return(error);
    }

    /*
     * Print some information about the controller and configuration.
     */
    twe_describe_controller(sc);

    /*
     * Create the control device.
     */
    sc->twe_dev_t = make_dev(&twe_cdevsw, device_get_unit(sc->twe_dev), UID_ROOT, GID_OPERATOR,
			     S_IRUSR | S_IWUSR, "twe%d", device_get_unit(sc->twe_dev));
    sc->twe_dev_t->si_drv1 = sc;
    /*
     * Schedule ourselves to bring the controller up once interrupts are available.
     * This isn't strictly necessary, since we disable interrupts while probing the
     * controller, but it is more in keeping with common practice for other disk 
     * devices.
     */
    sc->twe_ich.ich_func = twe_intrhook;
    sc->twe_ich.ich_arg = sc;
    if (config_intrhook_establish(&sc->twe_ich) != 0) {
	twe_printf(sc, "can't establish configuration hook\n");
	twe_free(sc);
	return(ENXIO);
    }

    return(0);
}