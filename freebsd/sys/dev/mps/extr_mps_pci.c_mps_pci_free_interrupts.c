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
struct mps_softc {int msi_msgs; int /*<<< orphan*/  mps_dev; struct mps_queue* queues; } ;
struct mps_queue {int /*<<< orphan*/ * irq; int /*<<< orphan*/  irq_rid; int /*<<< orphan*/  intrhand; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
mps_pci_free_interrupts(struct mps_softc *sc)
{
	struct mps_queue *q;
	int i;

	if (sc->queues == NULL)
		return;

	for (i = 0; i < sc->msi_msgs; i++) {
		q = &sc->queues[i];
		if (q->irq != NULL) {
			bus_teardown_intr(sc->mps_dev, q->irq,
			    q->intrhand);
			bus_release_resource(sc->mps_dev, SYS_RES_IRQ,
			    q->irq_rid, q->irq);
		}
	}
}