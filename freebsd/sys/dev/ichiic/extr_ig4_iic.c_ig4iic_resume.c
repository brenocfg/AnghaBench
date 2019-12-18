#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  call_lock; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ ig4iic_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  IG4_HAS_ADDREGS (int /*<<< orphan*/ ) ; 
 int bus_generic_resume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ig4iic_set_config (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int ig4iic_resume(ig4iic_softc_t *sc)
{
	int error;

	sx_xlock(&sc->call_lock);
	if (ig4iic_set_config(sc, IG4_HAS_ADDREGS(sc->version)))
		device_printf(sc->dev, "controller error during resume\n");
	sx_xunlock(&sc->call_lock);

	error = bus_generic_resume(sc->dev);

	return (error);
}