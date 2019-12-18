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
 int R92C_LEDCFG0_DIS ; 
 int /*<<< orphan*/  R92C_LEDCFG2 ; 
 int /*<<< orphan*/  R92C_MAC_PINMUX_CFG ; 
 int RTWN_LED_LINK ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int,int) ; 

void
r88e_set_led(struct rtwn_softc *sc, int led, int on)
{

	if (led == RTWN_LED_LINK) {
		if (!on) {
			rtwn_setbits_1(sc, R92C_LEDCFG2, 0x6f,
			    R92C_LEDCFG0_DIS);
			rtwn_setbits_1(sc, R92C_MAC_PINMUX_CFG, 0x01, 0);
		} else
			rtwn_setbits_1(sc, R92C_LEDCFG2, 0x0f, 0x60);
		sc->ledlink = on;	/* Save LED state. */
	}

	/* XXX led #1? */
}