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
struct gpiobus_ivar {uintptr_t npins; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 int ENOTSUP ; 
 struct gpiobus_ivar* GPIOBUS_IVAR (int /*<<< orphan*/ ) ; 
#define  GPIOBUS_IVAR_NPINS 129 
#define  GPIOBUS_IVAR_PINS 128 

__attribute__((used)) static int
gpiobus_read_ivar(device_t dev, device_t child, int which, uintptr_t *result)
{
	struct gpiobus_ivar *devi;

	devi = GPIOBUS_IVAR(child);
        switch (which) {
	case GPIOBUS_IVAR_NPINS:
		*result = devi->npins;
		break;
	case GPIOBUS_IVAR_PINS:
		/* Children do not ever need to directly examine this. */
		return (ENOTSUP);
        default:
                return (ENOENT);
        }

	return (0);
}