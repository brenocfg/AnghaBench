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
struct vtpci_softc {int vtpci_nmsix_resources; int /*<<< orphan*/  vtpci_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ pci_alloc_msix (int /*<<< orphan*/ ,int*) ; 
 int pci_msix_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vtpci_alloc_msix(struct vtpci_softc *sc, int nvectors)
{
	device_t dev;
	int nmsix, cnt, required;

	dev = sc->vtpci_dev;

	/* Allocate an additional vector for the config changes. */
	required = nvectors + 1;

	nmsix = pci_msix_count(dev);
	if (nmsix < required)
		return (1);

	cnt = required;
	if (pci_alloc_msix(dev, &cnt) == 0 && cnt >= required) {
		sc->vtpci_nmsix_resources = required;
		return (0);
	}

	pci_release_msi(dev);

	return (1);
}