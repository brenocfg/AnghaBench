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
typedef  int uint32_t ;
struct eventtimer {scalar_t__ et_frequency; scalar_t__ et_priv; } ;
struct epit_softc {int ctlreg; int oneshot; } ;
typedef  int sbintime_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EPIT_CR ; 
 int EPIT_CR_EN ; 
 int /*<<< orphan*/  EPIT_LR ; 
 int /*<<< orphan*/  EPIT_SR ; 
 int EPIT_SR_OCIF ; 
 int /*<<< orphan*/  WR4 (struct epit_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WR4B (struct epit_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
epit_et_start(struct eventtimer *et, sbintime_t first, sbintime_t period)
{
	struct epit_softc *sc;
	uint32_t ticks;

	sc = (struct epit_softc *)et->et_priv;

	/*
	 * Disable the timer and clear any pending status.  The timer may be
	 * running or may have just expired if we're called to reschedule the
	 * next event before the previous event time arrives.
	 */
	WR4(sc, EPIT_CR, sc->ctlreg);
	WR4(sc, EPIT_SR, EPIT_SR_OCIF);
	if (period != 0) {
		sc->oneshot = false;
		ticks = ((uint32_t)et->et_frequency * period) >> 32;
	} else if (first != 0) {
		sc->oneshot = true;
		ticks = ((uint32_t)et->et_frequency * first) >> 32;
	} else {
		return (EINVAL);
	}

	/* Set the countdown load register and start the timer. */
	WR4(sc, EPIT_LR, ticks);
	WR4B(sc, EPIT_CR, sc->ctlreg | EPIT_CR_EN);

	return (0);
}