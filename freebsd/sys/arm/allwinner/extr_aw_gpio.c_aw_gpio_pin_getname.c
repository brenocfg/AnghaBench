#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct aw_gpio_softc {TYPE_2__* padconf; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {size_t npins; TYPE_1__* pins; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int EINVAL ; 
 int GPIOMAXNAME ; 
 struct aw_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int
aw_gpio_pin_getname(device_t dev, uint32_t pin, char *name)
{
	struct aw_gpio_softc *sc;

	sc = device_get_softc(dev);
	if (pin >= sc->padconf->npins)
		return (EINVAL);

	snprintf(name, GPIOMAXNAME - 1, "%s",
	    sc->padconf->pins[pin].name);
	name[GPIOMAXNAME - 1] = '\0';

	return (0);
}