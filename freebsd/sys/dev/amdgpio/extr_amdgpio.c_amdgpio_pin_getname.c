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
struct amdgpio_softc {TYPE_1__* sc_gpio_pins; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {char* gp_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int GPIOMAXNAME ; 
 int /*<<< orphan*/  amdgpio_valid_pin (struct amdgpio_softc*,size_t) ; 
 struct amdgpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,size_t,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int
amdgpio_pin_getname(device_t dev, uint32_t pin, char *name)
{
	struct amdgpio_softc *sc;

	dprintf("pin %d\n", pin);
	sc = device_get_softc(dev);

	if (!amdgpio_valid_pin(sc, pin))
		return (EINVAL);

	/* Set a very simple name */
	snprintf(name, GPIOMAXNAME, "%s", sc->sc_gpio_pins[pin].gp_name);
	name[GPIOMAXNAME - 1] = '\0';

	dprintf("pin %d name %s\n", pin, name);

	return (0);
}