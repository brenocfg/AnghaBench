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
struct xenpci_softc {scalar_t__ res_irq; int /*<<< orphan*/  rid_irq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_deactivate_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct xenpci_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xenpci_deallocate_resources(device_t dev)
{
	struct xenpci_softc *scp = device_get_softc(dev);

	if (scp->res_irq != 0) {
		bus_deactivate_resource(dev, SYS_RES_IRQ,
			scp->rid_irq, scp->res_irq);
		bus_release_resource(dev, SYS_RES_IRQ,
			scp->rid_irq, scp->res_irq);
		scp->res_irq = 0;
	}

	return (0);
}