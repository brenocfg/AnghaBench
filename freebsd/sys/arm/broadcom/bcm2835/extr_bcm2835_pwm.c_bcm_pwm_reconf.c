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
typedef  scalar_t__ uint32_t ;
struct bcm_pwm_softc {int mode; int mode2; scalar_t__ period; scalar_t__ ratio; scalar_t__ period2; scalar_t__ ratio2; scalar_t__ freq; int /*<<< orphan*/  clkman; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_PWM_CLKSRC ; 
 int EINVAL ; 
 int /*<<< orphan*/  W_CTL (struct bcm_pwm_softc*,scalar_t__) ; 
 int /*<<< orphan*/  W_DAT (struct bcm_pwm_softc*,scalar_t__) ; 
 int /*<<< orphan*/  W_DAT2 (struct bcm_pwm_softc*,scalar_t__) ; 
 int /*<<< orphan*/  W_RNG (struct bcm_pwm_softc*,scalar_t__) ; 
 int /*<<< orphan*/  W_RNG2 (struct bcm_pwm_softc*,scalar_t__) ; 
 scalar_t__ bcm2835_clkman_set_frequency (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
bcm_pwm_reconf(struct bcm_pwm_softc *sc)
{
	uint32_t u, ctlr;

	/* Disable PWM */
	W_CTL(sc, 0);

	/* Stop PWM clock */
	(void)bcm2835_clkman_set_frequency(sc->clkman, BCM_PWM_CLKSRC, 0);

	ctlr = 0; /* pre-assign zero, enable bits, write to CTL at end */

	if (sc->mode == 0 && sc->mode2 == 0) /* both modes are zero */
		return 0; /* device is now off - return */

	/* set the PWM clock frequency */
	/* TODO:  should I only do this if it changes and not stop it first? */
	u = bcm2835_clkman_set_frequency(sc->clkman, BCM_PWM_CLKSRC, sc->freq);
	if (u == 0)
		return (EINVAL);
	sc->freq = u;

	/* control register CTL bits:
	 * (from BCM2835 ARM Peripherals manual, section 9.6)
	 *
	 * 15 MSEN2  chan 2 M/S enable; 0 for PWM algo, 1 for M/S transmission
	 * 14 unused; always reads as 0
	 * 13 USEF2  chan 2 use FIFO (0 uses data; 1 uses FIFO)
	 * 12 POLA2  chan 2 invert polarity (0 normal, 1 inverted polarity)
	 * 11 SBIT2  chan 2 'Silence' bit (when not transmitting data)
	 * 10 RPTL2  chan 2 FIFO repeat last data (1 repeats, 0 interrupts)
	 *  9 MODE2  chan 2 PWM/Serializer mode (0 PWM, 1 Serializer)
	 *  8 PWEN2  chan 2 enable (0 disable, 1 enable)
	 *  7 MSEN1  chan 1 M/S enable; 0 for PWM algo, 1 for M/S transmission
	 *  6 CLRF1  chan 1 clear FIFO (set 1 to clear; always reads as 0)
	 *  5 USEF1  chan 1 use FIFO (0 uses data; 1 uses FIFO)
	 *  4 POLA1  chan 1 invert polarity (0 normal, 1 inverted polarity)
	 *  3 SBIT1  chan 1 'Silence' bit (when not transmitting data)
	 *  2 RTPL1  chan 1 FIFO repeat last data (1 repeats, 0 interrupts)
	 *  1 MODE1  chan 1 PWM/Serializer mode (0 PWM, 1 Serializer)
	 *  0 PWMEN1 chan 1 enable (0 disable, 1 enable)
	 *
	 * Notes on M/S enable:  when this bit is '1', a simple M/S ratio is used. In short,
	 * the value of 'ratio' is the number of 'on' bits, and the total length of the data is
	 * defined by 'period'.  So if 'ratio' is 2500 and 'period' is 10000, then the output
	 * remains 'on' for 2500 clocks, and goes 'off' for the remaining 7500 clocks.
	 * When the M/S enable is '0', a more complicated algorithm effectively 'dithers' the
	 * pulses in order to obtain the desired ratio.  For details, see section 9.3 of the
	 * BCM2835 ARM Peripherals manual.
	 */

	if (sc->mode != 0) {
		/* Config PWM Channel 1 */
		W_RNG(sc, sc->period);
		if (sc->ratio > sc->period)
			sc->ratio = sc->period;
		W_DAT(sc, sc->ratio);

		/* Start PWM Channel 1 */
		if (sc->mode == 1)
			ctlr |= 0x81; /* chan 1 enable + chan 1 M/S enable */
		else
			ctlr |= 0x1; /* chan 1 enable */
	}

	if (sc->mode2 != 0) {
		/* Config PWM Channel 2 */
		W_RNG2(sc, sc->period2);
		if (sc->ratio2 > sc->period2)
			sc->ratio2 = sc->period2;
		W_DAT2(sc, sc->ratio2);

		/* Start PWM Channel 2 */
		if (sc->mode2 == 1)
			ctlr |= 0x8100; /* chan 2 enable + chan 2 M/S enable */
		else
			ctlr |= 0x100;  /* chan 2 enable */
	}

	/* write CTL register with updated value */
	W_CTL(sc, ctlr);

	return (0);
}