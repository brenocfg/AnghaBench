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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_NOWILDCARD ; 
 int ENXIO ; 
 int bhnd_sprom_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhndb_pci_driver ; 
 int /*<<< orphan*/ * device_get_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhndb_pci_sprom_probe(device_t dev)
{
	device_t	bridge;
	int		error;

	/* Our parent must be a PCI-BHND bridge */
	bridge = device_get_parent(dev);
	if (device_get_driver(bridge) != &bhndb_pci_driver)
		return (ENXIO);

	/* Defer to default driver implementation */
	if ((error = bhnd_sprom_probe(dev)) > 0)
		return (error);

	return (BUS_PROBE_NOWILDCARD);
}