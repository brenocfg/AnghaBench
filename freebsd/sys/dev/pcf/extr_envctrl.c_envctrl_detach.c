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
struct pcf_softc {scalar_t__ res_irq; scalar_t__ res_ioport; int /*<<< orphan*/  pcf_lock; int /*<<< orphan*/  rid_ioport; int /*<<< orphan*/  rid_irq; int /*<<< orphan*/  intr_cookie; int /*<<< orphan*/  iicbus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct pcf_softc* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
envctrl_detach(device_t dev)
{
	struct pcf_softc *sc;
	int rv;

	sc = DEVTOSOFTC(dev);

	if ((rv = bus_generic_detach(dev)) != 0)
		return (rv);

	if ((rv = device_delete_child(dev, sc->iicbus)) != 0)
		return (rv);

	if (sc->res_irq != 0) {
		bus_teardown_intr(dev, sc->res_irq, sc->intr_cookie);
		bus_release_resource(dev, SYS_RES_IRQ, sc->rid_irq, sc->res_irq);
	}

	bus_release_resource(dev, SYS_RES_MEMORY, sc->rid_ioport, sc->res_ioport);
	mtx_destroy(&sc->pcf_lock);

	return (0);
}