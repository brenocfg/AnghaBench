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
struct vtpci_softc {int /*<<< orphan*/  vtpci_dev; } ;
struct vtpci_interrupt {int vti_rid; int /*<<< orphan*/ * vti_irq; int /*<<< orphan*/ * vti_handler; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vtpci_free_interrupt(struct vtpci_softc *sc, struct vtpci_interrupt *intr)
{
	device_t dev;

	dev = sc->vtpci_dev;

	if (intr->vti_handler != NULL) {
		bus_teardown_intr(dev, intr->vti_irq, intr->vti_handler);
		intr->vti_handler = NULL;
	}

	if (intr->vti_irq != NULL) {
		bus_release_resource(dev, SYS_RES_IRQ, intr->vti_rid,
		    intr->vti_irq);
		intr->vti_irq = NULL;
		intr->vti_rid = -1;
	}
}