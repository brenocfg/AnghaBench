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
struct resource {int dummy; } ;
struct cbb_softc {struct resource* base_res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; struct resource* irq_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 struct resource* bus_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int,int,int /*<<< orphan*/ ) ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*) ; 
 struct cbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int isa_intr_mask ; 
 int /*<<< orphan*/  rman_get_bushandle (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bustag (struct resource*) ; 

__attribute__((used)) static int
cbb_isa_activate(device_t dev)
{
	struct cbb_softc *sc = device_get_softc(dev);
	struct resource *res;
	int rid;
	int i;

	/* A little bogus, but go ahead and get the irq for CSC events */
	rid = 0;
	res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid, RF_ACTIVE);
	if (res == NULL) {
		/*
		 * No IRQ specified, find one.  This can be due to the PnP
		 * data not specifying any IRQ, or the default kernel not
		 * assinging an IRQ.
		 */
		for (i = 0; i < 16 && res == NULL; i++) {
			if (((1 << i) & isa_intr_mask) == 0)
				continue;
			res = bus_alloc_resource(dev, SYS_RES_IRQ, &rid, i, i,
			    1, RF_ACTIVE);
		}
	}
	if (res == NULL)
		return (ENXIO);
	sc->irq_res = res;
	rid = 0;
	res = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &rid, RF_ACTIVE);
	if (res == NULL) {
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->irq_res);
		sc->irq_res = NULL;
		device_printf(dev, "Cannot allocate I/O\n");
		return (ENOMEM);
	}
	sc->bst = rman_get_bustag(res);
	sc->bsh = rman_get_bushandle(res);
	sc->base_res = res;
	return (0);
}