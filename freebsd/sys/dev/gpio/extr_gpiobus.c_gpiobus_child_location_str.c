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
struct gpiobus_ivar {int npins; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct gpiobus_ivar* GPIOBUS_IVAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiobus_print_pins (struct gpiobus_ivar*,char*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static int
gpiobus_child_location_str(device_t bus, device_t child, char *buf,
    size_t buflen)
{
	struct gpiobus_ivar *devi;

	devi = GPIOBUS_IVAR(child);
	if (devi->npins > 1)
		strlcpy(buf, "pins=", buflen);
	else
		strlcpy(buf, "pin=", buflen);
	gpiobus_print_pins(devi, buf, buflen);

	return (0);
}