#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pad_softc {int model; int gpio_npins; int nports; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * res; int /*<<< orphan*/  pad_spec; scalar_t__* gpio_ih; int /*<<< orphan*/ * busdev; TYPE_1__* gpio_pins; int /*<<< orphan*/  dev; int /*<<< orphan*/ * bsh; int /*<<< orphan*/ * bst; int /*<<< orphan*/  interrupt_table; int /*<<< orphan*/  gpio_map; } ;
struct gpio_bank {int /*<<< orphan*/  con; int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int ocd_data; } ;
struct TYPE_3__ {int gp_pin; int /*<<< orphan*/  gp_name; int /*<<< orphan*/  gp_flags; int /*<<< orphan*/  gp_caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_CAPS ; 
 int ENXIO ; 
#define  EXYNOS5250 129 
#define  EXYNOS5420 128 
 int /*<<< orphan*/  GPIOMAXNAME ; 
 int /*<<< orphan*/  GPIO_PIN_INPUT ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int PIN_OUT ; 
 int READ4 (struct pad_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pad_softc*,scalar_t__*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  compat_data ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct pad_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_bank (struct pad_softc*,int,struct gpio_bank*,int*) ; 
 int /*<<< orphan*/  gpio_map_5250 ; 
 int /*<<< orphan*/  gpio_map_5420 ; 
 struct pad_softc* gpio_sc ; 
 int /*<<< orphan*/ * gpiobus_attach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interrupt_table_5250 ; 
 int /*<<< orphan*/  interrupt_table_5420 ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pad_spec_5250 ; 
 int /*<<< orphan*/  pad_spec_5420 ; 
 int /*<<< orphan*/  port_intr ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int
pad_attach(device_t dev)
{
	struct gpio_bank bank;
	struct pad_softc *sc;
	int pin_shift;
	int reg;
	int i;

	sc = device_get_softc(dev);

	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), NULL, MTX_DEF);

	sc->model = ofw_bus_search_compatible(dev, compat_data)->ocd_data;
	switch (sc->model) {
	case EXYNOS5250:
		sc->pad_spec = pad_spec_5250;
		sc->gpio_map = gpio_map_5250;
		sc->interrupt_table = interrupt_table_5250;
		sc->gpio_npins = 253;
		sc->nports = 4;
		break;
	case EXYNOS5420:
		sc->pad_spec = pad_spec_5420;
		sc->gpio_map = gpio_map_5420;
		sc->interrupt_table = interrupt_table_5420;
		sc->gpio_npins = 232;
		sc->nports = 5;
		break;
	default:
		goto fail;
	}

	if (bus_alloc_resources(dev, sc->pad_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		goto fail;
	}

	/* Memory interface */

	for (i = 0; i < sc->nports; i++) {
		sc->bst[i] = rman_get_bustag(sc->res[i]);
		sc->bsh[i] = rman_get_bushandle(sc->res[i]);
	}

	sc->dev = dev;

	gpio_sc = sc;

	for (i = 0; i < sc->nports; i++) {
		if ((bus_setup_intr(dev, sc->res[sc->nports + i],
			    INTR_TYPE_BIO | INTR_MPSAFE, port_intr,
			    NULL, sc, &sc->gpio_ih[i]))) {
			device_printf(dev,
			    "ERROR: Unable to register interrupt handler\n");
			goto fail;
		}
	}

	for (i = 0; i < sc->gpio_npins; i++) {
		sc->gpio_pins[i].gp_pin = i;
		sc->gpio_pins[i].gp_caps = DEFAULT_CAPS;

		if (get_bank(sc, i, &bank, &pin_shift) != 0)
			continue;

		pin_shift *= 4;

		reg = READ4(sc, bank.port, bank.con);
		if (reg & (PIN_OUT << pin_shift))
			sc->gpio_pins[i].gp_flags = GPIO_PIN_OUTPUT;
		else
			sc->gpio_pins[i].gp_flags = GPIO_PIN_INPUT;

		/* TODO: add other pin statuses */

		snprintf(sc->gpio_pins[i].gp_name, GPIOMAXNAME,
		    "pad%d.%d", device_get_unit(dev), i);
	}
	sc->busdev = gpiobus_attach_bus(dev);
	if (sc->busdev == NULL)
		goto fail;

	return (0);

fail:
	for (i = 0; i < sc->nports; i++) {
		if (sc->gpio_ih[i])
			bus_teardown_intr(dev, sc->res[sc->nports + i],
			    sc->gpio_ih[i]);
	}
	bus_release_resources(dev, sc->pad_spec, sc->res);
	mtx_destroy(&sc->sc_mtx);

	return (ENXIO);
}