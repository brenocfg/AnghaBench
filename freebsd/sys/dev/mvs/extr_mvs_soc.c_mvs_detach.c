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
struct TYPE_2__ {scalar_t__ r_irq; int /*<<< orphan*/  r_irq_rid; int /*<<< orphan*/  handle; } ;
struct mvs_controller {int /*<<< orphan*/  mtx; scalar_t__ r_mem; int /*<<< orphan*/  r_rid; int /*<<< orphan*/  sc_iomem; TYPE_1__ irq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 struct mvs_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mvs_detach(device_t dev)
{
	struct mvs_controller *ctlr = device_get_softc(dev);

	/* Detach & delete all children */
	device_delete_children(dev);

	/* Free interrupt. */
	if (ctlr->irq.r_irq) {
		bus_teardown_intr(dev, ctlr->irq.r_irq,
		    ctlr->irq.handle);
		bus_release_resource(dev, SYS_RES_IRQ,
		    ctlr->irq.r_irq_rid, ctlr->irq.r_irq);
	}
	/* Free memory. */
	rman_fini(&ctlr->sc_iomem);
	if (ctlr->r_mem)
		bus_release_resource(dev, SYS_RES_MEMORY, ctlr->r_rid, ctlr->r_mem);
	mtx_destroy(&ctlr->mtx);
	return (0);
}