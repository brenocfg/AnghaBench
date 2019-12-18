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
struct bhndb_pci_probe {int /*<<< orphan*/  hostb_core; } ;
struct bhndb_pci_core {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/ * devclass_t ;
typedef  int /*<<< orphan*/  bhnd_devclass_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  bhndb_disable_pci_clocks (int /*<<< orphan*/ *) ; 
 int bhndb_enable_pci_clocks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhndb_expected_pci_devclass (int /*<<< orphan*/ *) ; 
 struct bhndb_pci_core* bhndb_pci_find_core (int /*<<< orphan*/ *) ; 
 int bhndb_pci_probe_alloc (struct bhndb_pci_probe**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhndb_pci_probe_free (struct bhndb_pci_probe*) ; 
 int /*<<< orphan*/ * devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_devclass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
bhndb_pci_probe(device_t dev)
{
	struct bhndb_pci_probe	*probe;
	struct bhndb_pci_core	*entry;
	bhnd_devclass_t		 hostb_devclass;
	device_t		 parent, parent_bus;
	devclass_t		 pci, bus_devclass;
	int			 error;

	probe = NULL;

	/* Our parent must be a PCI/PCIe device. */
	pci = devclass_find("pci");
	parent = device_get_parent(dev);
	parent_bus = device_get_parent(parent);
	if (parent_bus == NULL)
		return (ENXIO);

	/* The bus device class may inherit from 'pci' */
	for (bus_devclass = device_get_devclass(parent_bus);
	    bus_devclass != NULL;
	    bus_devclass = devclass_get_parent(bus_devclass))
	{
		if (bus_devclass == pci)
			break;
	}

	if (bus_devclass != pci)
		return (ENXIO);

	/* Enable clocks */
	if ((error = bhndb_enable_pci_clocks(dev)))
		return (error);

	/* Identify the chip and enumerate the bridged cores */
	hostb_devclass = bhndb_expected_pci_devclass(dev);
	if ((error = bhndb_pci_probe_alloc(&probe, dev, hostb_devclass)))
		goto cleanup;

	/* Look for a matching core table entry */
	if ((entry = bhndb_pci_find_core(&probe->hostb_core)) == NULL) {
		error = ENXIO;
		goto cleanup;
	}

	device_set_desc(dev, "PCI-BHND bridge");

	/* fall-through */
	error = BUS_PROBE_DEFAULT;

cleanup:
	if (probe != NULL)
		bhndb_pci_probe_free(probe);

	bhndb_disable_pci_clocks(dev);

	return (error);
}