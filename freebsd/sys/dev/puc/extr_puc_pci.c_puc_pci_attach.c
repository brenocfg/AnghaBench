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
struct puc_softc {int sc_msi; int sc_irid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct puc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int puc_bfe_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puc_msi_disable ; 

__attribute__((used)) static int
puc_pci_attach(device_t dev)
{
	struct puc_softc *sc;
	int error, count;

	sc = device_get_softc(dev);

	if (!puc_msi_disable) {
		count = 1;

		if (pci_alloc_msi(dev, &count) == 0) {
			sc->sc_msi = 1;
			sc->sc_irid = 1;
		}
	}

	error = puc_bfe_attach(dev);

	if (error != 0 && sc->sc_msi)
		pci_release_msi(dev);

	return (error);
}