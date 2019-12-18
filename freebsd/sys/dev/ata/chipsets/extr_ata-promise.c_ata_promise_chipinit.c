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
typedef  int u_int32_t ;
struct ata_promise_sx4 {int /*<<< orphan*/  busy; int /*<<< orphan*/  queue; int /*<<< orphan*/  mtx; } ;
struct ata_pci_controller {int channels; void* r_res1; void* r_rid1; void* r_type1; void* r_res2; void* r_rid2; void* r_type2; int /*<<< orphan*/  getrev; void* setmode; void* reset; void* ch_detach; void* ch_attach; TYPE_1__* chip; struct ata_promise_sx4* chipset_data; int /*<<< orphan*/  handle; int /*<<< orphan*/  r_irq; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int cfg1; int const cfg2; } ;

/* Variables and functions */
 int ATA_INB (void*,int) ; 
 int ATA_INL (void*,int) ; 
 int /*<<< orphan*/  ATA_INTR_FLAGS ; 
 int /*<<< orphan*/  ATA_OUTB (void*,int,int) ; 
 int /*<<< orphan*/  ATA_OUTL (void*,int,int) ; 
 int /*<<< orphan*/  BUS_SPACE_MAP_LINEAR ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_ATAPCI ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 void* PCIR_BAR (int) ; 
#define  PR_CMBO 136 
#define  PR_CMBO2 135 
#define  PR_MIO 134 
#define  PR_NEW 133 
#define  PR_OLD 132 
#define  PR_PATA 131 
#define  PR_SATA 130 
#define  PR_SATA2 129 
 int const PR_SX4X ; 
#define  PR_TX 128 
 int /*<<< orphan*/  RF_ACTIVE ; 
 void* SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ata_generic_intr ; 
 void* ata_pci_ch_detach ; 
 void* ata_promise_ch_attach ; 
 void* ata_promise_mio_ch_attach ; 
 void* ata_promise_mio_ch_detach ; 
 int /*<<< orphan*/  ata_promise_mio_getrev ; 
 int /*<<< orphan*/  ata_promise_mio_intr ; 
 void* ata_promise_mio_reset ; 
 void* ata_promise_mio_setmode ; 
 void* ata_promise_setmode ; 
 int /*<<< orphan*/  ata_promise_sx4_intr ; 
 void* ata_promise_tx2_ch_attach ; 
 scalar_t__ ata_setup_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,void*,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,void*,void*,void*) ; 
 int /*<<< orphan*/  bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ata_pci_controller*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ata_pci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct ata_promise_sx4* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (void*) ; 
 int /*<<< orphan*/  rman_get_bustag (void*) ; 
 int /*<<< orphan*/  rman_get_size (void*) ; 

