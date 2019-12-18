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
struct altera_avgen_softc {int avg_width; int /*<<< orphan*/ * avg_res; scalar_t__ avg_rid; int /*<<< orphan*/  avg_unit; int /*<<< orphan*/  avg_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALTERA_AVALON_STR_DEVNAME ; 
 int /*<<< orphan*/  ALTERA_AVALON_STR_DEVUNIT ; 
 int /*<<< orphan*/  ALTERA_AVALON_STR_FILEIO ; 
 int /*<<< orphan*/  ALTERA_AVALON_STR_GEOMIO ; 
 int /*<<< orphan*/  ALTERA_AVALON_STR_MMAPIO ; 
 int /*<<< orphan*/  ALTERA_AVALON_STR_WIDTH ; 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int altera_avgen_attach (struct altera_avgen_softc*,char const*,char const*,char const*,char const*,int) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 struct altera_avgen_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  resource_string_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static int
altera_avgen_nexus_attach(device_t dev)
{
	struct altera_avgen_softc *sc;
	const char *str_fileio, *str_geomio, *str_mmapio;
	const char *str_devname;
	int devunit, error;

	sc = device_get_softc(dev);
	sc->avg_dev = dev;
	sc->avg_unit = device_get_unit(dev);

	/*
	 * Query non-standard hints to find out what operations are permitted
	 * on the device, and whether it is cached.
	 */
	str_fileio = NULL;
	str_geomio = NULL;
	str_mmapio = NULL;
	str_devname = NULL;
	devunit = -1;
	sc->avg_width = 1;
	error = resource_int_value(device_get_name(dev), device_get_unit(dev),
	    ALTERA_AVALON_STR_WIDTH, &sc->avg_width);
	if (error != 0 && error != ENOENT) {
		device_printf(dev, "invalid %s\n", ALTERA_AVALON_STR_WIDTH);
		return (error);
	}
	(void)resource_string_value(device_get_name(dev),
	    device_get_unit(dev), ALTERA_AVALON_STR_FILEIO, &str_fileio);
	(void)resource_string_value(device_get_name(dev),
	    device_get_unit(dev), ALTERA_AVALON_STR_GEOMIO, &str_geomio);
	(void)resource_string_value(device_get_name(dev),
	    device_get_unit(dev), ALTERA_AVALON_STR_MMAPIO, &str_mmapio);
	(void)resource_string_value(device_get_name(dev),
	    device_get_unit(dev), ALTERA_AVALON_STR_DEVNAME, &str_devname);
	(void)resource_int_value(device_get_name(dev), device_get_unit(dev),
	    ALTERA_AVALON_STR_DEVUNIT, &devunit);

	/* Memory allocation and checking. */
	sc->avg_rid = 0;
	sc->avg_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &sc->avg_rid, RF_ACTIVE);
	if (sc->avg_res == NULL) {
		device_printf(dev, "couldn't map memory\n");
		return (ENXIO);
	}
	error = altera_avgen_attach(sc, str_fileio, str_geomio, str_mmapio,
	    str_devname, devunit);
	if (error != 0)
		bus_release_resource(dev, SYS_RES_MEMORY, sc->avg_rid,
		    sc->avg_res);
	return (error);
}