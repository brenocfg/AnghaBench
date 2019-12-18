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
struct bhnd_erom_io {int dummy; } ;
struct TYPE_2__ {struct bhnd_erom_io eio; } ;
struct bhndb_pci_probe {void* dev; int m_valid; int /*<<< orphan*/ * hr; int /*<<< orphan*/ * cores; int /*<<< orphan*/ * erom; int /*<<< orphan*/  hostb_core; int /*<<< orphan*/  ncores; int /*<<< orphan*/  cid; int /*<<< orphan*/ * erom_class; TYPE_1__ erom_io; int /*<<< orphan*/ * m_res; int /*<<< orphan*/ * m_win; void* pci_dev; } ;
struct bhndb_hwcfg {int dummy; } ;
struct bhnd_chipid {int dummy; } ;
typedef  void* device_t ;
typedef  int /*<<< orphan*/  bhnd_devclass_t ;

/* Variables and functions */
 struct bhnd_chipid* BHNDB_BUS_GET_CHIPID (void*,void*) ; 
 struct bhndb_hwcfg* BHNDB_BUS_GET_GENERIC_HWCFG (void*,void*) ; 
 int /*<<< orphan*/  BHND_DEFAULT_CHIPC_ADDR ; 
 int /*<<< orphan*/  BHND_DEFAULT_CORE_SIZE ; 
 int ENXIO ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_BHND ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * bhnd_erom_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct bhnd_erom_io*) ; 
 int /*<<< orphan*/  bhnd_erom_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_erom_free_core_table (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bhnd_erom_get_core_table (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_erom_io_fini (struct bhnd_erom_io*) ; 
 int bhnd_erom_io_map (struct bhnd_erom_io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bhnd_erom_probe_driver_classes (int /*<<< orphan*/ ,struct bhnd_erom_io*,struct bhnd_chipid const*,int /*<<< orphan*/ *) ; 
 int bhndb_alloc_host_resources (int /*<<< orphan*/ **,void*,void*,struct bhndb_hwcfg const*) ; 
 int bhndb_find_hostb_core (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhndb_pci_eio_init (TYPE_1__*,struct bhndb_pci_probe*) ; 
 int /*<<< orphan*/  bhndb_release_host_resources (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_devclass (void*) ; 
 void* device_get_parent (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*,...) ; 
 int /*<<< orphan*/  free (struct bhndb_pci_probe*,int /*<<< orphan*/ ) ; 
 struct bhndb_pci_probe* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bhndb_pci_probe_alloc(struct bhndb_pci_probe **probe, device_t dev,
    bhnd_devclass_t hostb_devclass)
{
	struct bhndb_pci_probe		*p;
	struct bhnd_erom_io		*eio;
	const struct bhndb_hwcfg	*hwcfg;
	const struct bhnd_chipid	*hint;
	device_t			 parent_dev;
	int				 error;

	parent_dev = device_get_parent(dev);
	eio = NULL;

	p = malloc(sizeof(*p), M_BHND, M_ZERO|M_WAITOK);
	p->dev = dev;
	p->pci_dev = parent_dev;

	/* Our register window mapping state must be initialized at this point,
	 * as bhndb_pci_eio will begin making calls into
	 * bhndb_pci_probe_(read|write|get_mapping) */
	p->m_win = NULL;
	p->m_res = NULL;
	p->m_valid = false;

	bhndb_pci_eio_init(&p->erom_io, p);
	eio = &p->erom_io.eio;

	/* Fetch our chipid hint (if any) and generic hardware configuration */
	hwcfg = BHNDB_BUS_GET_GENERIC_HWCFG(parent_dev, dev);
	hint = BHNDB_BUS_GET_CHIPID(parent_dev, dev);

	/* Allocate our host resources */
	error = bhndb_alloc_host_resources(&p->hr, dev, parent_dev, hwcfg);
	if (error) {
		p->hr = NULL;
		goto failed;
	}

	/* Map the first bus core from our bridged bhnd(4) bus */
	error = bhnd_erom_io_map(eio, BHND_DEFAULT_CHIPC_ADDR,
	    BHND_DEFAULT_CORE_SIZE);
	if (error)
		goto failed;

	/* Probe for a usable EROM class, and read the chip identifier */
	p->erom_class = bhnd_erom_probe_driver_classes(
	    device_get_devclass(dev), eio, hint, &p->cid);
	if (p->erom_class == NULL) {
		device_printf(dev, "device enumeration unsupported; no "
		    "compatible driver found\n");

		error = ENXIO;
		goto failed;
	}

	/* Allocate EROM parser */
	p->erom = bhnd_erom_alloc(p->erom_class, &p->cid, eio);
	if (p->erom == NULL) {
		device_printf(dev, "failed to allocate device enumeration "
		    "table parser\n");
		error = ENXIO;
		goto failed;
	}

	/* The EROM I/O instance is now owned by our EROM parser */
	eio = NULL;

	/* Read the full core table */
	error = bhnd_erom_get_core_table(p->erom, &p->cores, &p->ncores);
	if (error) {
		device_printf(p->dev, "error fetching core table: %d\n",
		    error);

		p->cores = NULL;
		goto failed;
	}

	/* Identify the host bridge core */
	error = bhndb_find_hostb_core(p->cores, p->ncores, hostb_devclass,
	    &p->hostb_core);
	if (error) {
		device_printf(dev, "failed to identify the host bridge "
		    "core: %d\n", error);

		goto failed;
	}

	*probe = p;
	return (0);

failed:
	if (eio != NULL) {
		KASSERT(p->erom == NULL, ("I/O instance will be freed by "
		    "its owning parser"));

		bhnd_erom_io_fini(eio);
	}

	if (p->erom != NULL) {
		if (p->cores != NULL)
			bhnd_erom_free_core_table(p->erom, p->cores);

		bhnd_erom_free(p->erom);
	} else {
		KASSERT(p->cores == NULL, ("cannot free erom-owned core table "
		    "without erom reference"));
	}

	if (p->hr != NULL)
		bhndb_release_host_resources(p->hr);

	free(p, M_BHND);

	return (error);
}