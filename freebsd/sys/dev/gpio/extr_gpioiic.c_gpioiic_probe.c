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
struct gpiobus_ivar {scalar_t__ npins; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 struct gpiobus_ivar* GPIOBUS_IVAR (int /*<<< orphan*/ ) ; 
 scalar_t__ GPIOIIC_MIN_PINS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gpioiic_probe(device_t dev)
{
	struct gpiobus_ivar *devi;

#ifdef FDT
	if (!ofw_bus_status_okay(dev))
		return (ENXIO);
	if (!ofw_bus_is_compatible(dev, "gpioiic"))
		return (ENXIO);
#endif
	devi = GPIOBUS_IVAR(dev);
	if (devi->npins < GPIOIIC_MIN_PINS) {
		device_printf(dev,
		    "gpioiic needs at least %d GPIO pins (only %d given).\n",
		    GPIOIIC_MIN_PINS, devi->npins);
		return (ENXIO);
	}
	device_set_desc(dev, "GPIO I2C bit-banging driver");

	return (BUS_PROBE_DEFAULT);
}