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
struct tegra_abpmisc_softc {int /*<<< orphan*/ * strap_opt_res; int /*<<< orphan*/ * abp_misc_res; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct tegra_abpmisc_softc* dev_sc ; 
 struct tegra_abpmisc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tegra_abpmisc_read_revision (struct tegra_abpmisc_softc*) ; 

__attribute__((used)) static int
tegra_abpmisc_attach(device_t dev)
{
	int rid;
	struct tegra_abpmisc_softc *sc;

	sc = device_get_softc(dev);
	sc->dev = dev;

	rid = 0;
	sc->abp_misc_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (sc->abp_misc_res == NULL) {
		device_printf(dev, "Cannot map ABP misc registers.\n");
		goto fail;
	}

	rid = 1;
	sc->strap_opt_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->strap_opt_res == NULL) {
		device_printf(dev, "Cannot map strapping options registers.\n");
		goto fail;
	}

	tegra_abpmisc_read_revision(sc);

	/* XXX - Hack - address collision with pinmux. */
	if (sc->abp_misc_res != NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->abp_misc_res);
		sc->abp_misc_res = NULL;
	}

	dev_sc = sc;
	return (bus_generic_attach(dev));

fail:
	if (sc->abp_misc_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->abp_misc_res);
	if (sc->strap_opt_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 1, sc->strap_opt_res);

	return (ENXIO);
}