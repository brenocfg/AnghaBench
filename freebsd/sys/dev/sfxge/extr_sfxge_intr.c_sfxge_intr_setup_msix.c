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
struct sfxge_intr {int n_alloc; struct resource* msix_res; int /*<<< orphan*/  type; } ;
struct sfxge_softc {int /*<<< orphan*/  evq_max; struct sfxge_intr intr; int /*<<< orphan*/  dev; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_INTR_MESSAGE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MIN (int,int /*<<< orphan*/ ) ; 
 int PCIR_BAR (int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 scalar_t__ pci_alloc_msix (int /*<<< orphan*/ ,int*) ; 
 int pci_msix_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 scalar_t__ sfxge_intr_alloc (struct sfxge_softc*,int) ; 

__attribute__((used)) static int
sfxge_intr_setup_msix(struct sfxge_softc *sc)
{
	struct sfxge_intr *intr;
	struct resource *resp;
	device_t dev;
	int count;
	int rid;

	dev = sc->dev;
	intr = &sc->intr;

	/* Check if MSI-X is available. */
	count = pci_msix_count(dev);
	if (count == 0)
		return (EINVAL);

	/* Do not try to allocate more than already estimated EVQ maximum */
	KASSERT(sc->evq_max > 0, ("evq_max is zero"));
	count = MIN(count, sc->evq_max);

	rid = PCIR_BAR(4);
	resp = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (resp == NULL)
		return (ENOMEM);

	if (pci_alloc_msix(dev, &count) != 0) {
		bus_release_resource(dev, SYS_RES_MEMORY, rid, resp);
		return (ENOMEM);
	}

	/* Allocate interrupt handlers. */
	if (sfxge_intr_alloc(sc, count) != 0) {
		bus_release_resource(dev, SYS_RES_MEMORY, rid, resp);
		pci_release_msi(dev);
		return (ENOMEM);
	}

	intr->type = EFX_INTR_MESSAGE;
	intr->n_alloc = count;
	intr->msix_res = resp;

	return (0);
}