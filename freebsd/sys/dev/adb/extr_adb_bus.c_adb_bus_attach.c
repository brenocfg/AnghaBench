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
struct TYPE_2__ {int /*<<< orphan*/  ich_arg; int /*<<< orphan*/  ich_func; } ;
struct adb_softc {TYPE_1__ enum_hook; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  adb_bus_enumerate ; 
 scalar_t__ config_intrhook_establish (TYPE_1__*) ; 
 struct adb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
adb_bus_attach(device_t dev)
{
	struct adb_softc *sc = device_get_softc(dev);
	sc->enum_hook.ich_func = adb_bus_enumerate;
	sc->enum_hook.ich_arg = dev;

	/*
	 * We should wait until interrupts are enabled to try to probe
	 * the bus. Enumerating the ADB involves receiving packets,
	 * which works best with interrupts enabled.
	 */
	
	if (config_intrhook_establish(&sc->enum_hook) != 0)
		return (ENOMEM);

	return (0);
}