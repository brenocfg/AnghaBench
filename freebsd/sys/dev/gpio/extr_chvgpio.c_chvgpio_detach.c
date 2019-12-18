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
struct chvgpio_softc {int /*<<< orphan*/ * sc_mem_res; int /*<<< orphan*/  sc_mem_rid; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/  sc_irq_rid; int /*<<< orphan*/ * intr_handle; int /*<<< orphan*/  sc_dev; scalar_t__ sc_busdev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHVGPIO_LOCK_DESTROY (struct chvgpio_softc*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct chvgpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiobus_detach_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
chvgpio_detach(device_t dev)
{
	struct chvgpio_softc *sc;
	sc = device_get_softc(dev);

	if (sc->sc_busdev)
		gpiobus_detach_bus(dev);

	if (sc->intr_handle != NULL)
	    bus_teardown_intr(sc->sc_dev, sc->sc_irq_res, sc->intr_handle);
	if (sc->sc_irq_res != NULL)
		bus_release_resource(dev, SYS_RES_IRQ, sc->sc_irq_rid, sc->sc_irq_res);
	if (sc->sc_mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, sc->sc_mem_rid, sc->sc_mem_res);

	CHVGPIO_LOCK_DESTROY(sc);

    return (0);
}