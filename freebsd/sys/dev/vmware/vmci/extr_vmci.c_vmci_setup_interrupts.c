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
struct vmci_softc {int vmci_num_intr; int /*<<< orphan*/  vmci_dev; struct vmci_interrupt* vmci_intrs; } ;
struct vmci_interrupt {int /*<<< orphan*/  vmci_handler; int /*<<< orphan*/  vmci_irq; } ;

/* Variables and functions */
 int INTR_EXCL ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  bus_describe_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmci_interrupt ; 
 int /*<<< orphan*/  vmci_interrupt_bm ; 

__attribute__((used)) static int
vmci_setup_interrupts(struct vmci_softc *sc)
{
	struct vmci_interrupt *intr;
	int error, flags;

	flags = INTR_TYPE_NET | INTR_MPSAFE;
	if (sc->vmci_num_intr > 1)
		flags |= INTR_EXCL;

	intr = &sc->vmci_intrs[0];
	error = bus_setup_intr(sc->vmci_dev, intr->vmci_irq, flags, NULL,
	    vmci_interrupt, NULL, &intr->vmci_handler);
	if (error)
		return (error);
	bus_describe_intr(sc->vmci_dev, intr->vmci_irq, intr->vmci_handler,
	    "vmci_interrupt");

	if (sc->vmci_num_intr == 2) {
		intr = &sc->vmci_intrs[1];
		error = bus_setup_intr(sc->vmci_dev, intr->vmci_irq, flags,
		    NULL, vmci_interrupt_bm, NULL, &intr->vmci_handler);
		if (error)
			return (error);
		bus_describe_intr(sc->vmci_dev, intr->vmci_irq,
		    intr->vmci_handler, "vmci_interrupt_bm");
	}

	return (0);
}