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
 int /*<<< orphan*/  R92C_LEDCFG1 ; 
 int /*<<< orphan*/  R92C_LEDCFG1_DIS ; 
 int RTWN_LED_LINK ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
r92e_set_led(struct rtwn_softc *sc, int led, int on)
{

	if (led == RTWN_LED_LINK) {
		if (!on)
			rtwn_setbits_1(sc, R92C_LEDCFG1, 0, R92C_LEDCFG1_DIS);
		else
			rtwn_setbits_1(sc, R92C_LEDCFG1, R92C_LEDCFG1_DIS, 0);
		sc->ledlink = on;	/* Save LED state. */
	}
}