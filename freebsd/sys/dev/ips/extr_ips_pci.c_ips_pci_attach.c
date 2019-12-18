#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* ich_arg; int /*<<< orphan*/  ich_func; } ;
struct TYPE_5__ {TYPE_3__ ips_ich; int /*<<< orphan*/  queue; int /*<<< orphan*/  adapter_dmatag; int /*<<< orphan*/  irqcookie; void* ips_adapter_intr; void* irqres; void* irqrid; int /*<<< orphan*/ * iores; void* rid; int /*<<< orphan*/  iotype; void* ips_poll_cmd; void* ips_issue_cmd; void* ips_adapter_reinit; int /*<<< orphan*/  queue_mtx; int /*<<< orphan*/  timer; int /*<<< orphan*/  cmd_sema; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ips_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int /*<<< orphan*/  DEVICE_PRINTF (int,int /*<<< orphan*/ ,char*) ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 scalar_t__ IPS_COPPERHEAD_DEVICE_ID ; 
 scalar_t__ IPS_MARCO_DEVICE_ID ; 
 int /*<<< orphan*/  IPS_MAX_SG_ELEMENTS ; 
 scalar_t__ IPS_MORPHEUS_DEVICE_ID ; 
 int /*<<< orphan*/  MTX_DEF ; 
 void* PCIR_BAR (int) ; 
 int /*<<< orphan*/  PRINTF (int,char*) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bioq_init (int /*<<< orphan*/ *) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *,void*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ config_intrhook_establish (TYPE_3__*) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 void* ips_copperhead_intr ; 
 void* ips_copperhead_poll ; 
 void* ips_copperhead_reinit ; 
 int /*<<< orphan*/  ips_intrhook ; 
 void* ips_issue_copperhead_cmd ; 
 void* ips_issue_morpheus_cmd ; 
 void* ips_morpheus_intr ; 
 void* ips_morpheus_poll ; 
 void* ips_morpheus_reinit ; 
 int /*<<< orphan*/  ips_pci_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ips_pci_attach(device_t dev)
{
        ips_softc_t *sc;

        DEVICE_PRINTF(1, dev, "in attach.\n");
        sc = (ips_softc_t *)device_get_softc(dev);
        sc->dev = dev;
	mtx_init(&sc->queue_mtx, "IPS bioqueue lock", NULL, MTX_DEF);
	sema_init(&sc->cmd_sema, 0, "IPS Command Semaphore");
	callout_init_mtx(&sc->timer, &sc->queue_mtx, 0);

        if(pci_get_device(dev) == IPS_MORPHEUS_DEVICE_ID){
		sc->ips_adapter_reinit = ips_morpheus_reinit;
                sc->ips_adapter_intr = ips_morpheus_intr;
		sc->ips_issue_cmd    = ips_issue_morpheus_cmd;
		sc->ips_poll_cmd     = ips_morpheus_poll;
        } else if(pci_get_device(dev) == IPS_COPPERHEAD_DEVICE_ID){
		sc->ips_adapter_reinit = ips_copperhead_reinit;
                sc->ips_adapter_intr = ips_copperhead_intr;
		sc->ips_issue_cmd    = ips_issue_copperhead_cmd;
		sc->ips_poll_cmd     = ips_copperhead_poll;
	} else if (pci_get_device(dev) == IPS_MARCO_DEVICE_ID){
		sc->ips_adapter_reinit = ips_morpheus_reinit;
		sc->ips_adapter_intr = ips_morpheus_intr;
		sc->ips_issue_cmd = ips_issue_morpheus_cmd;
		sc->ips_poll_cmd     = ips_morpheus_poll;
	} else
                goto error;
        /* make sure busmastering is on */
	pci_enable_busmaster(dev);
        /* setting up io space */
        sc->iores = NULL;
	PRINTF(10, "trying MEMIO\n");
	if(pci_get_device(dev) == IPS_COPPERHEAD_DEVICE_ID)
		sc->rid = PCIR_BAR(1);
	else
		sc->rid = PCIR_BAR(0);
	sc->iotype = SYS_RES_MEMORY;
	sc->iores = bus_alloc_resource_any(dev, sc->iotype, &sc->rid,
	    RF_ACTIVE);
        if(!sc->iores){
                PRINTF(10, "trying PORTIO\n");
                sc->rid = PCIR_BAR(0);
                sc->iotype = SYS_RES_IOPORT;
                sc->iores = bus_alloc_resource_any(dev, sc->iotype, 
			&sc->rid, RF_ACTIVE);
        }
        if(sc->iores == NULL){
                device_printf(dev, "resource allocation failed\n");
                return (ENXIO);
        }
        /*allocate an interrupt. when does the irq become active? after leaving attach? */
        sc->irqrid = 0;
        if(!(sc->irqres = bus_alloc_resource_any(dev, SYS_RES_IRQ,
		&sc->irqrid, RF_SHAREABLE | RF_ACTIVE))){
                device_printf(dev, "irq allocation failed\n");
                goto error;
        }
	if(bus_setup_intr(dev, sc->irqres, INTR_TYPE_BIO|INTR_MPSAFE, NULL, 
	    sc->ips_adapter_intr, sc, &sc->irqcookie)){
                device_printf(dev, "irq setup failed\n");
                goto error;
        }
	if (bus_dma_tag_create(	/* PCI parent */bus_get_dma_tag(dev),
				/* alignemnt */	1,
				/* boundary  */	0,
				/* lowaddr   */	BUS_SPACE_MAXADDR_32BIT,
				/* highaddr  */	BUS_SPACE_MAXADDR,
				/* filter    */	NULL,
				/* filterarg */	NULL,
				/* maxsize   */	BUS_SPACE_MAXSIZE_32BIT,
				/* numsegs   */	IPS_MAX_SG_ELEMENTS,
				/* maxsegsize*/	BUS_SPACE_MAXSIZE_32BIT,
				/* flags     */	0,
				/* lockfunc  */ NULL,
				/* lockarg   */ NULL,
				&sc->adapter_dmatag) != 0) {
                device_printf(dev, "can't alloc dma tag\n");
                goto error;
        }
	sc->ips_ich.ich_func = ips_intrhook;
	sc->ips_ich.ich_arg = sc;
	bioq_init(&sc->queue);
	if (config_intrhook_establish(&sc->ips_ich) != 0) {
		printf("IPS can't establish configuration hook\n");
		goto error;
	}
        return 0;
error:
	ips_pci_free(sc);
        return (ENXIO);
}