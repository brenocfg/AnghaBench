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
typedef  int uint16_t ;
typedef  int u_int ;
struct am335x_ehrpwm_softc {int sc_clkfreq; int sc_clktick; int sc_period; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int EPWM_READ2 (struct am335x_ehrpwm_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EPWM_TBCTL ; 
 int /*<<< orphan*/  EPWM_TBPRD ; 
 int /*<<< orphan*/  EPWM_WRITE2 (struct am335x_ehrpwm_softc*,int /*<<< orphan*/ ,int) ; 
 int NS_PER_SEC ; 
 int PWM_CLOCK ; 
 int /*<<< orphan*/  PWM_LOCK_ASSERT (struct am335x_ehrpwm_softc*) ; 
 int TBCTL_CLKDIV (int) ; 
 int TBCTL_CLKDIV_MASK ; 
 int TBCTL_HSPCLKDIV (int) ; 
 int TBCTL_HSPCLKDIV_MASK ; 
 int /*<<< orphan*/  am335x_ehrpwm_cfg_duty (struct am335x_ehrpwm_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,int,int,int,int,int) ; 
 int max (int,int) ; 

__attribute__((used)) static bool
am335x_ehrpwm_cfg_period(struct am335x_ehrpwm_softc *sc, u_int period)
{
	uint16_t regval;
	u_int clkdiv, hspclkdiv, pwmclk, pwmtick, tbprd;

	/* Can't do a period shorter than 2 clock ticks. */
	if (period < 2 * NS_PER_SEC / PWM_CLOCK) {
		sc->sc_clkfreq = 0;
		sc->sc_clktick = 0;
		sc->sc_period  = 0;
		return (false);
	}

	/*
	 * Figure out how much we have to divide down the base 100MHz clock so
	 * that we can express the requested period as a 16-bit tick count.
	 */
	tbprd = 0;
	for (clkdiv = 0; clkdiv < 8; ++clkdiv) {
		const u_int cd = 1 << clkdiv;
		for (hspclkdiv = 0; hspclkdiv < 8; ++hspclkdiv) {
			const u_int cdhs = max(1, hspclkdiv * 2);
			pwmclk = PWM_CLOCK / (cd * cdhs);
			pwmtick = NS_PER_SEC / pwmclk;
			if (period / pwmtick < 65536) {
				tbprd = period / pwmtick;
				break;
			}
		}
		if (tbprd != 0)
			break;
	}

	/* Handle requested period too long for available clock divisors. */
	if (tbprd == 0)
		return (false);

	/*
	 * If anything has changed from the current settings, reprogram the
	 * clock divisors and period register.
	 */
	if (sc->sc_clkfreq != pwmclk || sc->sc_clktick != pwmtick ||
	    sc->sc_period != tbprd * pwmtick) {

		sc->sc_clkfreq = pwmclk;
		sc->sc_clktick = pwmtick;
		sc->sc_period  = tbprd * pwmtick;
	
		PWM_LOCK_ASSERT(sc);
		regval = EPWM_READ2(sc, EPWM_TBCTL);
		regval &= ~(TBCTL_CLKDIV_MASK | TBCTL_HSPCLKDIV_MASK);
		regval |= TBCTL_CLKDIV(clkdiv) | TBCTL_HSPCLKDIV(hspclkdiv);
		EPWM_WRITE2(sc, EPWM_TBCTL, regval);
		EPWM_WRITE2(sc, EPWM_TBPRD, tbprd - 1);
#if 0
		device_printf(sc->sc_dev, "clkdiv %u hspclkdiv %u tbprd %u "
		    "clkfreq %u Hz clktick %u ns period got %u requested %u\n",
		    clkdiv, hspclkdiv, tbprd - 1,
		    sc->sc_clkfreq, sc->sc_clktick, sc->sc_period, period);
#endif
		/*
		 * If the period changed, that invalidates the current CMP
		 * registers (duty values), just zero them out.
		 */
		am335x_ehrpwm_cfg_duty(sc, 0, 0);
		am335x_ehrpwm_cfg_duty(sc, 1, 0);
	}

	return (true);
}