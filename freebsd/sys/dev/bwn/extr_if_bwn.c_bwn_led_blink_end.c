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
struct bwn_softc {scalar_t__ sc_led_blinking; } ;
struct bwn_mac {struct bwn_softc* mac_sc; } ;

/* Variables and functions */

__attribute__((used)) static void
bwn_led_blink_end(void *arg)
{
	struct bwn_mac *mac = arg;
	struct bwn_softc *sc = mac->mac_sc;

	sc->sc_led_blinking = 0;
}