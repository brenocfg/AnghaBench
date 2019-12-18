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
struct as3722_softc {int /*<<< orphan*/ * irq_res; int /*<<< orphan*/ * irq_h; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_DESTROY (struct as3722_softc*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct as3722_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
as3722_detach(device_t dev)
{
	struct as3722_softc *sc;

	sc = device_get_softc(dev);
	if (sc->irq_h != NULL)
		bus_teardown_intr(dev, sc->irq_res, sc->irq_h);
	if (sc->irq_res != NULL)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->irq_res);
	LOCK_DESTROY(sc);

	return (bus_generic_detach(dev));
}