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
struct chipc_spi_softc {int sc_rid; int sc_flash_rid; int /*<<< orphan*/ * sc_flash_res; int /*<<< orphan*/ * sc_res; } ;
struct chipc_caps {int /*<<< orphan*/  flash_type; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 struct chipc_caps* BHND_CHIPC_GET_CAPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chipc_register_slicer (int /*<<< orphan*/ ) ; 
 char* chipc_sflash_device_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ *) ; 
 struct chipc_spi_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 
 int device_probe_and_attach (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
chipc_spi_attach(device_t dev)
{
	struct chipc_spi_softc	*sc;
	struct chipc_caps	*ccaps;
	device_t		 flash_dev;
	device_t		 spibus;
	const char		*flash_name;
	int			 error;

	sc = device_get_softc(dev);

	/* Allocate SPI controller registers */
	sc->sc_rid = 1;
	sc->sc_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->sc_rid,
	    RF_ACTIVE);
	if (sc->sc_res == NULL) {
		device_printf(dev, "failed to allocate device registers\n");
		return (ENXIO);
	}

	/* Allocate flash shadow region */
	sc->sc_flash_rid = 0;
	sc->sc_flash_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &sc->sc_flash_rid, RF_ACTIVE);
	if (sc->sc_flash_res == NULL) {
		device_printf(dev, "failed to allocate flash region\n");
		error = ENXIO;
		goto failed;
	}

	/* 
	 * Add flash device
	 * 
	 * XXX: This should be replaced with a DEVICE_IDENTIFY implementation
	 * in chipc-specific subclasses of the mx25l and at45d drivers.
	 */
	if ((spibus = device_add_child(dev, "spibus", -1)) == NULL) {
		device_printf(dev, "failed to add spibus\n");
		error = ENXIO;
		goto failed;
	}

	/* Let spibus perform full attach before we try to call
	 * BUS_ADD_CHILD() */
	if ((error = bus_generic_attach(dev)))
		goto failed;

	/* Determine flash type and add the flash child */
	ccaps = BHND_CHIPC_GET_CAPS(device_get_parent(dev));
	flash_name = chipc_sflash_device_name(ccaps->flash_type);
	if (flash_name != NULL) {
		flash_dev = BUS_ADD_CHILD(spibus, 0, flash_name, -1);
		if (flash_dev == NULL) {
			device_printf(dev, "failed to add %s\n", flash_name);
			error = ENXIO;
			goto failed;
		}

		chipc_register_slicer(ccaps->flash_type);

		if ((error = device_probe_and_attach(flash_dev))) {
			device_printf(dev, "failed to attach %s: %d\n",
			    flash_name, error);
			goto failed;
		}
	}

	return (0);

failed:
	device_delete_children(dev);

	if (sc->sc_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, sc->sc_rid,
		    sc->sc_res);

	if (sc->sc_flash_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, sc->sc_flash_rid,
		    sc->sc_flash_res);

	return (error);
}