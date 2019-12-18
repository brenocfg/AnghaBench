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
typedef  scalar_t__ u_int ;
struct bge_softc {int /*<<< orphan*/  bge_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ PCI_FUNCMAX ; 
 int /*<<< orphan*/ * pci_find_dbsf (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ pci_get_bus (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_domain (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_function (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_slot (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bge_has_multiple_ports(struct bge_softc *sc)
{
	device_t dev = sc->bge_dev;
	u_int b, d, f, fscan, s;

	d = pci_get_domain(dev);
	b = pci_get_bus(dev);
	s = pci_get_slot(dev);
	f = pci_get_function(dev);
	for (fscan = 0; fscan <= PCI_FUNCMAX; fscan++)
		if (fscan != f && pci_find_dbsf(d, b, s, fscan) != NULL)
			return (1);
	return (0);
}