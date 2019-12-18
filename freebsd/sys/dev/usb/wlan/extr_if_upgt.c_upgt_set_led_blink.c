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
struct upgt_softc {scalar_t__ sc_led_blink; } ;

/* Variables and functions */

__attribute__((used)) static void
upgt_set_led_blink(void *arg)
{
	struct upgt_softc *sc = arg;

	/* blink finished, we are ready for a next one */
	sc->sc_led_blink = 0;
}