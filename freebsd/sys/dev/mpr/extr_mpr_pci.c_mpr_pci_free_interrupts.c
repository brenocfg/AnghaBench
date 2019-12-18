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
struct mpr_softc {int msi_msgs; int /*<<< orphan*/  mpr_dev; struct mpr_queue* queues; } ;
struct mpr_queue {int /*<<< orphan*/ * irq; int /*<<< orphan*/  irq_rid; int /*<<< orphan*/  intrhand; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
mpr_pci_free_interrupts(struct mpr_softc *sc)
{
	struct mpr_queue *q;
	int i;

	if (sc->queues == NULL)
		return;

	for (i = 0; i < sc->msi_msgs; i++) {
		q = &sc->queues[i];
		if (q->irq != NULL) {
			bus_teardown_intr(sc->mpr_dev, q->irq,
			    q->intrhand);
			bus_release_resource(sc->mpr_dev, SYS_RES_IRQ,
			    q->irq_rid, q->irq);
		}
	}
}