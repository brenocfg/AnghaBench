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
struct am335x_ehrpwm_softc {size_t sc_pwm_clkdiv; int sc_pwm_freq; int sc_pwm_period; } ;

/* Variables and functions */
 int PWM_CLOCK ; 
 int* am335x_ehrpwm_clkdiv ; 

__attribute__((used)) static void
am335x_ehrpwm_freq(struct am335x_ehrpwm_softc *sc)
{
	int clkdiv;

	clkdiv = am335x_ehrpwm_clkdiv[sc->sc_pwm_clkdiv];
	sc->sc_pwm_freq = PWM_CLOCK / (1 * clkdiv) / sc->sc_pwm_period;
}