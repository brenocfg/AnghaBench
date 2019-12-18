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
struct gpio_spi_softc {int sc_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 

__attribute__((used)) static void
gpio_delay(struct gpio_spi_softc *sc)
{
	int d;

	d = sc->sc_freq / 1000000;
	if (d == 0)
		d = 1;

	DELAY(d);
}