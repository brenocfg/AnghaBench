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
struct xenpci_softc {int /*<<< orphan*/ * res_irq; int /*<<< orphan*/  rid_irq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct xenpci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  xenpci_deallocate_resources (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xenpci_allocate_resources(device_t dev)
{
	struct xenpci_softc *scp = device_get_softc(dev);

	scp->res_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ,
			&scp->rid_irq, RF_SHAREABLE|RF_ACTIVE);
	if (scp->res_irq == NULL) {
		printf("xenpci Could not allocate irq.\n");
		goto errexit;
	}

	return (0);

errexit:
	/* Cleanup anything we may have assigned. */
	xenpci_deallocate_resources(dev);
	return (ENXIO); /* For want of a better idea. */
}