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
struct vf_gpio_softc {int gpio_npins; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * res; int /*<<< orphan*/ * sc_busdev; TYPE_1__* gpio_pins; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int gp_pin; int /*<<< orphan*/  gp_name; int /*<<< orphan*/  gp_flags; int /*<<< orphan*/  gp_caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_CAPS ; 
 int ENXIO ; 
 int /*<<< orphan*/  GPIOMAXNAME ; 
 int /*<<< orphan*/  GPIO_PDOR (int) ; 
 int /*<<< orphan*/  GPIO_PIN_INPUT ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int NGPIO ; 
 int READ4 (struct vf_gpio_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct vf_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct vf_gpio_softc* gpio_sc ; 
 int /*<<< orphan*/ * gpiobus_attach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  vf_gpio_spec ; 

__attribute__((used)) static int
vf_gpio_attach(device_t dev)
{
	struct vf_gpio_softc *sc;
	int i;

	sc = device_get_softc(dev);
	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), NULL, MTX_DEF);

	if (bus_alloc_resources(dev, vf_gpio_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		mtx_destroy(&sc->sc_mtx);
		return (ENXIO);
	}

	/* Memory interface */
	sc->bst = rman_get_bustag(sc->res[0]);
	sc->bsh = rman_get_bushandle(sc->res[0]);

	gpio_sc = sc;

	sc->gpio_npins = NGPIO;

	for (i = 0; i < sc->gpio_npins; i++) {
		sc->gpio_pins[i].gp_pin = i;
		sc->gpio_pins[i].gp_caps = DEFAULT_CAPS;
		sc->gpio_pins[i].gp_flags =
		    (READ4(sc, GPIO_PDOR(i)) & (1 << (i % 32))) ?
		    GPIO_PIN_OUTPUT: GPIO_PIN_INPUT;
		snprintf(sc->gpio_pins[i].gp_name, GPIOMAXNAME,
		    "vf_gpio%d.%d", device_get_unit(dev), i);
	}

	sc->sc_busdev = gpiobus_attach_bus(dev);
	if (sc->sc_busdev == NULL) {
		bus_release_resources(dev, vf_gpio_spec, sc->res);
		mtx_destroy(&sc->sc_mtx);
		return (ENXIO);
	}

	return (0);
}