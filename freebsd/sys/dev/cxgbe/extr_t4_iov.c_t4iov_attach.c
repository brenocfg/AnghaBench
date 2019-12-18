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
struct t4iov_softc {int /*<<< orphan*/ * sc_main; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ T4_IS_MAIN_READY (int /*<<< orphan*/ *) ; 
 struct t4iov_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pci_find_dbsf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_domain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ) ; 
 int t4iov_attach_child (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
t4iov_attach(device_t dev)
{
	struct t4iov_softc *sc;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	sc->sc_main = pci_find_dbsf(pci_get_domain(dev), pci_get_bus(dev),
	    pci_get_slot(dev), 4);
	if (sc->sc_main == NULL)
		return (ENXIO);
	if (T4_IS_MAIN_READY(sc->sc_main) == 0)
		return (t4iov_attach_child(dev));
	return (0);
}