__attribute__((used)) static int
ata_promise_chipinit(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(dev);
    int stat_reg;

    if (ata_setup_interrupt(dev, ata_generic_intr))
	return ENXIO;

    switch  (ctlr->chip->cfg1) {
    case PR_NEW:
	/* setup clocks */
	ATA_OUTB(ctlr->r_res1, 0x11, ATA_INB(ctlr->r_res1, 0x11) | 0x0a);
	/* FALLTHROUGH */

    case PR_OLD:
	/* enable burst mode */
	ATA_OUTB(ctlr->r_res1, 0x1f, ATA_INB(ctlr->r_res1, 0x1f) | 0x01);
	ctlr->ch_attach = ata_promise_ch_attach;
	ctlr->ch_detach = ata_pci_ch_detach;
	ctlr->setmode = ata_promise_setmode;
	return 0;

    case PR_TX:
	ctlr->ch_attach = ata_promise_tx2_ch_attach;
	ctlr->ch_detach = ata_pci_ch_detach;
	ctlr->setmode = ata_promise_setmode;
	return 0;

    case PR_MIO:
	ctlr->r_type1 = SYS_RES_MEMORY;
	ctlr->r_rid1 = PCIR_BAR(4);
	if (!(ctlr->r_res1 = bus_alloc_resource_any(dev, ctlr->r_type1,
						    &ctlr->r_rid1, RF_ACTIVE)))
	    goto failnfree;

#ifdef __sparc64__
	if (ctlr->chip->cfg2 == PR_SX4X &&
	    !bus_space_map(rman_get_bustag(ctlr->r_res1),
	    rman_get_bushandle(ctlr->r_res1), rman_get_size(ctlr->r_res1),
	    BUS_SPACE_MAP_LINEAR, NULL))
		goto failnfree;
#endif

	ctlr->r_type2 = SYS_RES_MEMORY;
	ctlr->r_rid2 = PCIR_BAR(3);
	if (!(ctlr->r_res2 = bus_alloc_resource_any(dev, ctlr->r_type2,
						    &ctlr->r_rid2, RF_ACTIVE)))
	    goto failnfree;

	if (ctlr->chip->cfg2 == PR_SX4X) {
	    struct ata_promise_sx4 *hpkt;
	    u_int32_t dimm = ATA_INL(ctlr->r_res2, 0x000c0080);

	    if (bus_teardown_intr(dev, ctlr->r_irq, ctlr->handle) ||
		bus_setup_intr(dev, ctlr->r_irq, ATA_INTR_FLAGS, NULL,
			       ata_promise_sx4_intr, ctlr, &ctlr->handle)) {
		device_printf(dev, "unable to setup interrupt\n");
		goto failnfree;
	    }

	    /* print info about cache memory */
	    device_printf(dev, "DIMM size %dMB @ 0x%08x%s\n",
			  (((dimm >> 16) & 0xff)-((dimm >> 24) & 0xff)+1) << 4,
			  ((dimm >> 24) & 0xff),
			  ATA_INL(ctlr->r_res2, 0x000c0088) & (1<<16) ?
			  " ECC enabled" : "" );

	    /* adjust cache memory parameters */
	    ATA_OUTL(ctlr->r_res2, 0x000c000c, 
		     (ATA_INL(ctlr->r_res2, 0x000c000c) & 0xffff0000));

	    /* setup host packet controls */
	    hpkt = malloc(sizeof(struct ata_promise_sx4),
			  M_ATAPCI, M_NOWAIT | M_ZERO);
	    if (hpkt == NULL) {
		device_printf(dev, "Cannot allocate HPKT\n");
		goto failnfree;
	    }
	    mtx_init(&hpkt->mtx, "ATA promise HPKT lock", NULL, MTX_DEF);
	    TAILQ_INIT(&hpkt->queue);
	    hpkt->busy = 0;
	    ctlr->chipset_data = hpkt;
	    ctlr->ch_attach = ata_promise_mio_ch_attach;
	    ctlr->ch_detach = ata_promise_mio_ch_detach;
	    ctlr->reset = ata_promise_mio_reset;
	    ctlr->setmode = ata_promise_setmode;
	    ctlr->channels = 4;
	    return 0;
	}

	/* mio type controllers need an interrupt intercept */
	if (bus_teardown_intr(dev, ctlr->r_irq, ctlr->handle) ||
	    bus_setup_intr(dev, ctlr->r_irq, ATA_INTR_FLAGS, NULL,
			       ata_promise_mio_intr, ctlr, &ctlr->handle)) {
		device_printf(dev, "unable to setup interrupt\n");
		goto failnfree;
	}

	switch (ctlr->chip->cfg2) {
	case PR_PATA:
	    ctlr->channels = ((ATA_INL(ctlr->r_res2, 0x48) & 0x01) > 0) +
			     ((ATA_INL(ctlr->r_res2, 0x48) & 0x02) > 0) + 2;
	    goto sata150;
	case PR_CMBO:
	    ctlr->channels = 3;
	    goto sata150;
	case PR_SATA:
	    ctlr->channels = 4;
sata150:
	    stat_reg = 0x6c;
	    break;

	case PR_CMBO2: 
	    ctlr->channels = 3;
	    goto sataii;
	case PR_SATA2:
	default:
	    ctlr->channels = 4;
sataii:
	    stat_reg = 0x60;
	    break;
	}

	/* prime fake interrupt register */
	ctlr->chipset_data = (void *)(uintptr_t)0xffffffff;

	/* clear SATA status and unmask interrupts */
	ATA_OUTL(ctlr->r_res2, stat_reg, 0x000000ff);

	/* enable "long burst length" on gen2 chips */
	if ((ctlr->chip->cfg2 == PR_SATA2) || (ctlr->chip->cfg2 == PR_CMBO2))
	    ATA_OUTL(ctlr->r_res2, 0x44, ATA_INL(ctlr->r_res2, 0x44) | 0x2000);

	ctlr->ch_attach = ata_promise_mio_ch_attach;
	ctlr->ch_detach = ata_promise_mio_ch_detach;
	ctlr->reset = ata_promise_mio_reset;
	ctlr->setmode = ata_promise_mio_setmode;
	ctlr->getrev = ata_promise_mio_getrev;

	return 0;
    }

failnfree:
    if (ctlr->r_res2)
	bus_release_resource(dev, ctlr->r_type2, ctlr->r_rid2, ctlr->r_res2);
    if (ctlr->r_res1)
	bus_release_resource(dev, ctlr->r_type1, ctlr->r_rid1, ctlr->r_res1);
    return ENXIO;
}