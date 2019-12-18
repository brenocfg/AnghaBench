#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rcc_gpio_softc {int sc_gpio_npins; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_io_res; scalar_t__ sc_io_rid; int /*<<< orphan*/ * sc_busdev; int /*<<< orphan*/  sc_output; int /*<<< orphan*/  sc_bsh; int /*<<< orphan*/  sc_bst; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int caps; int /*<<< orphan*/  pin; } ;

/* Variables and functions */
 int ENXIO ; 
 int GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  RCC_GPIO_GP_LVL ; 
 int /*<<< orphan*/  RCC_GPIO_IO_SEL ; 
 int /*<<< orphan*/  RCC_GPIO_USE_SEL ; 
 int /*<<< orphan*/  RCC_WRITE (struct rcc_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 struct rcc_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gpiobus_attach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  rcc_gpio_modify_bits (struct rcc_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* rcc_pins ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rcc_gpio_attach(device_t dev)
{
	int i;
	struct rcc_gpio_softc *sc;

	sc = device_get_softc(dev);
 	sc->sc_dev = dev;

	/* Allocate IO resources. */
	sc->sc_io_rid = 0;
	sc->sc_io_res = bus_alloc_resource_any(dev, SYS_RES_IOPORT,
	    &sc->sc_io_rid, RF_ACTIVE);
	if (sc->sc_io_res == NULL) {
		device_printf(dev, "cannot allocate memory window\n");
		return (ENXIO);
	}
	sc->sc_bst = rman_get_bustag(sc->sc_io_res);
	sc->sc_bsh = rman_get_bushandle(sc->sc_io_res);
	mtx_init(&sc->sc_mtx, "rcc-gpio", "gpio", MTX_DEF);

	/* Initialize the pins. */
	sc->sc_gpio_npins = nitems(rcc_pins);
	for (i = 0; i < sc->sc_gpio_npins; i++) {
		/* Enable it for GPIO. */
		rcc_gpio_modify_bits(sc, RCC_GPIO_USE_SEL, 0, rcc_pins[i].pin);
		/* Set the pin as input or output. */
		if (rcc_pins[i].caps & GPIO_PIN_OUTPUT)
			rcc_gpio_modify_bits(sc, RCC_GPIO_IO_SEL,
			    rcc_pins[i].pin, 0);
		else
			rcc_gpio_modify_bits(sc, RCC_GPIO_IO_SEL,
			    0, rcc_pins[i].pin);
	}
	RCC_WRITE(sc, RCC_GPIO_GP_LVL, sc->sc_output);

	/* Attach the gpiobus. */
	sc->sc_busdev = gpiobus_attach_bus(dev);
	if (sc->sc_busdev == NULL) {
		bus_release_resource(dev, SYS_RES_IOPORT, sc->sc_io_rid,
		    sc->sc_io_res);
		mtx_destroy(&sc->sc_mtx);
		return (ENXIO);
	}

	return (0);
}