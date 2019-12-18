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
struct ppc_data {scalar_t__ res_irq; scalar_t__ res_ioport; scalar_t__ res_drq; int /*<<< orphan*/  ppc_lock; int /*<<< orphan*/  rid_drq; int /*<<< orphan*/  rid_ioport; int /*<<< orphan*/  rid_irq; int /*<<< orphan*/  intr_cookie; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ppc_data* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

int
ppc_detach(device_t dev)
{
	struct ppc_data *ppc = DEVTOSOFTC(dev);

	if (ppc->res_irq == 0) {
		return (ENXIO);
	}

	/* detach & delete all children */
	device_delete_children(dev);

	if (ppc->res_irq != 0) {
		bus_teardown_intr(dev, ppc->res_irq, ppc->intr_cookie);
		bus_release_resource(dev, SYS_RES_IRQ, ppc->rid_irq,
				     ppc->res_irq);
	}
	if (ppc->res_ioport != 0) {
		bus_release_resource(dev, SYS_RES_IOPORT, ppc->rid_ioport,
				     ppc->res_ioport);
	}
	if (ppc->res_drq != 0) {
		bus_release_resource(dev, SYS_RES_DRQ, ppc->rid_drq,
				     ppc->res_drq);
	}

	mtx_destroy(&ppc->ppc_lock);

	return (0);
}