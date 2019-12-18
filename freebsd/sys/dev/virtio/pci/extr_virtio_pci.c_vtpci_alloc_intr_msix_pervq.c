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
struct vtpci_softc {int vtpci_flags; int vtpci_nvqs; TYPE_1__* vtpci_vqs; } ;
struct TYPE_2__ {scalar_t__ vtv_no_intr; } ;

/* Variables and functions */
 int ENOTSUP ; 
 int VTPCI_FLAG_MSIX ; 
 int VTPCI_FLAG_NO_MSIX ; 
 int vtpci_alloc_msix (struct vtpci_softc*,int) ; 
 scalar_t__ vtpci_disable_msix ; 

__attribute__((used)) static int
vtpci_alloc_intr_msix_pervq(struct vtpci_softc *sc)
{
	int i, nvectors, error;

	if (vtpci_disable_msix != 0 ||
	    sc->vtpci_flags & VTPCI_FLAG_NO_MSIX)
		return (ENOTSUP);

	for (nvectors = 0, i = 0; i < sc->vtpci_nvqs; i++) {
		if (sc->vtpci_vqs[i].vtv_no_intr == 0)
			nvectors++;
	}

	error = vtpci_alloc_msix(sc, nvectors);
	if (error)
		return (error);

	sc->vtpci_flags |= VTPCI_FLAG_MSIX;

	return (0);
}