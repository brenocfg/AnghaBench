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
struct TYPE_2__ {void* ich_arg; int /*<<< orphan*/  ich_func; } ;
struct twl_softc {int /*<<< orphan*/ * sc_clks; int /*<<< orphan*/ * sc_vreg; TYPE_1__ sc_scan_hook; void* sc_dev; } ;
typedef  void* device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  TWL_LOCK_INIT (struct twl_softc*) ; 
 int bus_generic_attach (void*) ; 
 scalar_t__ config_intrhook_establish (TYPE_1__*) ; 
 void* device_add_child (void*,char*,int) ; 
 struct twl_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*) ; 
 int /*<<< orphan*/  twl_scan ; 

__attribute__((used)) static int
twl_attach(device_t dev)
{
	struct twl_softc *sc;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	TWL_LOCK_INIT(sc);

	/* We have to wait until interrupts are enabled. I2C read and write
	 * only works if the interrupts are available.
	 */
	sc->sc_scan_hook.ich_func = twl_scan;
	sc->sc_scan_hook.ich_arg = dev;

	if (config_intrhook_establish(&sc->sc_scan_hook) != 0)
		return (ENOMEM);

	/* FIXME: should be in DTS file */
	if ((sc->sc_vreg = device_add_child(dev, "twl_vreg", -1)) == NULL)
		device_printf(dev, "could not allocate twl_vreg instance\n");
	if ((sc->sc_clks = device_add_child(dev, "twl_clks", -1)) == NULL)
		device_printf(dev, "could not allocate twl_clks instance\n");

	return (bus_generic_attach(dev));
}