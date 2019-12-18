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
typedef  int /*<<< orphan*/  phandle_t ;
typedef  void* pcell_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  cell ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_getprop (int /*<<< orphan*/ ,char*,void**,int) ; 
 int /*<<< orphan*/  OF_getprop_alloc (int /*<<< orphan*/ ,char*,void**) ; 
 int /*<<< orphan*/  OF_prop_free (char*) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int altera_avgen_attach (struct altera_avgen_softc*,char*,char*,char*,char*,int) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 struct altera_avgen_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
altera_avgen_fdt_attach(device_t dev)
{
	struct altera_avgen_softc *sc;
	char *str_fileio, *str_geomio, *str_mmapio;
	char *str_devname;
	phandle_t node;
	pcell_t cell;
	int devunit, error;

	sc = device_get_softc(dev);
	sc->avg_dev = dev;
	sc->avg_unit = device_get_unit(dev);

	/*
	 * Query driver-specific OpenFirmware properties to determine how to
	 * expose the device via /dev.
	 */
	str_fileio = NULL;
	str_geomio = NULL;
	str_mmapio = NULL;
	str_devname = NULL;
	devunit = -1;
	sc->avg_width = 1;
	node = ofw_bus_get_node(dev);
	if (OF_getprop(node, "sri-cambridge,width", &cell, sizeof(cell)) > 0)
		sc->avg_width = cell;
	(void)OF_getprop_alloc(node, "sri-cambridge,fileio",
	    (void **)&str_fileio);
	(void)OF_getprop_alloc(node, "sri-cambridge,geomio",
	    (void **)&str_geomio);
	(void)OF_getprop_alloc(node, "sri-cambridge,mmapio",
	    (void **)&str_mmapio);
	(void)OF_getprop_alloc(node,  "sri-cambridge,devname",
	    (void **)&str_devname);
	if (OF_getprop(node, "sri-cambridge,devunit", &cell, sizeof(cell)) > 0)
		devunit = cell;

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
	if (str_fileio != NULL)
		OF_prop_free(str_fileio);
	if (str_geomio != NULL)
		OF_prop_free(str_geomio);
	if (str_mmapio != NULL)
		OF_prop_free(str_mmapio);
	if (str_devname != NULL)
		OF_prop_free(str_devname);
	return (error);
}