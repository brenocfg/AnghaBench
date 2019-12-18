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
struct vtpci_interrupt {int dummy; } ;
struct vtpci_softc {int vtpci_flags; int vtpci_nmsix_resources; struct vtpci_interrupt* vtpci_msix_vq_interrupts; struct vtpci_interrupt vtpci_device_interrupt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int VTPCI_FLAG_LEGACY ; 
 int VTPCI_FLAG_MSI ; 
 struct vtpci_interrupt* malloc (int,int /*<<< orphan*/ ,int) ; 
 int vtpci_alloc_interrupt (struct vtpci_softc*,int,int,struct vtpci_interrupt*) ; 

__attribute__((used)) static int
vtpci_alloc_intr_resources(struct vtpci_softc *sc)
{
	struct vtpci_interrupt *intr;
	int i, rid, flags, nvq_intrs, error;

	rid = 0;
	flags = RF_ACTIVE;

	if (sc->vtpci_flags & VTPCI_FLAG_LEGACY)
		flags |= RF_SHAREABLE;
	else
		rid = 1;

	/*
	 * For legacy and MSI interrupts, this single resource handles all
	 * interrupts. For MSIX, this resource is used for the configuration
	 * changed interrupt.
	 */
	intr = &sc->vtpci_device_interrupt;
	error = vtpci_alloc_interrupt(sc, rid, flags, intr);
	if (error || sc->vtpci_flags & (VTPCI_FLAG_LEGACY | VTPCI_FLAG_MSI))
		return (error);

	/* Subtract one for the configuration changed interrupt. */
	nvq_intrs = sc->vtpci_nmsix_resources - 1;

	intr = sc->vtpci_msix_vq_interrupts = malloc(nvq_intrs *
	    sizeof(struct vtpci_interrupt), M_DEVBUF, M_NOWAIT | M_ZERO);
	if (sc->vtpci_msix_vq_interrupts == NULL)
		return (ENOMEM);

	for (i = 0, rid++; i < nvq_intrs; i++, rid++, intr++) {
		error = vtpci_alloc_interrupt(sc, rid, flags, intr);
		if (error)
			return (error);
	}

	return (0);
}