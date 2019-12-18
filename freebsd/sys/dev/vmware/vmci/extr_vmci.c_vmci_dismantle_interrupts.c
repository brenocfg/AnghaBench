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
struct vmci_softc {int vmci_num_intr; scalar_t__ vmci_intr_type; int /*<<< orphan*/  vmci_interrupt_bm_task; int /*<<< orphan*/  vmci_interrupt_dq_task; int /*<<< orphan*/  vmci_dev; struct vmci_interrupt* vmci_intrs; } ;
struct vmci_interrupt {int vmci_rid; int /*<<< orphan*/ * vmci_irq; int /*<<< orphan*/ * vmci_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 scalar_t__ VMCI_INTR_TYPE_INTX ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * data_buffer ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi ; 

__attribute__((used)) static void
vmci_dismantle_interrupts(struct vmci_softc *sc)
{
	struct vmci_interrupt *intr;
	int i;

	for (i = 0; i < sc->vmci_num_intr; i++) {
		intr = &sc->vmci_intrs[i];
		if (intr->vmci_handler != NULL) {
			bus_teardown_intr(sc->vmci_dev, intr->vmci_irq,
			    intr->vmci_handler);
			intr->vmci_handler = NULL;
		}
		if (intr->vmci_irq != NULL) {
			bus_release_resource(sc->vmci_dev, SYS_RES_IRQ,
			    intr->vmci_rid, intr->vmci_irq);
			intr->vmci_irq = NULL;
			intr->vmci_rid = -1;
		}
	}

	if ((sc->vmci_intr_type != VMCI_INTR_TYPE_INTX) &&
	    (sc->vmci_num_intr))
		pci_release_msi(sc->vmci_dev);

	taskqueue_drain(taskqueue_swi, &sc->vmci_interrupt_dq_task);
	taskqueue_drain(taskqueue_swi, &sc->vmci_interrupt_bm_task);

	if (data_buffer != NULL)
		free(data_buffer, M_DEVBUF);
}