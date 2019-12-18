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
struct psm_softc {int /*<<< orphan*/  callout; scalar_t__ watchdog; int /*<<< orphan*/  kbdc; int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VLOG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct psm_softc*) ; 
 int /*<<< orphan*/  hz ; 
 scalar_t__ kbdc_lock (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  psmintr (struct psm_softc*) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static void
psmtimeout(void *arg)
{
	struct psm_softc *sc;
	int s;

	sc = (struct psm_softc *)arg;
	s = spltty();
	if (sc->watchdog && kbdc_lock(sc->kbdc, TRUE)) {
		VLOG(6, (LOG_DEBUG, "psm%d: lost interrupt?\n", sc->unit));
		psmintr(sc);
		kbdc_lock(sc->kbdc, FALSE);
	}
	sc->watchdog = TRUE;
	splx(s);
	callout_reset(&sc->callout, hz, psmtimeout, sc);
}