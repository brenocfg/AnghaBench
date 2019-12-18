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
typedef  int /*<<< orphan*/  uint16_t ;
struct bhnd_sprom_softc {int /*<<< orphan*/ * store; int /*<<< orphan*/  dev; } ;
struct bhnd_resource {int /*<<< orphan*/  res; } ;
struct bhnd_nvram_io {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_SERVICE_NVRAM ; 
 scalar_t__ BUS_SPACE_MAXSIZE ; 
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 struct bhnd_resource* bhnd_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nvram_io_free (struct bhnd_nvram_io*) ; 
 struct bhnd_nvram_io* bhnd_nvram_iores_new (struct bhnd_resource*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  bhnd_nvram_sprom_class ; 
 int /*<<< orphan*/  bhnd_nvram_store_free (int /*<<< orphan*/ *) ; 
 int bhnd_nvram_store_parse_new (int /*<<< orphan*/ **,struct bhnd_nvram_io*,int /*<<< orphan*/ *) ; 
 int bhnd_register_provider (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct bhnd_resource*) ; 
 struct bhnd_sprom_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ rman_get_size (int /*<<< orphan*/ ) ; 

int
bhnd_sprom_attach(device_t dev, bus_size_t offset)
{
	struct bhnd_sprom_softc	*sc;
	struct bhnd_nvram_io	*io;
	struct bhnd_resource	*r;
	bus_size_t		 r_size, sprom_size;
	int			 rid;
	int			 error;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->store = NULL;

	io = NULL;
	r = NULL;

	/* Allocate SPROM resource */
	rid = 0;
	r = bhnd_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (r == NULL) {
		device_printf(dev, "failed to allocate resources\n");
		return (ENXIO);
	}

	/* Determine SPROM size */
	r_size = rman_get_size(r->res);
	if (r_size <= offset || (r_size - offset) > BUS_SPACE_MAXSIZE) {
		device_printf(dev, "invalid sprom offset\n");
		error = ENXIO;
		goto failed;
	}

	sprom_size = r_size - offset;

	/* Allocate an I/O context for the SPROM parser. All SPROM reads
	 * must be 16-bit aligned */
	io = bhnd_nvram_iores_new(r, offset, sprom_size, sizeof(uint16_t));
	if (io == NULL) {
		error = ENXIO;
		goto failed;
	}

	/* Initialize NVRAM data store */
	error = bhnd_nvram_store_parse_new(&sc->store, io,
	    &bhnd_nvram_sprom_class);
	if (error)
		goto failed;

	/* Clean up our temporary I/O context and its backing resource */
	bhnd_nvram_io_free(io);
	bhnd_release_resource(dev, SYS_RES_MEMORY, rid, r);

	io = NULL;
	r = NULL;

	/* Register ourselves with the bus */
	if ((error = bhnd_register_provider(dev, BHND_SERVICE_NVRAM))) {
		device_printf(dev, "failed to register NVRAM provider: %d\n",
		    error);
		goto failed;
	}

	return (0);

failed:
	/* Clean up I/O context before releasing its backing resource */
	if (io != NULL)
		bhnd_nvram_io_free(io);

	if (r != NULL)
		bhnd_release_resource(dev, SYS_RES_MEMORY, rid, r);

	if (sc->store != NULL)
		bhnd_nvram_store_free(sc->store);

	return (error);
}