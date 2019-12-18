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
struct ath_softc {TYPE_1__* sc_hwmap; scalar_t__ sc_blinking; int /*<<< orphan*/  sc_ledevent; } ;
struct TYPE_2__ {int /*<<< orphan*/  ledoff; int /*<<< orphan*/  ledon; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath_led_blink (struct ath_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ticks ; 

void
ath_led_event(struct ath_softc *sc, int rix)
{
	sc->sc_ledevent = ticks;	/* time of last event */
	if (sc->sc_blinking)		/* don't interrupt active blink */
		return;
	ath_led_blink(sc, sc->sc_hwmap[rix].ledon, sc->sc_hwmap[rix].ledoff);
}