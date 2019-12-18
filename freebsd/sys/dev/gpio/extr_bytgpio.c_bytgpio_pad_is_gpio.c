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
struct bytgpio_softc {scalar_t__* sc_pad_funcs; TYPE_1__* sc_pinpad_map; } ;
struct TYPE_2__ {scalar_t__ pad_func; } ;

/* Variables and functions */
 scalar_t__ PADCONF_FUNC_ANY ; 

__attribute__((used)) static bool
bytgpio_pad_is_gpio(struct bytgpio_softc *sc, int pin)
{
	if ((sc->sc_pinpad_map[pin].pad_func == PADCONF_FUNC_ANY) ||
	    (sc->sc_pad_funcs[pin] == sc->sc_pinpad_map[pin].pad_func))
		return (true);
	else
		return (false);
}