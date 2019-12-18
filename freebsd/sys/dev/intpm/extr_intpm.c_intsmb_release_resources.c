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
struct intsmb_softc {int /*<<< orphan*/  lock; scalar_t__ io_res; int /*<<< orphan*/  io_rid; scalar_t__ irq_res; scalar_t__ irq_hand; scalar_t__ smbus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 struct intsmb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
intsmb_release_resources(device_t dev)
{
	struct intsmb_softc *sc = device_get_softc(dev);

	if (sc->smbus)
		device_delete_child(dev, sc->smbus);
	if (sc->irq_hand)
		bus_teardown_intr(dev, sc->irq_res, sc->irq_hand);
	if (sc->irq_res)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->irq_res);
	if (sc->io_res)
		bus_release_resource(dev, SYS_RES_IOPORT, sc->io_rid,
		    sc->io_res);
	mtx_destroy(&sc->lock);
}