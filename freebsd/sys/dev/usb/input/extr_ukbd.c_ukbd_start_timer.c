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
struct TYPE_2__ {int kb_delay2; } ;
struct ukbd_softc {int sc_delay; scalar_t__ sc_co_basetime; int /*<<< orphan*/  sc_callout; TYPE_1__ sc_kbd; } ;
typedef  scalar_t__ sbintime_t ;

/* Variables and functions */
 int /*<<< orphan*/  C_ABSOLUTE ; 
 int SBT_1MS ; 
 scalar_t__ qmin (scalar_t__,int) ; 
 scalar_t__ sbinuptime () ; 
 int /*<<< orphan*/  ukbd_timeout ; 
 int /*<<< orphan*/  usb_callout_reset_sbt (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct ukbd_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ukbd_start_timer(struct ukbd_softc *sc)
{
	sbintime_t delay, now, prec;

	now = sbinuptime();

	/* check if initial delay passed and fallback to key repeat delay */
	if (sc->sc_delay == 0)
		sc->sc_delay = sc->sc_kbd.kb_delay2;

	/* compute timeout */
	delay = SBT_1MS * sc->sc_delay;
	sc->sc_co_basetime += delay;

	/* check if we are running behind */
	if (sc->sc_co_basetime < now)
		sc->sc_co_basetime = now;

	/* This is rarely called, so prefer precision to efficiency. */
	prec = qmin(delay >> 7, SBT_1MS * 10);
	usb_callout_reset_sbt(&sc->sc_callout, sc->sc_co_basetime, prec,
	    ukbd_timeout, sc, C_ABSOLUTE);
}