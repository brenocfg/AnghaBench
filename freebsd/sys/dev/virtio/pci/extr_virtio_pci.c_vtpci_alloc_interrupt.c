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
struct vtpci_interrupt {int vti_rid; struct resource* vti_irq; } ;
struct resource {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
vtpci_alloc_interrupt(struct vtpci_softc *sc, int rid, int flags,
    struct vtpci_interrupt *intr)
{
	struct resource *irq;

	irq = bus_alloc_resource_any(sc->vtpci_dev, SYS_RES_IRQ, &rid, flags);
	if (irq == NULL)
		return (ENXIO);

	intr->vti_irq = irq;
	intr->vti_rid = rid;

	return (0);
}