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
struct TYPE_5__ {int /*<<< orphan*/  call_lock; int /*<<< orphan*/  version; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ig4iic_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  IG4_DEVICE_IDLE ; 
 scalar_t__ IG4_HAS_ADDREGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IG4_REG_DEVIDLE_CTRL ; 
 int /*<<< orphan*/  IG4_REG_RESETS_SKL ; 
 int /*<<< orphan*/  IG4_RESETS_ASSERT_SKL ; 
 int bus_generic_suspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_controller (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
ig4iic_suspend(ig4iic_softc_t *sc)
{
	int error;

	/* suspend all children */
	error = bus_generic_suspend(sc->dev);

	sx_xlock(&sc->call_lock);
	set_controller(sc, 0);
	if (IG4_HAS_ADDREGS(sc->version)) {
		/*
		 * Place the device in the idle state, just to be safe
		 */
		reg_write(sc, IG4_REG_DEVIDLE_CTRL, IG4_DEVICE_IDLE);
		/*
		 * Controller can become dysfunctional if I2C lines are pulled
		 * down when suspend procedure turns off power to I2C device.
		 * Place device in the reset state to avoid this.
		 */
		reg_write(sc, IG4_REG_RESETS_SKL, IG4_RESETS_ASSERT_SKL);
	}
	sx_xunlock(&sc->call_lock);

	return (error);
}