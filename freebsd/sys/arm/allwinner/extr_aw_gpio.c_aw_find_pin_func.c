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
struct aw_gpio_softc {TYPE_2__* padconf; } ;
struct TYPE_4__ {TYPE_1__* pins; } ;
struct TYPE_3__ {scalar_t__* functions; } ;

/* Variables and functions */
 int AW_MAX_FUNC_BY_PIN ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static int
aw_find_pin_func(struct aw_gpio_softc *sc, int pin, const char *func)
{
	int i;

	for (i = 0; i < AW_MAX_FUNC_BY_PIN; i++)
		if (sc->padconf->pins[pin].functions[i] &&
		    !strcmp(func, sc->padconf->pins[pin].functions[i]))
			return (i);

	return (-1);
}