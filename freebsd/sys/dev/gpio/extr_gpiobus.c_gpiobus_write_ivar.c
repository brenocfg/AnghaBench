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
typedef  int /*<<< orphan*/  uint32_t ;
struct gpiobus_ivar {uintptr_t npins; int /*<<< orphan*/ * pins; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct gpiobus_ivar* GPIOBUS_IVAR (int /*<<< orphan*/ ) ; 
#define  GPIOBUS_IVAR_NPINS 129 
#define  GPIOBUS_IVAR_PINS 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpiobus_acquire_child_pins (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiobus_alloc_ivars (struct gpiobus_ivar*) ; 

__attribute__((used)) static int
gpiobus_write_ivar(device_t dev, device_t child, int which, uintptr_t value)
{
	struct gpiobus_ivar *devi;
	const uint32_t *ptr;
	int i;

	devi = GPIOBUS_IVAR(child);
        switch (which) {
	case GPIOBUS_IVAR_NPINS:
		/* GPIO ivars are set once. */
		if (devi->npins != 0) {
			return (EBUSY);
		}
		devi->npins = value;
		if (gpiobus_alloc_ivars(devi) != 0) {
			device_printf(child, "cannot allocate device ivars\n");
			devi->npins = 0;
			return (ENOMEM);
		}
		break;
	case GPIOBUS_IVAR_PINS:
		ptr = (const uint32_t *)value;
		for (i = 0; i < devi->npins; i++)
			devi->pins[i] = ptr[i];
		if (gpiobus_acquire_child_pins(dev, child) != 0)
			return (EBUSY);
		break;
        default:
                return (ENOENT);
        }

        return (0);
}