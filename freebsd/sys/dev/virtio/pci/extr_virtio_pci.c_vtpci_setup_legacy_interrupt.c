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
struct vtpci_interrupt {int /*<<< orphan*/  vti_handler; int /*<<< orphan*/  vti_irq; } ;
struct vtpci_softc {int /*<<< orphan*/  vtpci_dev; struct vtpci_interrupt vtpci_device_interrupt; } ;
typedef  enum intr_type { ____Placeholder_intr_type } intr_type ;

/* Variables and functions */
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vtpci_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtpci_legacy_intr ; 

__attribute__((used)) static int
vtpci_setup_legacy_interrupt(struct vtpci_softc *sc, enum intr_type type)
{
	struct vtpci_interrupt *intr;
	int error;

	intr = &sc->vtpci_device_interrupt;
	error = bus_setup_intr(sc->vtpci_dev, intr->vti_irq, type, NULL,
	    vtpci_legacy_intr, sc, &intr->vti_handler);

	return (error);
}