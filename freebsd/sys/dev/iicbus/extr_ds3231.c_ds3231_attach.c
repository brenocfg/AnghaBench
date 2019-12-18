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
struct TYPE_2__ {void* ich_arg; int /*<<< orphan*/  ich_func; } ;
struct ds3231_softc {int sc_last_c; TYPE_1__ enum_hook; scalar_t__ sc_year0; int /*<<< orphan*/  sc_addr; void* sc_dev; } ;
typedef  void* device_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ config_intrhook_establish (TYPE_1__*) ; 
 struct ds3231_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  ds3231_start ; 
 int /*<<< orphan*/  iicbus_get_addr (void*) ; 

__attribute__((used)) static int
ds3231_attach(device_t dev)
{
	struct ds3231_softc *sc;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_addr = iicbus_get_addr(dev);
	sc->sc_last_c = -1;
	sc->sc_year0 = 0;
	sc->enum_hook.ich_func = ds3231_start;
	sc->enum_hook.ich_arg = dev;

	/*
	 * We have to wait until interrupts are enabled.  Usually I2C read
	 * and write only works when the interrupts are available.
	 */
	if (config_intrhook_establish(&sc->enum_hook) != 0)
		return (ENOMEM);

	return (0);
}