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
struct an_softc {int irq_rid; struct resource* irq_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 int RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 struct an_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
an_alloc_irq(device_t dev, int rid, int flags)
{
	struct an_softc *sc = device_get_softc(dev);
	struct resource *res;

	res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
				     (RF_ACTIVE | flags));
	if (res) {
		sc->irq_rid = rid;
		sc->irq_res = res;
		return (0);
	} else {
		return (ENOENT);
	}
}