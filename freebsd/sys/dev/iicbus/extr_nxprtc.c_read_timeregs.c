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
typedef  scalar_t__ uint8_t ;
struct time_regs {scalar_t__ sec; } ;
struct nxprtc_softc {scalar_t__ use_timer; int /*<<< orphan*/  secaddr; int /*<<< orphan*/  dev; int /*<<< orphan*/  tmcaddr; } ;

/* Variables and functions */
 scalar_t__ TMR_TICKS_HALFSEC ; 
 scalar_t__ TMR_TICKS_SEC ; 
 int /*<<< orphan*/  WAITFLAGS ; 
 int nxprtc_readfrom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct time_regs*,int,int /*<<< orphan*/ ) ; 
 int read_reg (struct nxprtc_softc*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int
read_timeregs(struct nxprtc_softc *sc, struct time_regs *tregs, uint8_t *tmr)
{
	int err;
	uint8_t sec, tmr1, tmr2;

	/*
	 * The datasheet says loop to read the same timer value twice because it
	 * does not freeze while reading.  To that we add our own logic that
	 * the seconds register must be the same before and after reading the
	 * timer, ensuring the fractional part is from the same second as tregs.
	 */
	do {
		if (sc->use_timer) {
			if ((err = read_reg(sc, sc->secaddr, &sec)) != 0)
				break;
			if ((err = read_reg(sc, sc->tmcaddr, &tmr1)) != 0)
				break;
			if ((err = read_reg(sc, sc->tmcaddr, &tmr2)) != 0)
				break;
			if (tmr1 != tmr2)
				continue;
		}
		if ((err = nxprtc_readfrom(sc->dev, sc->secaddr, tregs,
		    sizeof(*tregs), WAITFLAGS)) != 0)
			break;
	} while (sc->use_timer && tregs->sec != sec);

	/*
	 * If the timer value is greater than our hz rate (or is zero),
	 * something is wrong.  Maybe some other OS used the timer differently?
	 * Just set it to zero.  Likewise if we're not using the timer.  After
	 * the offset calc below, the zero turns into 32, the mid-second point,
	 * which in effect performs 4/5 rounding, which is just the right thing
	 * to do if we don't have fine-grained time.
	 */
	if (!sc->use_timer || tmr1 > TMR_TICKS_SEC)
		tmr1 = 0;

	/*
	 * Turn the downcounter into an upcounter.  The timer starts counting at
	 * and rolls over at mid-second, so add half a second worth of ticks to
	 * get its zero point back in sync with the tregs.sec rollover.
	 */
	*tmr = (TMR_TICKS_SEC - tmr1 + TMR_TICKS_HALFSEC) % TMR_TICKS_SEC;

	return (err);
}