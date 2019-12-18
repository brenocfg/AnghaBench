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
struct rbled_softc {int /*<<< orphan*/  sc_led; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct rbled_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rbled_detach(device_t dev)
{
	struct rbled_softc *sc;

	sc = device_get_softc(dev);
	led_destroy(sc->sc_led);

	return (0);
}