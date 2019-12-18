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
typedef  int /*<<< orphan*/  u_int ;
struct bhnd_chipid {int dummy; } ;
struct bhnd_core_info {int dummy; } ;
struct bhndb_softc {int /*<<< orphan*/  services; int /*<<< orphan*/ * bus_res; int /*<<< orphan*/  dev; int /*<<< orphan*/  parent_dev; int /*<<< orphan*/ * bus_dev; struct bhnd_chipid chipid; struct bhnd_core_info bridge_core; } ;
struct bhndb_hwcfg {int dummy; } ;
struct bhndb_hw_priority {int dummy; } ;
struct bhndb_hw {int name; struct bhndb_hwcfg* cfg; } ;
struct bhndb_devinfo {int /*<<< orphan*/  addrspace; } ;
struct bhnd_erom_io {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bhnd_erom_t ;
typedef  int /*<<< orphan*/  bhnd_erom_class_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHNDB_ADDRSPACE_BRIDGED ; 
 struct bhndb_hwcfg* BHNDB_BUS_GET_GENERIC_HWCFG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bhndb_hw_priority* BHNDB_BUS_GET_HARDWARE_PRIO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BHNDB_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHNDB_LOCK_DESTROY (struct bhndb_softc*) ; 
 int /*<<< orphan*/  BHNDB_LOCK_INIT (struct bhndb_softc*) ; 
 int /*<<< orphan*/  BHND_PROBE_BUS ; 
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  PRIO ; 
 int /*<<< orphan*/ * bhnd_erom_alloc (int /*<<< orphan*/ *,struct bhnd_chipid*,struct bhnd_erom_io*) ; 
 int /*<<< orphan*/  bhnd_erom_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_erom_io_fini (struct bhnd_erom_io*) ; 
 struct bhnd_erom_io* bhnd_erom_iores_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_service_registry_fini (int /*<<< orphan*/ *) ; 
 int bhnd_service_registry_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bhndb_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bhndb_hwcfg const*) ; 
 int bhndb_find_hwspec (struct bhndb_softc*,struct bhnd_core_info*,int /*<<< orphan*/ ,struct bhndb_hw const**) ; 
 int /*<<< orphan*/  bhndb_free_resources (int /*<<< orphan*/ *) ; 
 int bhndb_init_region_cfg (struct bhndb_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct bhnd_core_info*,int /*<<< orphan*/ ,struct bhndb_hw_priority const*) ; 
 scalar_t__ bootverbose ; 
 struct bhndb_devinfo* device_get_ivars (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct bhndb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

int
bhndb_attach(device_t dev, struct bhnd_chipid *cid,
    struct bhnd_core_info *cores, u_int ncores,
    struct bhnd_core_info *bridge_core, bhnd_erom_class_t *erom_class)
{
	struct bhndb_devinfo		*dinfo;
	struct bhndb_softc		*sc;
	const struct bhndb_hw		*hw;
	const struct bhndb_hwcfg	*hwcfg;
	const struct bhndb_hw_priority	*hwprio;
	struct bhnd_erom_io		*eio;
	bhnd_erom_t			*erom;
	int				 error;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->parent_dev = device_get_parent(dev);
	sc->bridge_core = *bridge_core;
	sc->chipid = *cid;

	if ((error = bhnd_service_registry_init(&sc->services)))
		return (error);

	BHNDB_LOCK_INIT(sc);

	erom = NULL;

	/* Find a matching bridge hardware configuration */
	if ((error = bhndb_find_hwspec(sc, cores, ncores, &hw))) {
		device_printf(sc->dev, "unable to identify device, "
		    " using generic bridge resource definitions\n");

		hwcfg = BHNDB_BUS_GET_GENERIC_HWCFG(sc->parent_dev, dev);
		hw = NULL;
	} else {
		hwcfg = hw->cfg;
	}

	if (hw != NULL && (bootverbose || BHNDB_DEBUG(PRIO))) {
		device_printf(sc->dev, "%s resource configuration\n", hw->name);
	}

	/* Allocate bridge resource state using the discovered hardware
	 * configuration */
	sc->bus_res = bhndb_alloc_resources(sc->dev, sc->parent_dev, hwcfg);
	if (sc->bus_res == NULL) {
		device_printf(sc->dev, "failed to allocate bridge resource "
		    "state\n");
		error = ENOMEM;
		goto failed;
	}

	/* Add our bridged bus device */
	sc->bus_dev = BUS_ADD_CHILD(dev, BHND_PROBE_BUS, "bhnd", -1);
	if (sc->bus_dev == NULL) {
		error = ENXIO;
		goto failed;
	}

	dinfo = device_get_ivars(sc->bus_dev);
	dinfo->addrspace = BHNDB_ADDRSPACE_BRIDGED;

	/* We can now use bhndb to perform bridging of SYS_RES_MEMORY resources;
	 * we use this to instantiate an erom parser instance */
	eio = bhnd_erom_iores_new(sc->bus_dev, 0);
	if ((erom = bhnd_erom_alloc(erom_class, cid, eio)) == NULL) {
		bhnd_erom_io_fini(eio);
		error = ENXIO;
		goto failed;
	}

	/* Populate our resource priority configuration */
	hwprio = BHNDB_BUS_GET_HARDWARE_PRIO(sc->parent_dev, sc->dev);
	error = bhndb_init_region_cfg(sc, erom, sc->bus_res, cores, ncores,
	    hwprio);
	if (error) {
		device_printf(sc->dev, "failed to initialize resource "
		    "priority configuration: %d\n", error);
		goto failed;
	}

	/* Free our erom instance */
	bhnd_erom_free(erom);
	erom = NULL;

	return (0);

failed:
	BHNDB_LOCK_DESTROY(sc);

	if (sc->bus_res != NULL)
		bhndb_free_resources(sc->bus_res);

	if (erom != NULL)
		bhnd_erom_free(erom);

	bhnd_service_registry_fini(&sc->services);

	return (error);
}