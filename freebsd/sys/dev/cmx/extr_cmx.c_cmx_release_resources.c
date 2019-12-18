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
struct cmx_softc {int /*<<< orphan*/ * ioport; int /*<<< orphan*/  ioport_rid; int /*<<< orphan*/ * irq; int /*<<< orphan*/  irq_rid; int /*<<< orphan*/ * ih; int /*<<< orphan*/  mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_deactivate_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct cmx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

void
cmx_release_resources(device_t dev)
{
	struct cmx_softc *sc = device_get_softc(dev);

	mtx_destroy(&sc->mtx);

#ifdef CMX_INTR
	if (sc->ih) {
		bus_teardown_intr(dev, sc->irq, sc->ih);
		sc->ih = NULL;
	}
	if (sc->irq) {
		bus_release_resource(dev, SYS_RES_IRQ,
				sc->irq_rid, sc->irq);
		sc->irq = NULL;
	}
#endif

	if (sc->ioport) {
		bus_deactivate_resource(dev, SYS_RES_IOPORT,
				sc->ioport_rid, sc->ioport);
		bus_release_resource(dev, SYS_RES_IOPORT,
				sc->ioport_rid, sc->ioport);
		sc->ioport = NULL;
	}
	return;
}