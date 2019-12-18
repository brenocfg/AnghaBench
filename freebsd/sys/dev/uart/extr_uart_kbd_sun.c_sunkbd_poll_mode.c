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
struct sunkbd_softc {int /*<<< orphan*/  sc_polling; } ;
typedef  int /*<<< orphan*/  keyboard_t ;

/* Variables and functions */

__attribute__((used)) static int
sunkbd_poll_mode(keyboard_t *kbd, int on)
{
	struct sunkbd_softc *sc;

	sc = (struct sunkbd_softc *)kbd;
	if (on)
		sc->sc_polling++;
	else
		sc->sc_polling--;
	return (0);
}