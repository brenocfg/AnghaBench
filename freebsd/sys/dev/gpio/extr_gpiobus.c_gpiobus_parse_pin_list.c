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
struct gpiobus_softc {int /*<<< orphan*/  sc_busdev; } ;
struct gpiobus_ivar {int npins; unsigned long* pins; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 struct gpiobus_ivar* GPIOBUS_IVAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ gpiobus_acquire_child_pins (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gpiobus_alloc_ivars (struct gpiobus_ivar*) ; 
 unsigned long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gpiobus_parse_pin_list(struct gpiobus_softc *sc, device_t child,
    const char *pins)
{
	struct gpiobus_ivar *devi = GPIOBUS_IVAR(child);
	const char *p;
	char *endp;
	unsigned long pin;
	int i, npins;

	npins = 0;
	p = pins;
	for (;;) {
		pin = strtoul(p, &endp, 0);
		if (endp == p)
			break;
		npins++;
		if (*endp == '\0')
			break;
		p = endp + 1;
	}

	if (*endp != '\0') {
		device_printf(child, "garbage in the pin list: %s\n", endp);
		return (EINVAL);
	}
	if (npins == 0) {
		device_printf(child, "empty pin list\n");
		return (EINVAL);
	}

	devi->npins = npins;
	if (gpiobus_alloc_ivars(devi) != 0) {
		device_printf(child, "cannot allocate device ivars\n");
		return (EINVAL);
	}

	i = 0;
	p = pins;
	for (;;) {
		pin = strtoul(p, &endp, 0);

		devi->pins[i] = pin;

		if (*endp == '\0')
			break;
		i++;
		p = endp + 1;
	}

	if (gpiobus_acquire_child_pins(sc->sc_busdev, child) != 0)
		return (EINVAL);
	return (0);
}