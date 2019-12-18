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
struct vtpci_softc {int vtpci_flags; } ;
typedef  enum intr_type { ____Placeholder_intr_type } intr_type ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int VTPCI_FLAG_LEGACY ; 
 int VTPCI_FLAG_MSI ; 
 int VTPCI_FLAG_SHARED_MSIX ; 
 scalar_t__ bootverbose ; 
 struct vtpci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int vtpci_alloc_intr_legacy (struct vtpci_softc*) ; 
 int vtpci_alloc_intr_msi (struct vtpci_softc*) ; 
 int vtpci_alloc_intr_msix_pervq (struct vtpci_softc*) ; 
 int vtpci_alloc_intr_msix_shared (struct vtpci_softc*) ; 
 int /*<<< orphan*/  vtpci_cleanup_setup_intr_attempt (struct vtpci_softc*) ; 
 scalar_t__ vtpci_setup_interrupts (struct vtpci_softc*,int) ; 

__attribute__((used)) static int
vtpci_setup_intr(device_t dev, enum intr_type type)
{
	struct vtpci_softc *sc;
	int attempt, error;

	sc = device_get_softc(dev);

	for (attempt = 0; attempt < 5; attempt++) {
		/*
		 * Start with the most desirable interrupt configuration and
		 * fallback towards less desirable ones.
		 */
		switch (attempt) {
		case 0:
			error = vtpci_alloc_intr_msix_pervq(sc);
			break;
		case 1:
			error = vtpci_alloc_intr_msix_shared(sc);
			break;
		case 2:
			error = vtpci_alloc_intr_msi(sc);
			break;
		case 3:
			error = vtpci_alloc_intr_legacy(sc);
			break;
		default:
			device_printf(dev,
			    "exhausted all interrupt allocation attempts\n");
			return (ENXIO);
		}

		if (error == 0 && vtpci_setup_interrupts(sc, type) == 0)
			break;

		vtpci_cleanup_setup_intr_attempt(sc);
	}

	if (bootverbose) {
		if (sc->vtpci_flags & VTPCI_FLAG_LEGACY)
			device_printf(dev, "using legacy interrupt\n");
		else if (sc->vtpci_flags & VTPCI_FLAG_MSI)
			device_printf(dev, "using MSI interrupt\n");
		else if (sc->vtpci_flags & VTPCI_FLAG_SHARED_MSIX)
			device_printf(dev, "using shared MSIX interrupts\n");
		else
			device_printf(dev, "using per VQ MSIX interrupts\n");
	}

	return (0);
}