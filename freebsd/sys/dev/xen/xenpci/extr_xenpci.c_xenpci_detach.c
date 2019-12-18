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
struct xenpci_softc {int /*<<< orphan*/ * intr_cookie; int /*<<< orphan*/  res_irq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ BUS_TEARDOWN_INTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct xenpci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int xenpci_deallocate_resources (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xenpci_detach(device_t dev)
{
	struct xenpci_softc *scp = device_get_softc(dev);
	device_t parent = device_get_parent(dev);

	/*
	 * Take our interrupt handler out of the list of handlers
	 * that can handle this irq.
	 */
	if (scp->intr_cookie != NULL) {
		if (BUS_TEARDOWN_INTR(parent, dev,
		    scp->res_irq, scp->intr_cookie) != 0)
			device_printf(dev,
			    "intr teardown failed.. continuing\n");
		scp->intr_cookie = NULL;
	}

	/*
	 * Deallocate any system resources we may have
	 * allocated on behalf of this driver.
	 */
	return (xenpci_deallocate_resources(dev));
}