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
struct auxio_softc {int /*<<< orphan*/  sc_led_stat; int /*<<< orphan*/  sc_led_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  auxio_free_resource (struct auxio_softc*) ; 
 int /*<<< orphan*/  auxio_led_func (struct auxio_softc*,int /*<<< orphan*/ ) ; 
 struct auxio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
auxio_bus_detach(device_t dev)
{
	struct auxio_softc *sc;

	sc = device_get_softc(dev);
	led_destroy(sc->sc_led_dev);
	auxio_led_func(sc, sc->sc_led_stat);
	auxio_free_resource(sc);

	return (0);
}