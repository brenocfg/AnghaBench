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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_enumerate_hinted_children (int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int gpiobus_init_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gpiobus_attach(device_t dev)
{
	int err;

	err = gpiobus_init_softc(dev);
	if (err != 0)
		return (err);

	/*
	 * Get parent's pins and mark them as unmapped
	 */
	bus_generic_probe(dev);
	bus_enumerate_hinted_children(dev);

	return (bus_generic_attach(dev));
}