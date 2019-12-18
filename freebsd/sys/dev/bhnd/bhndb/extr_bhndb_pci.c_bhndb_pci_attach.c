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
struct bhndb_pci_softc {scalar_t__ msi_count; int /*<<< orphan*/  parent; int /*<<< orphan*/  dev; int /*<<< orphan*/ * isrc; int /*<<< orphan*/ * set_regwin; scalar_t__ pci_quirks; int /*<<< orphan*/  pci_devclass; } ;
struct bhnd_core_info {int dummy; } ;
struct bhnd_chipid {scalar_t__ chip_type; } ;
struct bhndb_pci_probe {struct bhnd_core_info hostb_core; int /*<<< orphan*/ * erom_class; struct bhnd_chipid cid; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bhnd_erom_class_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHNDB_PCI_LOCK_DESTROY (struct bhndb_pci_softc*) ; 
 int /*<<< orphan*/  BHNDB_PCI_LOCK_INIT (struct bhndb_pci_softc*) ; 
 scalar_t__ BHND_CHIPTYPE_SIBA ; 
 int ENXIO ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  RM_MAX_END ; 
 int /*<<< orphan*/ * bhndb_alloc_intr_isrc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int bhndb_attach (int /*<<< orphan*/ ,struct bhnd_chipid*,struct bhnd_core_info*,int /*<<< orphan*/ ,struct bhnd_core_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhndb_disable_pci_clocks (int /*<<< orphan*/ ) ; 
 int bhndb_enable_pci_clocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhndb_expected_pci_devclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhndb_free_intr_isrc (int /*<<< orphan*/ *) ; 
 int bhndb_pci_add_children (struct bhndb_pci_softc*) ; 
 scalar_t__ bhndb_pci_alloc_msi (struct bhndb_pci_softc*,scalar_t__*) ; 
 int /*<<< orphan*/ * bhndb_pci_compat_setregwin ; 
 int /*<<< orphan*/ * bhndb_pci_fast_setregwin ; 
 scalar_t__ bhndb_pci_get_core_quirks (struct bhnd_chipid*,struct bhnd_core_info*) ; 
 int bhndb_pci_probe_alloc (struct bhndb_pci_probe**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bhndb_pci_probe_copy_core_table (struct bhndb_pci_probe*,struct bhnd_core_info**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhndb_pci_probe_free (struct bhndb_pci_probe*) ; 
 int /*<<< orphan*/  bhndb_pci_probe_free_core_table (struct bhnd_core_info*) ; 
 int bhndb_pci_srsh_pi_war (struct bhndb_pci_softc*,struct bhndb_pci_probe*) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct bhndb_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pci_disable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhndb_pci_attach(device_t dev)
{
	struct bhndb_pci_softc	*sc;
	struct bhnd_chipid	 cid;
	struct bhnd_core_info	*cores, hostb_core;
	bhnd_erom_class_t	*erom_class;
	struct bhndb_pci_probe	*probe;
	u_int			 ncores;
	int			 irq_rid;
	int			 error;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->parent = device_get_parent(dev);
	sc->pci_devclass = bhndb_expected_pci_devclass(dev);
	sc->pci_quirks = 0;
	sc->set_regwin = NULL;

	BHNDB_PCI_LOCK_INIT(sc);

	probe = NULL;
	cores = NULL;

	/* Enable PCI bus mastering */
	pci_enable_busmaster(sc->parent);

	/* Enable clocks (if required by this hardware) */
	if ((error = bhndb_enable_pci_clocks(sc->dev)))
		goto cleanup;

	/* Identify the chip and enumerate the bridged cores */
	error = bhndb_pci_probe_alloc(&probe, dev, sc->pci_devclass);
	if (error)
		goto cleanup;

	sc->pci_quirks = bhndb_pci_get_core_quirks(&probe->cid,
	    &probe->hostb_core);

	/* Select the appropriate register window handler */
	if (probe->cid.chip_type == BHND_CHIPTYPE_SIBA) {
		sc->set_regwin = bhndb_pci_compat_setregwin;
	} else {
		sc->set_regwin = bhndb_pci_fast_setregwin;
	}

	/*
	 * Fix up our PCI base address in the SPROM shadow, if necessary.
	 * 
	 * This must be done prior to accessing any static register windows
	 * that map the PCI core.
	 */
	if ((error = bhndb_pci_srsh_pi_war(sc, probe)))
		goto cleanup;

	/* Set up PCI interrupt handling */
	if (bhndb_pci_alloc_msi(sc, &sc->msi_count) == 0) {
		/* MSI uses resource IDs starting at 1 */
		irq_rid = 1;

		device_printf(dev, "Using MSI interrupts on %s\n",
		    device_get_nameunit(sc->parent));
	} else {
		sc->msi_count = 0;
		irq_rid = 0;

		device_printf(dev, "Using INTx interrupts on %s\n",
		    device_get_nameunit(sc->parent));
	}

	sc->isrc = bhndb_alloc_intr_isrc(sc->parent, irq_rid, 0, RM_MAX_END, 1,
	    RF_SHAREABLE | RF_ACTIVE);
	if (sc->isrc == NULL) {
		device_printf(sc->dev, "failed to allocate interrupt "
		    "resource\n");
		error = ENXIO;
		goto cleanup;
	}

	/*
	 * Copy out the probe results and then free our probe state, releasing
	 * its exclusive ownership of host bridge resources.
	 * 
	 * This must be done prior to full configuration of the bridge via
	 * bhndb_attach().
	 */
	cid = probe->cid;
	erom_class = probe->erom_class;
	hostb_core = probe->hostb_core;

	error = bhndb_pci_probe_copy_core_table(probe, &cores, &ncores);
	if (error) {
		cores = NULL;
		goto cleanup;
	}

	bhndb_pci_probe_free(probe);
	probe = NULL;

	/* Perform bridge attach */
	error = bhndb_attach(dev, &cid, cores, ncores, &hostb_core, erom_class);
	if (error)
		goto cleanup;

	/* Add any additional child devices */
	if ((error = bhndb_pci_add_children(sc)))
		goto cleanup;

	/* Probe and attach our children */
	if ((error = bus_generic_attach(dev)))
		goto cleanup;

	bhndb_pci_probe_free_core_table(cores);

	return (0);

cleanup:
	device_delete_children(dev);

	if (sc->isrc != NULL)
		bhndb_free_intr_isrc(sc->isrc);

	if (sc->msi_count > 0)
		pci_release_msi(sc->parent);

	if (cores != NULL)
		bhndb_pci_probe_free_core_table(cores);

	if (probe != NULL)
		bhndb_pci_probe_free(probe);

	bhndb_disable_pci_clocks(sc->dev);

	pci_disable_busmaster(sc->parent);

	BHNDB_PCI_LOCK_DESTROY(sc);

	return (error);
}