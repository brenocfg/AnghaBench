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
typedef  size_t uint32_t ;
struct gpiobus_softc {size_t sc_npins; TYPE_1__* sc_pins; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int EINVAL ; 
 struct gpiobus_softc* GPIOBUS_SOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIOMAXNAME ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gpiobus_pin_setname(device_t dev, uint32_t pin, const char *name)
{
	struct gpiobus_softc *sc;

	sc = GPIOBUS_SOFTC(dev);
	if (pin > sc->sc_npins)
		return (EINVAL);
	if (name == NULL)
		return (EINVAL);
	/* Save the pin name. */
	if (sc->sc_pins[pin].name == NULL)
		sc->sc_pins[pin].name = malloc(GPIOMAXNAME, M_DEVBUF,
		    M_WAITOK | M_ZERO);
	strlcpy(sc->sc_pins[pin].name, name, GPIOMAXNAME);

	return (0);
}