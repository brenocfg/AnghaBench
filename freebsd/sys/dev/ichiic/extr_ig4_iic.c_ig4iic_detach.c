#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  call_lock; int /*<<< orphan*/  io_lock; int /*<<< orphan*/ * intr_handle; int /*<<< orphan*/ * iicbus; int /*<<< orphan*/  intr_res; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ig4iic_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  IG4_REG_INTR_MASK ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_controller (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
ig4iic_detach(ig4iic_softc_t *sc)
{
	int error;

	if (device_is_attached(sc->dev)) {
		error = bus_generic_detach(sc->dev);
		if (error)
			return (error);
	}
	if (sc->iicbus)
		device_delete_child(sc->dev, sc->iicbus);
	if (sc->intr_handle)
		bus_teardown_intr(sc->dev, sc->intr_res, sc->intr_handle);

	sx_xlock(&sc->call_lock);

	sc->iicbus = NULL;
	sc->intr_handle = NULL;
	reg_write(sc, IG4_REG_INTR_MASK, 0);
	set_controller(sc, 0);

	sx_xunlock(&sc->call_lock);

	mtx_destroy(&sc->io_lock);
	sx_destroy(&sc->call_lock);

	return (0);
}