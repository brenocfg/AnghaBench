#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int64_t ;
typedef  int u_int32_t ;
struct tws_softc {int mfa_base; int irqs; int /*<<< orphan*/  tws_clist; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  gen_lock; int /*<<< orphan*/  sim_lock; int /*<<< orphan*/  q_lock; void* reg_res_id; int /*<<< orphan*/ * reg_res; int /*<<< orphan*/  tws_dev; void* mfa_res_id; int /*<<< orphan*/ * mfa_res; int /*<<< orphan*/ ** irq_res; void** irq_res_id; scalar_t__ cmd_tag; int /*<<< orphan*/  cmd_map; scalar_t__ dma_mem; scalar_t__ dma_mem_phys; TYPE_1__* tws_cdev; int /*<<< orphan*/  device_id; int /*<<< orphan*/  intr_type; void* bus_mfa_handle; void* bus_mfa_tag; void* bus_handle; void* bus_tag; int /*<<< orphan*/ * tws_oidp; int /*<<< orphan*/  stats_timer; int /*<<< orphan*/  subdevice_id; int /*<<< orphan*/  subvendor_id; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {struct tws_softc* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_MEMORY_RES ; 
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int ENXIO ; 
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  GID_OPERATOR ; 
 int MTX_DEF ; 
 int MTX_RECURSE ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/ * SYSCTL_ADD_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_STRING (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSCTL_TREE_NODE_ADD ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int TWS_BIT2 ; 
 int /*<<< orphan*/  TWS_CAM_ATTACH ; 
 int /*<<< orphan*/  TWS_CTLR_INIT_FAILURE ; 
 int /*<<< orphan*/  TWS_DRIVER_VERSION_STRING ; 
 int /*<<< orphan*/  TWS_INIT_COMPLETE ; 
 int /*<<< orphan*/  TWS_INIT_FAILURE ; 
 int /*<<< orphan*/  TWS_INIT_START ; 
 int /*<<< orphan*/  TWS_INTx ; 
 int /*<<< orphan*/  TWS_MSI ; 
 void* TWS_PCI_BAR0 ; 
 void* TWS_PCI_BAR1 ; 
 void* TWS_PCI_BAR2 ; 
 int /*<<< orphan*/  TWS_TRACE (struct tws_softc*,char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  _hw ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_unload (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  destroy_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct tws_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 TYPE_1__* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_subdevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_subvendor (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 void* rman_get_bushandle (int /*<<< orphan*/ *) ; 
 void* rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_ctx_init (int /*<<< orphan*/ *) ; 
 int tws_cam_attach (struct tws_softc*) ; 
 int /*<<< orphan*/  tws_cdevsw ; 
 scalar_t__ tws_enable_msi ; 
 scalar_t__ tws_init (struct tws_softc*) ; 
 scalar_t__ tws_init_ctlr (struct tws_softc*) ; 
 scalar_t__ tws_init_trace_q (struct tws_softc*) ; 
 int /*<<< orphan*/  tws_log (struct tws_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tws_send_event (struct tws_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ tws_setup_irq (struct tws_softc*) ; 
 int /*<<< orphan*/  tws_teardown_intr (struct tws_softc*) ; 

__attribute__((used)) static int
tws_attach(device_t dev)
{
    struct tws_softc *sc = device_get_softc(dev);
    u_int32_t bar;
    int error=0,i;

    /* no tracing yet */
    /* Look up our softc and initialize its fields. */
    sc->tws_dev = dev;
    sc->device_id = pci_get_device(dev);
    sc->subvendor_id = pci_get_subvendor(dev);
    sc->subdevice_id = pci_get_subdevice(dev);

    /* Intialize mutexes */
    mtx_init( &sc->q_lock, "tws_q_lock", NULL, MTX_DEF);
    mtx_init( &sc->sim_lock,  "tws_sim_lock", NULL, MTX_DEF);
    mtx_init( &sc->gen_lock,  "tws_gen_lock", NULL, MTX_DEF);
    mtx_init( &sc->io_lock,  "tws_io_lock", NULL, MTX_DEF | MTX_RECURSE);
    callout_init(&sc->stats_timer, 1);

    if ( tws_init_trace_q(sc) == FAILURE )
        printf("trace init failure\n");
    /* send init event */
    mtx_lock(&sc->gen_lock);
    tws_send_event(sc, TWS_INIT_START);
    mtx_unlock(&sc->gen_lock);


#if _BYTE_ORDER == _BIG_ENDIAN
    TWS_TRACE(sc, "BIG endian", 0, 0);
#endif
    /* sysctl context setup */
    sysctl_ctx_init(&sc->tws_clist);
    sc->tws_oidp = SYSCTL_ADD_NODE(&sc->tws_clist,
                                   SYSCTL_STATIC_CHILDREN(_hw), OID_AUTO,
                                   device_get_nameunit(dev), 
                                   CTLFLAG_RD, 0, "");
    if ( sc->tws_oidp == NULL ) {
        tws_log(sc, SYSCTL_TREE_NODE_ADD);
        goto attach_fail_1;
    }
    SYSCTL_ADD_STRING(&sc->tws_clist, SYSCTL_CHILDREN(sc->tws_oidp),
                      OID_AUTO, "driver_version", CTLFLAG_RD,
                      TWS_DRIVER_VERSION_STRING, 0, "TWS driver version");

    pci_enable_busmaster(dev);

    bar = pci_read_config(dev, TWS_PCI_BAR0, 4);
    TWS_TRACE_DEBUG(sc, "bar0 ", bar, 0);
    bar = pci_read_config(dev, TWS_PCI_BAR1, 4);
    bar = bar & ~TWS_BIT2;
    TWS_TRACE_DEBUG(sc, "bar1 ", bar, 0);
 
    /* MFA base address is BAR2 register used for 
     * push mode. Firmware will evatualy move to 
     * pull mode during witch this needs to change
     */ 
#ifndef TWS_PULL_MODE_ENABLE
    sc->mfa_base = (u_int64_t)pci_read_config(dev, TWS_PCI_BAR2, 4);
    sc->mfa_base = sc->mfa_base & ~TWS_BIT2;
    TWS_TRACE_DEBUG(sc, "bar2 ", sc->mfa_base, 0);
#endif

    /* allocate MMIO register space */ 
    sc->reg_res_id = TWS_PCI_BAR1; /* BAR1 offset */
    if ((sc->reg_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
                                &(sc->reg_res_id), RF_ACTIVE))
                                == NULL) {
        tws_log(sc, ALLOC_MEMORY_RES);
        goto attach_fail_1;
    }
    sc->bus_tag = rman_get_bustag(sc->reg_res);
    sc->bus_handle = rman_get_bushandle(sc->reg_res);

#ifndef TWS_PULL_MODE_ENABLE
    /* Allocate bus space for inbound mfa */ 
    sc->mfa_res_id = TWS_PCI_BAR2; /* BAR2 offset */
    if ((sc->mfa_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
                          &(sc->mfa_res_id), RF_ACTIVE))
                                == NULL) {
        tws_log(sc, ALLOC_MEMORY_RES);
        goto attach_fail_2;
    }
    sc->bus_mfa_tag = rman_get_bustag(sc->mfa_res);
    sc->bus_mfa_handle = rman_get_bushandle(sc->mfa_res);
#endif

    /* Allocate and register our interrupt. */
    sc->intr_type = TWS_INTx; /* default */

    if ( tws_enable_msi )
        sc->intr_type = TWS_MSI;
    if ( tws_setup_irq(sc) == FAILURE ) {
        tws_log(sc, ALLOC_MEMORY_RES);
        goto attach_fail_3;
    }

    /*
     * Create a /dev entry for this device.  The kernel will assign us
     * a major number automatically.  We use the unit number of this
     * device as the minor number and name the character device
     * "tws<unit>".
     */
    sc->tws_cdev = make_dev(&tws_cdevsw, device_get_unit(dev),
        UID_ROOT, GID_OPERATOR, S_IRUSR | S_IWUSR, "tws%u", 
        device_get_unit(dev));
    sc->tws_cdev->si_drv1 = sc;

    if ( tws_init(sc) == FAILURE ) {
        tws_log(sc, TWS_INIT_FAILURE);
        goto attach_fail_4;
    }
    if ( tws_init_ctlr(sc) == FAILURE ) {
        tws_log(sc, TWS_CTLR_INIT_FAILURE);
        goto attach_fail_4;
    }
    if ((error = tws_cam_attach(sc))) {
        tws_log(sc, TWS_CAM_ATTACH);
        goto attach_fail_4;
    }
    /* send init complete event */
    mtx_lock(&sc->gen_lock);
    tws_send_event(sc, TWS_INIT_COMPLETE);
    mtx_unlock(&sc->gen_lock);
        
    TWS_TRACE_DEBUG(sc, "attached successfully", 0, sc->device_id);
    return(0);

attach_fail_4:
    tws_teardown_intr(sc);
    destroy_dev(sc->tws_cdev);
    if (sc->dma_mem_phys)
	    bus_dmamap_unload(sc->cmd_tag, sc->cmd_map);
    if (sc->dma_mem)
	    bus_dmamem_free(sc->cmd_tag, sc->dma_mem, sc->cmd_map);
    if (sc->cmd_tag)
	    bus_dma_tag_destroy(sc->cmd_tag);
attach_fail_3:
    for(i=0;i<sc->irqs;i++) {
        if ( sc->irq_res[i] ){
            if (bus_release_resource(sc->tws_dev,
                 SYS_RES_IRQ, sc->irq_res_id[i], sc->irq_res[i]))
                TWS_TRACE(sc, "bus irq res", 0, 0);
        }
    }
#ifndef TWS_PULL_MODE_ENABLE
attach_fail_2: 
#endif
    if ( sc->mfa_res ){
        if (bus_release_resource(sc->tws_dev,
                 SYS_RES_MEMORY, sc->mfa_res_id, sc->mfa_res))
            TWS_TRACE(sc, "bus release ", 0, sc->mfa_res_id);
    }
    if ( sc->reg_res ){
        if (bus_release_resource(sc->tws_dev,
                 SYS_RES_MEMORY, sc->reg_res_id, sc->reg_res))
            TWS_TRACE(sc, "bus release2 ", 0, sc->reg_res_id);
    }
attach_fail_1:
    mtx_destroy(&sc->q_lock);
    mtx_destroy(&sc->sim_lock);
    mtx_destroy(&sc->gen_lock);
    mtx_destroy(&sc->io_lock);
    sysctl_ctx_free(&sc->tws_clist);
    return (ENXIO);
}