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
struct imx51_gpio_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_res; scalar_t__* gpio_ih; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int FIRST_IRQRES ; 
 int NUM_IRQRES ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct imx51_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiobus_detach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_gpio_spec ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
imx51_gpio_detach(device_t dev)
{
	int irq;
	struct imx51_gpio_softc *sc;

	sc = device_get_softc(dev);

	gpiobus_detach_bus(dev);
	for (irq = 0; irq < NUM_IRQRES; irq++) {
		if (sc->gpio_ih[irq])
			bus_teardown_intr(dev, sc->sc_res[irq + FIRST_IRQRES],
			    sc->gpio_ih[irq]);
	}
	bus_release_resources(dev, imx_gpio_spec, sc->sc_res);
	mtx_destroy(&sc->sc_mtx);

	return(0);
}