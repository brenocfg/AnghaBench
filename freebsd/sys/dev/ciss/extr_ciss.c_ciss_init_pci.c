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
typedef  int uint32_t ;
struct ciss_softc {int ciss_regs_rid; int ciss_cfg_rid; int* ciss_irq_rid; int ciss_interrupt_mask; int /*<<< orphan*/  ciss_buffer_dmat; int /*<<< orphan*/  ciss_mtx; int /*<<< orphan*/  ciss_parent_dmat; int /*<<< orphan*/  ciss_dev; int /*<<< orphan*/  ciss_intr; int /*<<< orphan*/ * ciss_irq_resource; struct ciss_perf_config* ciss_perf; struct ciss_config_table* ciss_cfg; int /*<<< orphan*/  ciss_max_requests; int /*<<< orphan*/ * ciss_regs_resource; int /*<<< orphan*/ * ciss_cfg_resource; int /*<<< orphan*/  ciss_regs_btag; int /*<<< orphan*/  ciss_regs_bhandle; } ;
struct ciss_perf_config {int dummy; } ;
struct ciss_config_table {int supported_methods; int requested_method; int active_method; int /*<<< orphan*/  host_driver; int /*<<< orphan*/  interrupt_coalesce_count; int /*<<< orphan*/  interrupt_coalesce_delay; scalar_t__ command_physlimit; scalar_t__ transport_offset; int /*<<< orphan*/ * signature; int /*<<< orphan*/  max_outstanding_commands; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int BUS_SPACE_MAXSIZE_32BIT ; 
 int BUS_SPACE_UNRESTRICTED ; 
 int CISS_BOARD_SA5 ; 
 int CISS_BOARD_SA5B ; 
 int CISS_BOARD_SIMPLE ; 
 int /*<<< orphan*/  CISS_DRIVER_SCSI_PREFETCH ; 
 int /*<<< orphan*/  CISS_INTERRUPT_COALESCE_COUNT ; 
 int /*<<< orphan*/  CISS_INTERRUPT_COALESCE_DELAY ; 
 int /*<<< orphan*/  CISS_MAX_REQUESTS ; 
 int CISS_MAX_SG_ELEMENTS ; 
 int CISS_TL_PERF_INTR_MSI ; 
 int CISS_TL_PERF_INTR_OPQ ; 
 int CISS_TL_SIMPLE_BAR_REGS ; 
 int /*<<< orphan*/  CISS_TL_SIMPLE_CFG_BAR ; 
 int /*<<< orphan*/  CISS_TL_SIMPLE_CFG_OFF ; 
 int /*<<< orphan*/  CISS_TL_SIMPLE_DISABLE_INTERRUPTS (struct ciss_softc*) ; 
 int /*<<< orphan*/  CISS_TL_SIMPLE_IDBR ; 
 int CISS_TL_SIMPLE_INTR_OPQ_SA5 ; 
 int CISS_TL_SIMPLE_INTR_OPQ_SA5B ; 
 int CISS_TL_SIMPLE_READ (struct ciss_softc*,int /*<<< orphan*/ ) ; 
 int CISS_TRANSPORT_METHOD_PERF ; 
 int CISS_TRANSPORT_METHOD_SIMPLE ; 
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_CAM ; 
 int PAGE_SIZE ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void*,struct ciss_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * busdma_lock_mutex ; 
 int ciss_force_interrupt ; 
 int ciss_force_transport ; 
 scalar_t__ ciss_init_perf (struct ciss_softc*) ; 
 void* ciss_intr ; 
 int ciss_lookup (int /*<<< orphan*/ ) ; 
 void* ciss_perf_intr ; 
 void* ciss_perf_msi_intr ; 
 int /*<<< orphan*/  ciss_printf (struct ciss_softc*,char*,...) ; 
 scalar_t__ ciss_setup_msix (struct ciss_softc*) ; 
 scalar_t__ ciss_update_config (struct ciss_softc*) ; 
 TYPE_1__* ciss_vendor_data ; 
 int ciss_wait_adapter (struct ciss_softc*) ; 
 int /*<<< orphan*/  debug (int,char*,struct ciss_config_table*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int rman_get_end (int /*<<< orphan*/ *) ; 
 int rman_get_start (int /*<<< orphan*/ *) ; 
 scalar_t__ rman_get_virtual (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
ciss_init_pci(struct ciss_softc *sc)
{
    uintptr_t		cbase, csize, cofs;
    uint32_t		method, supported_methods;
    int			error, sqmask, i;
    void		*intr;

    debug_called(1);

    /*
     * Work out adapter type.
     */
    i = ciss_lookup(sc->ciss_dev);
    if (i < 0) {
	ciss_printf(sc, "unknown adapter type\n");
	return (ENXIO);
    }

    if (ciss_vendor_data[i].flags & CISS_BOARD_SA5) {
	sqmask = CISS_TL_SIMPLE_INTR_OPQ_SA5;
    } else if (ciss_vendor_data[i].flags & CISS_BOARD_SA5B) {
	sqmask = CISS_TL_SIMPLE_INTR_OPQ_SA5B;
    } else {
	/*
	 * XXX Big hammer, masks/unmasks all possible interrupts.  This should
	 * work on all hardware variants.  Need to add code to handle the
	 * "controller crashed" interrupt bit that this unmasks.
	 */
	sqmask = ~0;
    }

    /*
     * Allocate register window first (we need this to find the config
     * struct).
     */
    error = ENXIO;
    sc->ciss_regs_rid = CISS_TL_SIMPLE_BAR_REGS;
    if ((sc->ciss_regs_resource =
	 bus_alloc_resource_any(sc->ciss_dev, SYS_RES_MEMORY,
				&sc->ciss_regs_rid, RF_ACTIVE)) == NULL) {
	ciss_printf(sc, "can't allocate register window\n");
	return(ENXIO);
    }
    sc->ciss_regs_bhandle = rman_get_bushandle(sc->ciss_regs_resource);
    sc->ciss_regs_btag = rman_get_bustag(sc->ciss_regs_resource);

    /*
     * Find the BAR holding the config structure.  If it's not the one
     * we already mapped for registers, map it too.
     */
    sc->ciss_cfg_rid = CISS_TL_SIMPLE_READ(sc, CISS_TL_SIMPLE_CFG_BAR) & 0xffff;
    if (sc->ciss_cfg_rid != sc->ciss_regs_rid) {
	if ((sc->ciss_cfg_resource =
	     bus_alloc_resource_any(sc->ciss_dev, SYS_RES_MEMORY,
				    &sc->ciss_cfg_rid, RF_ACTIVE)) == NULL) {
	    ciss_printf(sc, "can't allocate config window\n");
	    return(ENXIO);
	}
	cbase = (uintptr_t)rman_get_virtual(sc->ciss_cfg_resource);
	csize = rman_get_end(sc->ciss_cfg_resource) -
	    rman_get_start(sc->ciss_cfg_resource) + 1;
    } else {
	cbase = (uintptr_t)rman_get_virtual(sc->ciss_regs_resource);
	csize = rman_get_end(sc->ciss_regs_resource) -
	    rman_get_start(sc->ciss_regs_resource) + 1;
    }
    cofs = CISS_TL_SIMPLE_READ(sc, CISS_TL_SIMPLE_CFG_OFF);

    /*
     * Use the base/size/offset values we just calculated to
     * sanity-check the config structure.  If it's OK, point to it.
     */
    if ((cofs + sizeof(struct ciss_config_table)) > csize) {
	ciss_printf(sc, "config table outside window\n");
	return(ENXIO);
    }
    sc->ciss_cfg = (struct ciss_config_table *)(cbase + cofs);
    debug(1, "config struct at %p", sc->ciss_cfg);

    /*
     * Calculate the number of request structures/commands we are
     * going to provide for this adapter.
     */
    sc->ciss_max_requests = min(CISS_MAX_REQUESTS, sc->ciss_cfg->max_outstanding_commands);

    /*
     * Validate the config structure.  If we supported other transport
     * methods, we could select amongst them at this point in time.
     */
    if (strncmp(sc->ciss_cfg->signature, "CISS", 4)) {
	ciss_printf(sc, "config signature mismatch (got '%c%c%c%c')\n",
		    sc->ciss_cfg->signature[0], sc->ciss_cfg->signature[1],
		    sc->ciss_cfg->signature[2], sc->ciss_cfg->signature[3]);
	return(ENXIO);
    }

    /*
     * Select the mode of operation, prefer Performant.
     */
    if (!(sc->ciss_cfg->supported_methods &
	(CISS_TRANSPORT_METHOD_SIMPLE | CISS_TRANSPORT_METHOD_PERF))) {
	ciss_printf(sc, "No supported transport layers: 0x%x\n",
	    sc->ciss_cfg->supported_methods);
    }

    switch (ciss_force_transport) {
    case 1:
	supported_methods = CISS_TRANSPORT_METHOD_SIMPLE;
	break;
    case 2:
	supported_methods = CISS_TRANSPORT_METHOD_PERF;
	break;
    default:
        /*
         * Override the capabilities of the BOARD and specify SIMPLE
         * MODE 
         */
        if (ciss_vendor_data[i].flags & CISS_BOARD_SIMPLE)
                supported_methods = CISS_TRANSPORT_METHOD_SIMPLE;
        else
                supported_methods = sc->ciss_cfg->supported_methods;
        break;
    }

setup:
    if ((supported_methods & CISS_TRANSPORT_METHOD_PERF) != 0) {
	method = CISS_TRANSPORT_METHOD_PERF;
	sc->ciss_perf = (struct ciss_perf_config *)(cbase + cofs +
	    sc->ciss_cfg->transport_offset);
	if (ciss_init_perf(sc)) {
	    supported_methods &= ~method;
	    goto setup;
	}
    } else if (supported_methods & CISS_TRANSPORT_METHOD_SIMPLE) {
	method = CISS_TRANSPORT_METHOD_SIMPLE;
    } else {
	ciss_printf(sc, "No supported transport methods: 0x%x\n",
	    sc->ciss_cfg->supported_methods);
	return(ENXIO);
    }

    /*
     * Tell it we're using the low 4GB of RAM.  Set the default interrupt
     * coalescing options.
     */
    sc->ciss_cfg->requested_method = method;
    sc->ciss_cfg->command_physlimit = 0;
    sc->ciss_cfg->interrupt_coalesce_delay = CISS_INTERRUPT_COALESCE_DELAY;
    sc->ciss_cfg->interrupt_coalesce_count = CISS_INTERRUPT_COALESCE_COUNT;

#ifdef __i386__
    sc->ciss_cfg->host_driver |= CISS_DRIVER_SCSI_PREFETCH;
#endif

    if (ciss_update_config(sc)) {
	ciss_printf(sc, "adapter refuses to accept config update (IDBR 0x%x)\n",
		    CISS_TL_SIMPLE_READ(sc, CISS_TL_SIMPLE_IDBR));
	return(ENXIO);
    }
    if ((sc->ciss_cfg->active_method & method) == 0) {
	supported_methods &= ~method;
	if (supported_methods == 0) {
	    ciss_printf(sc, "adapter refuses to go into available transports "
		"mode (0x%x, 0x%x)\n", supported_methods,
		sc->ciss_cfg->active_method);
	    return(ENXIO);
	} else 
	    goto setup;
    }

    /*
     * Wait for the adapter to come ready.
     */
    if ((error = ciss_wait_adapter(sc)) != 0)
	return(error);

    /* Prepare to possibly use MSIX and/or PERFORMANT interrupts.  Normal
     * interrupts have a rid of 0, this will be overridden if MSIX is used.
     */
    sc->ciss_irq_rid[0] = 0;
    if (method == CISS_TRANSPORT_METHOD_PERF) {
	ciss_printf(sc, "PERFORMANT Transport\n");
	if ((ciss_force_interrupt != 1) && (ciss_setup_msix(sc) == 0)) {
	    intr = ciss_perf_msi_intr;
	} else {
	    intr = ciss_perf_intr;
	}
	/* XXX The docs say that the 0x01 bit is only for SAS controllers.
	 * Unfortunately, there is no good way to know if this is a SAS
	 * controller.  Hopefully enabling this bit universally will work OK.
	 * It seems to work fine for SA6i controllers.
	 */
	sc->ciss_interrupt_mask = CISS_TL_PERF_INTR_OPQ | CISS_TL_PERF_INTR_MSI;

    } else {
	ciss_printf(sc, "SIMPLE Transport\n");
	/* MSIX doesn't seem to work in SIMPLE mode, only enable if it forced */
	if (ciss_force_interrupt == 2)
	    /* If this fails, we automatically revert to INTx */
	    ciss_setup_msix(sc);
	sc->ciss_perf = NULL;
	intr = ciss_intr;
	sc->ciss_interrupt_mask = sqmask;
    }

    /*
     * Turn off interrupts before we go routing anything.
     */
    CISS_TL_SIMPLE_DISABLE_INTERRUPTS(sc);

    /*
     * Allocate and set up our interrupt.
     */
    if ((sc->ciss_irq_resource =
	 bus_alloc_resource_any(sc->ciss_dev, SYS_RES_IRQ, &sc->ciss_irq_rid[0],
				RF_ACTIVE | RF_SHAREABLE)) == NULL) {
	ciss_printf(sc, "can't allocate interrupt\n");
	return(ENXIO);
    }

    if (bus_setup_intr(sc->ciss_dev, sc->ciss_irq_resource,
		       INTR_TYPE_CAM|INTR_MPSAFE, NULL, intr, sc,
		       &sc->ciss_intr)) {
	ciss_printf(sc, "can't set up interrupt\n");
	return(ENXIO);
    }

    /*
     * Allocate the parent bus DMA tag appropriate for our PCI
     * interface.
     *
     * Note that "simple" adapters can only address within a 32-bit
     * span.
     */
    if (bus_dma_tag_create(bus_get_dma_tag(sc->ciss_dev),/* PCI parent */
			   1, 0, 			/* alignment, boundary */
			   BUS_SPACE_MAXADDR,		/* lowaddr */
			   BUS_SPACE_MAXADDR, 		/* highaddr */
			   NULL, NULL, 			/* filter, filterarg */
			   BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
			   BUS_SPACE_UNRESTRICTED,	/* nsegments */
			   BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
			   0,				/* flags */
			   NULL, NULL,			/* lockfunc, lockarg */
			   &sc->ciss_parent_dmat)) {
	ciss_printf(sc, "can't allocate parent DMA tag\n");
	return(ENOMEM);
    }

    /*
     * Create DMA tag for mapping buffers into adapter-addressable
     * space.
     */
    if (bus_dma_tag_create(sc->ciss_parent_dmat, 	/* parent */
			   1, 0, 			/* alignment, boundary */
			   BUS_SPACE_MAXADDR,		/* lowaddr */
			   BUS_SPACE_MAXADDR, 		/* highaddr */
			   NULL, NULL, 			/* filter, filterarg */
			   (CISS_MAX_SG_ELEMENTS - 1) * PAGE_SIZE, /* maxsize */
			   CISS_MAX_SG_ELEMENTS,	/* nsegments */
			   BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
			   BUS_DMA_ALLOCNOW,		/* flags */
			   busdma_lock_mutex, &sc->ciss_mtx,	/* lockfunc, lockarg */
			   &sc->ciss_buffer_dmat)) {
	ciss_printf(sc, "can't allocate buffer DMA tag\n");
	return(ENOMEM);
    }
    return(0);
}