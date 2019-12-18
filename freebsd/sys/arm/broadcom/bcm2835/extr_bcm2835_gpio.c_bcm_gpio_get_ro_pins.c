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
struct bcm_gpio_softc {int* sc_ro_pins; int sc_ro_npins; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int pcell_t ;

/* Variables and functions */
 int OF_getencprop_alloc_multi (int /*<<< orphan*/ ,char const*,int,void**) ; 
 int /*<<< orphan*/  OF_prop_free (int*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
bcm_gpio_get_ro_pins(struct bcm_gpio_softc *sc, phandle_t node,
	const char *propname, const char *label)
{
	int i, need_comma, npins, range_start, range_stop;
	pcell_t *pins;

	/* Get the property data. */
	npins = OF_getencprop_alloc_multi(node, propname, sizeof(*pins),
	    (void **)&pins);
	if (npins < 0)
		return (-1);
	if (npins == 0) {
		OF_prop_free(pins);
		return (0);
	}
	for (i = 0; i < npins; i++)
		sc->sc_ro_pins[i + sc->sc_ro_npins] = pins[i];
	sc->sc_ro_npins += npins;
	need_comma = 0;
	device_printf(sc->sc_dev, "%s pins: ", label);
	range_start = range_stop = pins[0];
	for (i = 1; i < npins; i++) {
		if (pins[i] != range_stop + 1) {
			if (need_comma)
				printf(",");
			if (range_start != range_stop)
				printf("%d-%d", range_start, range_stop);
			else
				printf("%d", range_start);
			range_start = range_stop = pins[i];
			need_comma = 1;
		} else
			range_stop++;
	}
	if (need_comma)
		printf(",");
	if (range_start != range_stop)
		printf("%d-%d.\n", range_start, range_stop);
	else
		printf("%d.\n", range_start);
	OF_prop_free(pins);

	return (0);
}