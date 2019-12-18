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
struct TYPE_2__ {struct imx6_anatop_softc* ich_arg; int /*<<< orphan*/  ich_func; } ;
struct imx6_anatop_softc {int /*<<< orphan*/  res; int /*<<< orphan*/  cpu_curmv; int /*<<< orphan*/  dev; TYPE_1__ intr_setup_hook; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int ENXIO ; 
 int /*<<< orphan*/  IMX6_ANALOG_PMU_MISC0_SELFBIASOFF ; 
 int /*<<< orphan*/  IMX6_ANALOG_PMU_MISC0_SET ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_intrhook_establish (TYPE_1__*) ; 
 struct imx6_anatop_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct imx6_anatop_softc* imx6_anatop_sc ; 
 int /*<<< orphan*/  imx6_anatop_spec ; 
 int /*<<< orphan*/  imx6_anatop_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_setup ; 

__attribute__((used)) static int
imx6_anatop_attach(device_t dev)
{
	struct imx6_anatop_softc *sc;
	int err;

	sc = device_get_softc(dev);
	sc->dev = dev;

	/* Allocate bus_space resources. */
	if (bus_alloc_resources(dev, imx6_anatop_spec, sc->res)) {
		device_printf(dev, "Cannot allocate resources\n");
		err = ENXIO;
		goto out;
	}

	sc->intr_setup_hook.ich_func = intr_setup;
	sc->intr_setup_hook.ich_arg = sc;
	config_intrhook_establish(&sc->intr_setup_hook);

	SYSCTL_ADD_UINT(device_get_sysctl_ctx(sc->dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(sc->dev)),
	    OID_AUTO, "cpu_voltage", CTLFLAG_RD,
	    &sc->cpu_curmv, 0, "Current CPU voltage in millivolts");

	imx6_anatop_sc = sc;

	/*
	 * Other code seen on the net sets this SELFBIASOFF flag around the same
	 * time the temperature sensor is set up, although it's unclear how the
	 * two are related (if at all).
	 */
	imx6_anatop_write_4(IMX6_ANALOG_PMU_MISC0_SET, 
	    IMX6_ANALOG_PMU_MISC0_SELFBIASOFF);

	/*
	 * Some day, when we're ready to deal with the actual anatop regulators
	 * that are described in fdt data as children of this "bus", this would
	 * be the place to invoke a simplebus helper routine to instantiate the
	 * children from the fdt data.
	 */

	err = 0;

out:

	if (err != 0) {
		bus_release_resources(dev, imx6_anatop_spec, sc->res);
	}

	return (err);
}