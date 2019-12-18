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
struct ppb_data {int /*<<< orphan*/  ppc_lock; int /*<<< orphan*/ * ppc_irq_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_READ_IVAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t*) ; 
 int BUS_WRITE_IVAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t) ; 
 int /*<<< orphan*/  PPC_IVAR_INTR_HANDLER ; 
 int /*<<< orphan*/  PPC_IVAR_LOCK ; 
 int /*<<< orphan*/  RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct ppb_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_scan_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppbus_intr ; 

__attribute__((used)) static int
ppbus_attach(device_t dev)
{
	struct ppb_data *ppb = device_get_softc(dev);
	int error, rid;

	error = BUS_READ_IVAR(device_get_parent(dev), dev, PPC_IVAR_LOCK,
	    (uintptr_t *)&ppb->ppc_lock);
	if (error) {
		device_printf(dev, "Unable to fetch parent's lock\n");
		return (error);
	}

	rid = 0;
	ppb->ppc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_SHAREABLE);
	if (ppb->ppc_irq_res != NULL) {
		mtx_lock(ppb->ppc_lock);
		error = BUS_WRITE_IVAR(device_get_parent(dev), dev,
		    PPC_IVAR_INTR_HANDLER, (uintptr_t)&ppbus_intr);
		mtx_unlock(ppb->ppc_lock);
		if (error) {
			device_printf(dev, "Unable to set interrupt handler\n");
			return (error);
		}
	}

	/* Locate our children */
	bus_generic_probe(dev);

#ifndef DONTPROBE_1284
	/* detect IEEE1284 compliant devices */
	mtx_lock(ppb->ppc_lock);
	ppb_scan_bus(dev);
	mtx_unlock(ppb->ppc_lock);
#endif /* !DONTPROBE_1284 */

	/* launch attachment of the added children */
	bus_generic_attach(dev);

	return (0);
}