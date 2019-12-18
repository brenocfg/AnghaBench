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
struct mv_pinctrl_softc {TYPE_2__* padconf; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int npins; TYPE_1__* pins; } ;
struct TYPE_3__ {scalar_t__* functions; scalar_t__ name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MAX_PIN_FUNC ; 
 int OF_getprop_alloc (int /*<<< orphan*/ ,char*,void**) ; 
 int /*<<< orphan*/  OF_node_from_xref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_prop_free (char const**) ; 
 struct mv_pinctrl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_pinctrl_configure_pin (struct mv_pinctrl_softc*,int,int) ; 
 int ofw_bus_string_list_to_array (int /*<<< orphan*/ ,char*,char const***) ; 
 scalar_t__ strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static int
mv_pinctrl_configure_pins(device_t dev, phandle_t cfgxref)
{
	struct mv_pinctrl_softc *sc;
	phandle_t node;
	char *function;
	const char **pins;
	int i, pin_num, pin_func, npins;

	sc = device_get_softc(dev);
	node = OF_node_from_xref(cfgxref);

	if (OF_getprop_alloc(node, "marvell,function",
	    (void **)&function) == -1)
		return (ENOMEM);

	npins = ofw_bus_string_list_to_array(node, "marvell,pins", &pins);
	if (npins == -1)
		return (ENOMEM);

	for (i = 0; i < npins; i++) {
		for (pin_num = 0; pin_num < sc->padconf->npins; pin_num++) {
			if (strcmp(pins[i], sc->padconf->pins[pin_num].name) == 0)
				break;
		}
		if (pin_num == sc->padconf->npins)
			continue;

		for (pin_func = 0; pin_func < MAX_PIN_FUNC; pin_func++)
			if (sc->padconf->pins[pin_num].functions[pin_func] &&
			    strcmp(function, sc->padconf->pins[pin_num].functions[pin_func]) == 0)
				break;

		if (pin_func == MAX_PIN_FUNC)
			continue;

		mv_pinctrl_configure_pin(sc, pin_num, pin_func);
	}

	OF_prop_free(pins);

	return (0);
}