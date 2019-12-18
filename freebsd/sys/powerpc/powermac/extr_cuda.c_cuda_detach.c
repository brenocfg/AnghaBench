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
struct cuda_softc {int /*<<< orphan*/  sc_mutex; int /*<<< orphan*/  sc_memr; int /*<<< orphan*/  sc_memrid; int /*<<< orphan*/  sc_irq; int /*<<< orphan*/  sc_irqrid; int /*<<< orphan*/  sc_ih; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cuda_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cuda_detach(device_t dev) {
	struct cuda_softc *sc;

	sc = device_get_softc(dev);

	bus_teardown_intr(dev, sc->sc_irq, sc->sc_ih);
	bus_release_resource(dev, SYS_RES_IRQ, sc->sc_irqrid, sc->sc_irq);
	bus_release_resource(dev, SYS_RES_MEMORY, sc->sc_memrid, sc->sc_memr);
	mtx_destroy(&sc->sc_mutex);

	return (bus_generic_detach(dev));
}