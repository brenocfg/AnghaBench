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
struct gpioleds_softc {int sc_total_leds; int /*<<< orphan*/ * sc_leds; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 struct gpioleds_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpioleds_detach_led (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gpioled_detach(device_t dev)
{
	struct gpioleds_softc *sc;
	int i;

	sc = device_get_softc(dev);

	for (i = 0; i < sc->sc_total_leds; i++)
		gpioleds_detach_led(&sc->sc_leds[i]);

	if (sc->sc_leds)
		free(sc->sc_leds, M_DEVBUF);

	return (0);
}