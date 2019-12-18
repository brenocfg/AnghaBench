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
struct gpiobus_ivar {int npins; int /*<<< orphan*/ * pins; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EBUSY ; 
 struct gpiobus_ivar* GPIOBUS_IVAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIOBUS_PIN_SETNAME (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ gpiobus_acquire_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiobus_free_ivars (struct gpiobus_ivar*) ; 
 int /*<<< orphan*/  gpiobus_release_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gpiobus_acquire_child_pins(device_t dev, device_t child)
{
	struct gpiobus_ivar *devi = GPIOBUS_IVAR(child);
	int i;

	for (i = 0; i < devi->npins; i++) {
		/* Reserve the GPIO pin. */
		if (gpiobus_acquire_pin(dev, devi->pins[i]) != 0) {
			device_printf(child, "cannot acquire pin %d\n",
			    devi->pins[i]);
			while (--i >= 0) {
				(void)gpiobus_release_pin(dev,
				    devi->pins[i]);
			}
			gpiobus_free_ivars(devi);
			return (EBUSY);
		}
	}
	for (i = 0; i < devi->npins; i++) {
		/* Use the child name as pin name. */
		GPIOBUS_PIN_SETNAME(dev, devi->pins[i],
		    device_get_nameunit(child));

	}
	return (0);
}