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
struct rcc_gpio_softc {int sc_gpio_npins; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_io_res; int /*<<< orphan*/  sc_io_rid; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCC_GPIO_USE_SEL ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rcc_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiobus_detach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcc_gpio_modify_bits (struct rcc_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* rcc_pins ; 

__attribute__((used)) static int
rcc_gpio_detach(device_t dev)
{
	int i;
	struct rcc_gpio_softc *sc;

	sc = device_get_softc(dev);
	gpiobus_detach_bus(dev);

	/* Disable the GPIO function. */
	for (i = 0; i < sc->sc_gpio_npins; i++)
		rcc_gpio_modify_bits(sc, RCC_GPIO_USE_SEL, rcc_pins[i].pin, 0);

	if (sc->sc_io_res != NULL)
		bus_release_resource(dev, SYS_RES_IOPORT, sc->sc_io_rid,
		    sc->sc_io_res);
	mtx_destroy(&sc->sc_mtx);

	return (0);
}