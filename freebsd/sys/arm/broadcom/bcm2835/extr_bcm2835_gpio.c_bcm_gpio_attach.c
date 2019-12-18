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
typedef  int /*<<< orphan*/  uint32_t ;
struct bcm_gpio_softc {int sc_gpio_npins; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_res; int /*<<< orphan*/ * sc_busdev; TYPE_1__* sc_gpio_pins; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_bsh; int /*<<< orphan*/  sc_bst; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int gp_pin; int /*<<< orphan*/  gp_flags; int /*<<< orphan*/  gp_caps; int /*<<< orphan*/  gp_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_GPIO_DEFAULT_CAPS ; 
 int BCM_GPIO_PINS ; 
 int ENXIO ; 
 int /*<<< orphan*/  GPIOMAXNAME ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bcm_gpio_func_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_gpio_get_function (struct bcm_gpio_softc*,int) ; 
 int bcm_gpio_get_reserved_pins (struct bcm_gpio_softc*) ; 
 scalar_t__ bcm_gpio_intr_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_gpio_intr_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_gpio_res_spec ; 
 struct bcm_gpio_softc* bcm_gpio_sc ; 
 int /*<<< orphan*/  bcm_gpio_sysctl_init (struct bcm_gpio_softc*) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct bcm_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fdt_pinctrl_configure_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_pinctrl_register (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gpiobus_attach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
bcm_gpio_attach(device_t dev)
{
	int i, j;
	phandle_t gpio;
	struct bcm_gpio_softc *sc;
	uint32_t func;

	if (bcm_gpio_sc != NULL)
		return (ENXIO);

	bcm_gpio_sc = sc = device_get_softc(dev);
 	sc->sc_dev = dev;
	mtx_init(&sc->sc_mtx, "bcm gpio", "gpio", MTX_SPIN);
	if (bus_alloc_resources(dev, bcm_gpio_res_spec, sc->sc_res) != 0) {
		device_printf(dev, "cannot allocate resources\n");
		goto fail;
	}
	sc->sc_bst = rman_get_bustag(sc->sc_res[0]);
	sc->sc_bsh = rman_get_bushandle(sc->sc_res[0]);
	/* Setup the GPIO interrupt handler. */
	if (bcm_gpio_intr_attach(dev)) {
		device_printf(dev, "unable to setup the gpio irq handler\n");
		goto fail;
	}
	/* Find our node. */
	gpio = ofw_bus_get_node(sc->sc_dev);
	if (!OF_hasprop(gpio, "gpio-controller"))
		/* Node is not a GPIO controller. */
		goto fail;
	/*
	 * Find the read-only pins.  These are pins we never touch or bad
	 * things could happen.
	 */
	if (bcm_gpio_get_reserved_pins(sc) == -1)
		goto fail;
	/* Initialize the software controlled pins. */
	for (i = 0, j = 0; j < BCM_GPIO_PINS; j++) {
		snprintf(sc->sc_gpio_pins[i].gp_name, GPIOMAXNAME,
		    "pin %d", j);
		func = bcm_gpio_get_function(sc, j);
		sc->sc_gpio_pins[i].gp_pin = j;
		sc->sc_gpio_pins[i].gp_caps = BCM_GPIO_DEFAULT_CAPS;
		sc->sc_gpio_pins[i].gp_flags = bcm_gpio_func_flag(func);
		i++;
	}
	sc->sc_gpio_npins = i;
	bcm_gpio_sysctl_init(sc);
	sc->sc_busdev = gpiobus_attach_bus(dev);
	if (sc->sc_busdev == NULL)
		goto fail;

	fdt_pinctrl_register(dev, "brcm,pins");
	fdt_pinctrl_configure_tree(dev);

	return (0);

fail:
	bcm_gpio_intr_detach(dev);
	bus_release_resources(dev, bcm_gpio_res_spec, sc->sc_res);
	mtx_destroy(&sc->sc_mtx);

	return (ENXIO);
}