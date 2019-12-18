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
struct rtwn_softc {int ledlink; } ;

/* Variables and functions */
 int R12A_LEDCFG2_ENA ; 
 int /*<<< orphan*/  R92C_LEDCFG0 ; 
 int R92C_LEDCFG0_DIS ; 
 int RTWN_LED_LINK ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int,int) ; 

void
r12a_set_led(struct rtwn_softc *sc, int led, int on)
{
	/* XXX assume led #0 == LED_LINK */
	/* XXX antenna diversity */

	if (led == RTWN_LED_LINK) {
		rtwn_setbits_1(sc, R92C_LEDCFG0, 0x8f,
		    R12A_LEDCFG2_ENA | (on ? 0 : R92C_LEDCFG0_DIS));
		sc->ledlink = on;	/* Save LED state. */
	}

	/* XXX leds #1/#2 ? */
}