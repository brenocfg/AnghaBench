#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  intr_handle; int /*<<< orphan*/  intr_res; int /*<<< orphan*/ * iicbus; int /*<<< orphan*/  version; int /*<<< orphan*/  call_lock; int /*<<< orphan*/  io_lock; } ;
typedef  TYPE_1__ ig4iic_softc_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IG4_HAS_ADDREGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IG4_I2C_ENABLE ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ig4iic_get_config (TYPE_1__*) ; 
 int /*<<< orphan*/  ig4iic_intr ; 
 int ig4iic_set_config (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ set_controller (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

int
ig4iic_attach(ig4iic_softc_t *sc)
{
	int error;

	mtx_init(&sc->io_lock, "IG4 I/O lock", NULL, MTX_SPIN);
	sx_init(&sc->call_lock, "IG4 call lock");

	ig4iic_get_config(sc);

	error = ig4iic_set_config(sc, IG4_HAS_ADDREGS(sc->version));
	if (error)
		goto done;

	sc->iicbus = device_add_child(sc->dev, "iicbus", -1);
	if (sc->iicbus == NULL) {
		device_printf(sc->dev, "iicbus driver not found\n");
		error = ENXIO;
		goto done;
	}

	if (set_controller(sc, IG4_I2C_ENABLE)) {
		device_printf(sc->dev, "controller error during attach-2\n");
		error = ENXIO;
		goto done;
	}
	if (set_controller(sc, 0)) {
		device_printf(sc->dev, "controller error during attach-3\n");
		error = ENXIO;
		goto done;
	}
	error = bus_setup_intr(sc->dev, sc->intr_res, INTR_TYPE_MISC | INTR_MPSAFE,
			       ig4iic_intr, NULL, sc, &sc->intr_handle);
	if (error) {
		device_printf(sc->dev,
			      "Unable to setup irq: error %d\n", error);
	}

	error = bus_generic_attach(sc->dev);
	if (error) {
		device_printf(sc->dev,
			      "failed to attach child: error %d\n", error);
	}

done:
	return (error);
}