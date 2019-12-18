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
struct adt746x_softc {TYPE_1__ enum_hook; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  adt746x_start ; 
 scalar_t__ config_intrhook_establish (TYPE_1__*) ; 
 struct adt746x_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
adt746x_attach(device_t dev)
{
	struct adt746x_softc *sc;

	sc = device_get_softc(dev);

	sc->enum_hook.ich_func = adt746x_start;
	sc->enum_hook.ich_arg = dev;

	/* We have to wait until interrupts are enabled. I2C read and write
	 * only works if the interrupts are available.
	 * The unin/i2c is controlled by the htpic on unin. But this is not
	 * the master. The openpic on mac-io is controlling the htpic.
	 * This one gets attached after the mac-io probing and then the
	 * interrupts will be available.
	 */

	if (config_intrhook_establish(&sc->enum_hook) != 0)
		return (ENOMEM);

	return (0);
}