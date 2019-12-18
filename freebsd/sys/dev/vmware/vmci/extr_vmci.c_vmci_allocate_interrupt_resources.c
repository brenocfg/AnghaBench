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
struct vmci_softc {int vmci_num_intr; scalar_t__ vmci_intr_type; TYPE_1__* vmci_intrs; int /*<<< orphan*/  vmci_dev; } ;
struct resource {int dummy; } ;
struct TYPE_2__ {int vmci_rid; struct resource* vmci_irq; } ;

/* Variables and functions */
 int ENXIO ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 scalar_t__ VMCI_INTR_TYPE_INTX ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
vmci_allocate_interrupt_resources(struct vmci_softc *sc)
{
	struct resource *irq;
	int flags, i, rid;

	flags = RF_ACTIVE;
	flags |= (sc->vmci_num_intr == 1) ? RF_SHAREABLE : 0;
	rid = (sc->vmci_intr_type == VMCI_INTR_TYPE_INTX) ? 0 : 1;

	for (i = 0; i < sc->vmci_num_intr; i++, rid++) {
		irq = bus_alloc_resource_any(sc->vmci_dev, SYS_RES_IRQ, &rid,
		    flags);
		if (irq == NULL)
			return (ENXIO);
		sc->vmci_intrs[i].vmci_irq = irq;
		sc->vmci_intrs[i].vmci_rid = rid;
	}

	return (0);
}