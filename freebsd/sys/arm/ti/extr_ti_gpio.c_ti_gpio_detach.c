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
struct ti_gpio_softc {int /*<<< orphan*/ * sc_mem_res; int /*<<< orphan*/  sc_mem_rid; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/  sc_irq_rid; scalar_t__ sc_irq_hdl; int /*<<< orphan*/ * sc_isrcs; int /*<<< orphan*/ * sc_busdev; int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TI_GPIO_LOCK_DESTROY (struct ti_gpio_softc*) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 struct ti_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiobus_detach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ti_gpio_intr_clr (struct ti_gpio_softc*,int) ; 
 int /*<<< orphan*/  ti_gpio_pic_detach (struct ti_gpio_softc*) ; 

__attribute__((used)) static int
ti_gpio_detach(device_t dev)
{
	struct ti_gpio_softc *sc = device_get_softc(dev);

	KASSERT(mtx_initialized(&sc->sc_mtx), ("gpio mutex not initialized"));

	/* Disable all interrupts */
	if (sc->sc_mem_res != NULL)
		ti_gpio_intr_clr(sc, 0xffffffff);
	if (sc->sc_busdev != NULL)
		gpiobus_detach_bus(dev);
	if (sc->sc_isrcs != NULL)
		ti_gpio_pic_detach(sc);
	/* Release the memory and IRQ resources. */
	if (sc->sc_irq_hdl) {
		bus_teardown_intr(dev, sc->sc_irq_res,
		    sc->sc_irq_hdl);
	}
	if (sc->sc_irq_res)
		bus_release_resource(dev, SYS_RES_IRQ, sc->sc_irq_rid,
		    sc->sc_irq_res);
	if (sc->sc_mem_res)
		bus_release_resource(dev, SYS_RES_MEMORY, sc->sc_mem_rid,
		    sc->sc_mem_res);
	TI_GPIO_LOCK_DESTROY(sc);

	return (0);
}