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
struct cmx_softc {int /*<<< orphan*/  mtx; int /*<<< orphan*/  ch; int /*<<< orphan*/  ih; void* irq; int /*<<< orphan*/  irq_rid; void* ioport; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; int /*<<< orphan*/  ioport_rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INTR_TYPE_TTY ; 
 int MTX_DEF ; 
 int MTX_RECURSE ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cmx_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmx_intr ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct cmx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (void*) ; 
 int /*<<< orphan*/  rman_get_bustag (void*) ; 

int
cmx_alloc_resources(device_t dev)
{
	struct cmx_softc *sc = device_get_softc(dev);
#ifdef CMX_INTR
	int rv;
#endif

	sc->ioport = bus_alloc_resource_any(dev, SYS_RES_IOPORT,
			&sc->ioport_rid, RF_ACTIVE);
	if (!sc->ioport) {
		device_printf(dev, "failed to allocate io port\n");
		return ENOMEM;
	}
	sc->bst = rman_get_bustag(sc->ioport);
	sc->bsh = rman_get_bushandle(sc->ioport);

#ifdef CMX_INTR
	sc->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ,
			&sc->irq_rid, RF_ACTIVE);
	if (!sc->irq) {
		device_printf(dev, "failed to allocate irq\n");
		return ENOMEM;
	}
	if ((rv = bus_setup_intr(dev, sc->irq, INTR_TYPE_TTY,
			cmx_intr, sc, &sc->ih)) != 0) {
		device_printf(dev, "failed to set up irq\n");
		return ENOMEM;
	}
#endif

	mtx_init(&sc->mtx, device_get_nameunit(dev),
			"cmx softc lock",
			MTX_DEF | MTX_RECURSE);
	callout_init_mtx(&sc->ch, &sc->mtx, 0);

	return 0;
}