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
struct ti_pinmux_softc {int /*<<< orphan*/ * sc_res; int /*<<< orphan*/  sc_bsh; int /*<<< orphan*/  sc_bst; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ti_pinmux_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fdt_pinctrl_configure_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_pinctrl_register (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_pinmux_res_spec ; 
 struct ti_pinmux_softc* ti_pinmux_sc ; 

__attribute__((used)) static int
ti_pinmux_attach(device_t dev)
{
	struct ti_pinmux_softc *sc = device_get_softc(dev);

#if 0
	if (ti_pinmux_sc)
		return (ENXIO);
#endif

	sc->sc_dev = dev;

	if (bus_alloc_resources(dev, ti_pinmux_res_spec, sc->sc_res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	sc->sc_bst = rman_get_bustag(sc->sc_res[0]);
	sc->sc_bsh = rman_get_bushandle(sc->sc_res[0]);

	if (ti_pinmux_sc == NULL)
		ti_pinmux_sc = sc;

	fdt_pinctrl_register(dev, "pinctrl-single,pins");
	fdt_pinctrl_configure_tree(dev);

	return (0);
}