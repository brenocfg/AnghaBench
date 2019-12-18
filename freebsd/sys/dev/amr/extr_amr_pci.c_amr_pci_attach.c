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
typedef  int /*<<< orphan*/  vm_paddr_t ;
struct amr_softc {int /*<<< orphan*/  amr_hw_lock; int /*<<< orphan*/  amr_list_lock; int /*<<< orphan*/  amr_dev; int /*<<< orphan*/  amr_buffer64_dmat; int /*<<< orphan*/  amr_parent_dmat; int /*<<< orphan*/  amr_buffer_dmat; int /*<<< orphan*/  amr_intr; int /*<<< orphan*/ * amr_irq; int /*<<< orphan*/ * amr_reg; int /*<<< orphan*/  amr_bhandle; int /*<<< orphan*/  amr_btag; int /*<<< orphan*/  amr_type; } ;
struct amr_ident {int flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AMR_ID_DO_SG64 ; 
 int AMR_ID_QUARTZ ; 
 scalar_t__ AMR_IS_QUARTZ (struct amr_softc*) ; 
 scalar_t__ AMR_IS_SG64 (struct amr_softc*) ; 
 int /*<<< orphan*/  AMR_NSEG ; 
 int /*<<< orphan*/  AMR_TYPE_QUARTZ ; 
 int /*<<< orphan*/  AMR_TYPE_SG64 ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_UNRESTRICTED ; 
 int /*<<< orphan*/  DFLTPHYS ; 
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_ENTROPY ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int SYS_RES_IOPORT ; 
 int SYS_RES_IRQ ; 
 int SYS_RES_MEMORY ; 
 int amr_attach (struct amr_softc*) ; 
 int amr_ccb_map (struct amr_softc*) ; 
 struct amr_ident* amr_find_ident (int /*<<< orphan*/ ) ; 
 scalar_t__ amr_force_sg32 ; 
 int /*<<< orphan*/  amr_pci_free (struct amr_softc*) ; 
 int /*<<< orphan*/  amr_pci_intr ; 
 int amr_setup_mbox (struct amr_softc*) ; 
 int amr_sglist_map (struct amr_softc*) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int,int*,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct amr_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * busdma_lock_mutex ; 
 int /*<<< orphan*/  bzero (struct amr_softc*,int) ; 
 int /*<<< orphan*/  debug (int,char*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 struct amr_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
amr_pci_attach(device_t dev)
{
    struct amr_softc	*sc;
    struct amr_ident	*id;
    int			rid, rtype, error;

    debug_called(1);

    /*
     * Initialise softc.
     */
    sc = device_get_softc(dev);
    bzero(sc, sizeof(*sc));
    sc->amr_dev = dev;

    /* assume failure is 'not configured' */
    error = ENXIO;

    /*
     * Determine board type.
     */
    if ((id = amr_find_ident(dev)) == NULL)
	return (ENXIO);

    if (id->flags & AMR_ID_QUARTZ) {
	sc->amr_type |= AMR_TYPE_QUARTZ;
    }

    if ((amr_force_sg32 == 0) && (id->flags & AMR_ID_DO_SG64) &&
	(sizeof(vm_paddr_t) > 4)) {
	device_printf(dev, "Using 64-bit DMA\n");
	sc->amr_type |= AMR_TYPE_SG64;
    }

    /* force the busmaster enable bit on */
    pci_enable_busmaster(dev);

    /*
     * Allocate the PCI register window.
     */
    rid = PCIR_BAR(0);
    rtype = AMR_IS_QUARTZ(sc) ? SYS_RES_MEMORY : SYS_RES_IOPORT;
    sc->amr_reg = bus_alloc_resource_any(dev, rtype, &rid, RF_ACTIVE);
    if (sc->amr_reg == NULL) {
	device_printf(sc->amr_dev, "can't allocate register window\n");
	goto out;
    }
    sc->amr_btag = rman_get_bustag(sc->amr_reg);
    sc->amr_bhandle = rman_get_bushandle(sc->amr_reg);

    /*
     * Allocate and connect our interrupt.
     */
    rid = 0;
    sc->amr_irq = bus_alloc_resource_any(sc->amr_dev, SYS_RES_IRQ, &rid,
        RF_SHAREABLE | RF_ACTIVE);
    if (sc->amr_irq == NULL) {
        device_printf(sc->amr_dev, "can't allocate interrupt\n");
	goto out;
    }
    if (bus_setup_intr(sc->amr_dev, sc->amr_irq,
	INTR_TYPE_BIO | INTR_ENTROPY | INTR_MPSAFE, NULL, amr_pci_intr,
	sc, &sc->amr_intr)) {
        device_printf(sc->amr_dev, "can't set up interrupt\n");
	goto out;
    }

    debug(2, "interrupt attached");

    /* assume failure is 'out of memory' */
    error = ENOMEM;

    /*
     * Allocate the parent bus DMA tag appropriate for PCI.
     */
    if (bus_dma_tag_create(bus_get_dma_tag(dev),	/* PCI parent */
			   1, 0, 			/* alignment,boundary */
			   AMR_IS_SG64(sc) ?
			   BUS_SPACE_MAXADDR :
			   BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
			   BUS_SPACE_MAXADDR, 		/* highaddr */
			   NULL, NULL, 			/* filter, filterarg */
			   BUS_SPACE_MAXSIZE,		/* maxsize */
			   BUS_SPACE_UNRESTRICTED,	/* nsegments */
			   BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
			   0,				/* flags */
			   NULL, NULL,			/* lockfunc, lockarg */
			   &sc->amr_parent_dmat)) {
	device_printf(dev, "can't allocate parent DMA tag\n");
	goto out;
    }

    /*
     * Create DMA tag for mapping buffers into controller-addressable space.
     */
    if (bus_dma_tag_create(sc->amr_parent_dmat,		/* parent */
			   1, 0,			/* alignment,boundary */
			   BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
			   BUS_SPACE_MAXADDR,		/* highaddr */
			   NULL, NULL,			/* filter, filterarg */
			   DFLTPHYS,			/* maxsize */
			   AMR_NSEG,			/* nsegments */
			   BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
			   0,		/* flags */
			   busdma_lock_mutex,		/* lockfunc */
			   &sc->amr_list_lock,		/* lockarg */
			   &sc->amr_buffer_dmat)) {
        device_printf(sc->amr_dev, "can't allocate buffer DMA tag\n");
	goto out;
    }

    if (bus_dma_tag_create(sc->amr_parent_dmat,		/* parent */
			   1, 0,			/* alignment,boundary */
			   BUS_SPACE_MAXADDR,		/* lowaddr */
			   BUS_SPACE_MAXADDR,		/* highaddr */
			   NULL, NULL,			/* filter, filterarg */
			   DFLTPHYS,			/* maxsize */
			   AMR_NSEG,			/* nsegments */
			   BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
			   0,		/* flags */
			   busdma_lock_mutex,		/* lockfunc */
			   &sc->amr_list_lock,		/* lockarg */
			   &sc->amr_buffer64_dmat)) {
        device_printf(sc->amr_dev, "can't allocate buffer DMA tag\n");
	goto out;
    }

    debug(2, "dma tag done");

    /*
     * Allocate and set up mailbox in a bus-visible fashion.
     */
    mtx_init(&sc->amr_list_lock, "AMR List Lock", NULL, MTX_DEF);
    mtx_init(&sc->amr_hw_lock, "AMR HW Lock", NULL, MTX_DEF);
    if ((error = amr_setup_mbox(sc)) != 0)
	goto out;

    debug(2, "mailbox setup");

    /*
     * Build the scatter/gather buffers.
     */
    if ((error = amr_sglist_map(sc)) != 0)
	goto out;
    debug(2, "s/g list mapped");

    if ((error = amr_ccb_map(sc)) != 0)
	goto out;
    debug(2, "ccb mapped");


    /*
     * Do bus-independant initialisation, bring controller online.
     */
    error = amr_attach(sc);

out:
    if (error)
	amr_pci_free(sc);
    return(error);
}