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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  et_arg; int /*<<< orphan*/  (* et_event_cb ) (TYPE_1__*,int /*<<< orphan*/ ) ;scalar_t__ et_active; } ;
struct epit_softc {TYPE_1__ et; int /*<<< orphan*/  ctlreg; scalar_t__ oneshot; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPIT_CR ; 
 int /*<<< orphan*/  EPIT_SR ; 
 int EPIT_SR_OCIF ; 
 int FILTER_HANDLED ; 
 int FILTER_STRAY ; 
 int RD4 (struct epit_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (struct epit_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4B (struct epit_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
epit_intr(void *arg)
{
	struct epit_softc *sc;
	uint32_t status;

	sc = arg;

	/*
	 * Disable a one-shot timer until a new event is scheduled so that the
	 * counter doesn't wrap and fire again.  Do this before clearing the
	 * status since a short period would make it fire again really soon.
	 *
	 * Clear interrupt status before invoking event callbacks.  The callback
	 * often sets up a new one-shot timer event and if the interval is short
	 * enough it can fire before we get out of this function.  If we cleared
	 * at the bottom we'd miss the interrupt and hang until the clock wraps.
	 */
	if (sc->oneshot)
		WR4(sc, EPIT_CR, sc->ctlreg);

	status = RD4(sc, EPIT_SR);
	WR4B(sc, EPIT_SR, status);

	if ((status & EPIT_SR_OCIF) == 0)
		return (FILTER_STRAY);

	if (sc->et.et_active)
		sc->et.et_event_cb(&sc->et, sc->et.et_arg);

	return (FILTER_HANDLED);
}