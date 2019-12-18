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
struct resource_list {int dummy; } ;
struct simplebus_devinfo {struct resource_list rl; } ;
struct cesa_softc {int sc_cesa_engine_id; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  rid; } ;

/* Variables and functions */
 scalar_t__ CESA0_CESA_ADDR ; 
 scalar_t__ CESA0_TDMA_ADDR ; 
 scalar_t__ CESA1_CESA_ADDR ; 
 scalar_t__ CESA1_TDMA_ADDR ; 
 scalar_t__ CESA_CESA_SIZE ; 
 scalar_t__ CESA_TDMA_SIZE ; 
 int ENXIO ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int cesa_attach_late (int /*<<< orphan*/ ) ; 
 struct simplebus_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct cesa_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  resource_list_add (struct resource_list*,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  resource_list_delete (struct resource_list*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* resource_list_find (struct resource_list*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  simplebus_add_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cesa_attach(device_t dev)
{
	static int engine_idx = 0;
	struct simplebus_devinfo *ndi;
	struct resource_list *rl;
	struct cesa_softc *sc;

	if (!ofw_bus_is_compatible(dev, "marvell,armada-38x-crypto"))
		return (cesa_attach_late(dev));

	/*
	 * Get simplebus_devinfo which contains
	 * resource list filled with adresses and
	 * interrupts read form FDT.
	 * Let's correct it by splitting resources
	 * for each engine.
	 */
	if ((ndi = device_get_ivars(dev)) == NULL)
		return (ENXIO);

	rl = &ndi->rl;

	switch (engine_idx) {
		case 0:
			/* Update regs values */
			resource_list_add(rl, SYS_RES_MEMORY, 0, CESA0_TDMA_ADDR,
			    CESA0_TDMA_ADDR + CESA_TDMA_SIZE - 1, CESA_TDMA_SIZE);
			resource_list_add(rl, SYS_RES_MEMORY, 1, CESA0_CESA_ADDR,
			    CESA0_CESA_ADDR + CESA_CESA_SIZE - 1, CESA_CESA_SIZE);

			/* Remove unused interrupt */
			resource_list_delete(rl, SYS_RES_IRQ, 1);
			break;

		case 1:
			/* Update regs values */
			resource_list_add(rl, SYS_RES_MEMORY, 0, CESA1_TDMA_ADDR,
			    CESA1_TDMA_ADDR + CESA_TDMA_SIZE - 1, CESA_TDMA_SIZE);
			resource_list_add(rl, SYS_RES_MEMORY, 1, CESA1_CESA_ADDR,
			    CESA1_CESA_ADDR + CESA_CESA_SIZE - 1, CESA_CESA_SIZE);

			/* Remove unused interrupt */
			resource_list_delete(rl, SYS_RES_IRQ, 0);
			resource_list_find(rl, SYS_RES_IRQ, 1)->rid = 0;
			break;

		default:
			device_printf(dev, "Bad cesa engine_idx\n");
			return (ENXIO);
	}

	sc = device_get_softc(dev);
	sc->sc_cesa_engine_id = engine_idx;

	/*
	 * Call simplebus_add_device only once.
	 * It will create second cesa driver instance
	 * with the same FDT node as first instance.
	 * When second driver reach this function,
	 * it will be configured to use second cesa engine
	 */
	if (engine_idx == 0)
		simplebus_add_device(device_get_parent(dev), ofw_bus_get_node(dev),
		    0, "cesa", 1, NULL);

	engine_idx++;

	return (cesa_attach_late(dev));
}