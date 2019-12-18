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
struct bcm_mbox_softc {int /*<<< orphan*/  property_chan_lock; scalar_t__* have_message; scalar_t__* msg; int /*<<< orphan*/  lock; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/  intr_hl; int /*<<< orphan*/ * mem_res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BCM2835_MBOX_CHANS ; 
 int /*<<< orphan*/  CONFIG_DATA_IRQ ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  REG_CONFIG ; 
 int /*<<< orphan*/  REG_READ ; 
 int /*<<< orphan*/  REG_STATUS ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int STATUS_EMPTY ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bcm_mbox_intr ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bcm_mbox_softc*,int /*<<< orphan*/ *) ; 
 struct bcm_mbox_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int mbox_read_4 (struct bcm_mbox_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_write_4 (struct bcm_mbox_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
bcm_mbox_attach(device_t dev)
{
	struct bcm_mbox_softc *sc = device_get_softc(dev);
	int i;
	int rid = 0;

	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (sc->mem_res == NULL) {
		device_printf(dev, "could not allocate memory resource\n");
		return (ENXIO);
	}

	sc->bst = rman_get_bustag(sc->mem_res);
	sc->bsh = rman_get_bushandle(sc->mem_res);

	rid = 0;
	sc->irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid, RF_ACTIVE);
	if (sc->irq_res == NULL) {
		device_printf(dev, "could not allocate interrupt resource\n");
		return (ENXIO);
	}

	/* Setup and enable the timer */
	if (bus_setup_intr(dev, sc->irq_res, INTR_MPSAFE | INTR_TYPE_MISC, 
	    NULL, bcm_mbox_intr, sc, &sc->intr_hl) != 0) {
		bus_release_resource(dev, SYS_RES_IRQ, rid, sc->irq_res);
		device_printf(dev, "Unable to setup the clock irq handler.\n");
		return (ENXIO);
	}

	mtx_init(&sc->lock, "vcio mbox", NULL, MTX_DEF);
	for (i = 0; i < BCM2835_MBOX_CHANS; i++) {
		sc->msg[i] = 0;
		sc->have_message[i] = 0;
	}

	sx_init(&sc->property_chan_lock, "mboxprop");

	/* Read all pending messages */
	while ((mbox_read_4(sc, REG_STATUS) & STATUS_EMPTY) == 0)
		(void)mbox_read_4(sc, REG_READ);

	mbox_write_4(sc, REG_CONFIG, CONFIG_DATA_IRQ);

	return (0);
}