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
struct ahci_controller {int numirqs; int /*<<< orphan*/  ch_mtx; int /*<<< orphan*/  sc_iomem; int /*<<< orphan*/  dma_tag; TYPE_1__* irqs; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ r_irq; int /*<<< orphan*/  r_irq_rid; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  ahci_free_mem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 struct ahci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_fini (int /*<<< orphan*/ *) ; 

int
ahci_detach(device_t dev)
{
	struct ahci_controller *ctlr = device_get_softc(dev);
	int i;

	/* Detach & delete all children */
	device_delete_children(dev);

	/* Free interrupts. */
	for (i = 0; i < ctlr->numirqs; i++) {
		if (ctlr->irqs[i].r_irq) {
			bus_teardown_intr(dev, ctlr->irqs[i].r_irq,
			    ctlr->irqs[i].handle);
			bus_release_resource(dev, SYS_RES_IRQ,
			    ctlr->irqs[i].r_irq_rid, ctlr->irqs[i].r_irq);
		}
	}
	bus_dma_tag_destroy(ctlr->dma_tag);
	/* Free memory. */
	rman_fini(&ctlr->sc_iomem);
	ahci_free_mem(dev);
	mtx_destroy(&ctlr->ch_mtx);
	return (0);
}