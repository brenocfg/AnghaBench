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
struct eventtimer {scalar_t__ et_frequency; struct am335x_dmtimer_softc* et_priv; } ;
struct am335x_dmtimer_softc {int tclr; } ;
typedef  int sbintime_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMTIMER_WRITE4 (struct am335x_dmtimer_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DMT_IRQENABLE_SET ; 
 int /*<<< orphan*/  DMT_IRQSTATUS ; 
 int DMT_IRQ_OVF ; 
 int /*<<< orphan*/  DMT_TCLR ; 
 int DMT_TCLR_AUTOLOAD ; 
 int DMT_TCLR_START ; 
 int /*<<< orphan*/  DMT_TCRR ; 
 int /*<<< orphan*/  DMT_TLDR ; 

__attribute__((used)) static int
am335x_dmtimer_et_start(struct eventtimer *et, sbintime_t first, sbintime_t period)
{
	struct am335x_dmtimer_softc *sc;
	uint32_t initial_count, reload_count;

	sc = et->et_priv;

	/*
	 * Stop the timer before changing it.  This routine will often be called
	 * while the timer is still running, to either lengthen or shorten the
	 * current event time.  We need to ensure the timer doesn't expire while
	 * we're working with it.
	 *
	 * Also clear any pending interrupt status, because it's at least
	 * theoretically possible that we're running in a primary interrupt
	 * context now, and a timer interrupt could be pending even before we
	 * stopped the timer.  The more likely case is that we're being called
	 * from the et_event_cb() routine dispatched from our own handler, but
	 * it's not clear to me that that's the only case possible.
	 */
	sc->tclr &= ~(DMT_TCLR_START | DMT_TCLR_AUTOLOAD);
	DMTIMER_WRITE4(sc, DMT_TCLR, sc->tclr);
	DMTIMER_WRITE4(sc, DMT_IRQSTATUS, DMT_IRQ_OVF);

	if (period != 0) {
		reload_count = ((uint32_t)et->et_frequency * period) >> 32;
		sc->tclr |= DMT_TCLR_AUTOLOAD;
	} else {
		reload_count = 0;
	}

	if (first != 0)
		initial_count = ((uint32_t)et->et_frequency * first) >> 32;
	else
		initial_count = reload_count;

	/*
	 * Set auto-reload and current-count values.  This timer hardware counts
	 * up from the initial/reload value and interrupts on the zero rollover.
	 */
	DMTIMER_WRITE4(sc, DMT_TLDR, 0xFFFFFFFF - reload_count);
	DMTIMER_WRITE4(sc, DMT_TCRR, 0xFFFFFFFF - initial_count);

	/* Enable overflow interrupt, and start the timer. */
	DMTIMER_WRITE4(sc, DMT_IRQENABLE_SET, DMT_IRQ_OVF);
	sc->tclr |= DMT_TCLR_START;
	DMTIMER_WRITE4(sc, DMT_TCLR, sc->tclr);

	return (0);
}