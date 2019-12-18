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
typedef  int /*<<< orphan*/  u_long ;
struct rk30_gpio_softc {int sc_gpio_npins; int /*<<< orphan*/  sc_dev; TYPE_1__* sc_gpio_pins; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int pcell_t ;
typedef  int /*<<< orphan*/  ihandle_t ;
struct TYPE_2__ {int gp_pin; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  GPIO_PIN_INPUT ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 scalar_t__ fdt_regsize (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rk30_gpio_pin_configure (struct rk30_gpio_softc*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  rk30_gpio_pin_set (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct rk30_gpio_softc* rk30_gpio_sc ; 

int
rk30_gpios_prop_handle(phandle_t ctrl, pcell_t *gpios, int len)
{
	struct rk30_gpio_softc *sc;
	pcell_t gpio_cells;
	int inc, t, tuples, tuple_size;
	int dir, flags, pin, i;
	u_long gpio_ctrl, size;

	sc = rk30_gpio_sc;
	if (sc == NULL)
		return ENXIO;

	if (OF_getencprop(ctrl, "#gpio-cells", &gpio_cells, sizeof(pcell_t)) < 0)
		return (ENXIO);
	if (gpio_cells != 2)
		return (ENXIO);

	tuple_size = gpio_cells * sizeof(pcell_t) + sizeof(phandle_t);
	tuples = len / tuple_size;

	if (fdt_regsize(ctrl, &gpio_ctrl, &size))
		return (ENXIO);

	/*
	 * Skip controller reference, since controller's phandle is given
	 * explicitly (in a function argument).
	 */
	inc = sizeof(ihandle_t) / sizeof(pcell_t);
	gpios += inc;
	for (t = 0; t < tuples; t++) {
		pin = gpios[0];
		dir = gpios[1];
		flags = gpios[2];

		for (i = 0; i < sc->sc_gpio_npins; i++) {
			if (sc->sc_gpio_pins[i].gp_pin == pin)
				break;
		}
		if (i >= sc->sc_gpio_npins)
			return (EINVAL);

		rk30_gpio_pin_configure(sc, &sc->sc_gpio_pins[i], flags);

		if (dir == 1) {
			/* Input. */
			rk30_gpio_pin_set(sc->sc_dev, pin, GPIO_PIN_INPUT);
		} else {
			/* Output. */
			rk30_gpio_pin_set(sc->sc_dev, pin, GPIO_PIN_OUTPUT);
		}
		gpios += gpio_cells + inc;
	}

	return (0);
}