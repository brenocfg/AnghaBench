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
struct gpioled_softc {int /*<<< orphan*/ * sc_leddev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOLED_LOCK_DESTROY (struct gpioled_softc*) ; 
 struct gpioled_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gpioled_detach(device_t dev)
{
	struct gpioled_softc *sc;

	sc = device_get_softc(dev);
	if (sc->sc_leddev) {
		led_destroy(sc->sc_leddev);
		sc->sc_leddev = NULL;
	}
	GPIOLED_LOCK_DESTROY(sc);
	return (0);
}