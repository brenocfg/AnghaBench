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
typedef  int uint16_t ;
struct fsl_sdhci_softc {int sdclockreg_freq_bits; scalar_t__ hwtype; int baseclk_hz; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ HWTYPE_ESDHC ; 
 int RD4 (struct fsl_sdhci_softc*,int /*<<< orphan*/ ) ; 
 int SDHCI_CLOCK_CARD_EN ; 
 int /*<<< orphan*/  SDHCI_CLOCK_CONTROL ; 
 int SDHCI_DIVIDERS_MASK ; 
 int SDHCI_DIVIDER_HI_MASK ; 
 int SDHCI_DIVIDER_HI_SHIFT ; 
 int SDHCI_DIVIDER_MASK ; 
 int SDHCI_DIVIDER_MASK_LEN ; 
 int SDHCI_DIVIDER_SHIFT ; 
 int SDHC_CLK_DIVISOR_MASK ; 
 int SDHC_CLK_DIVISOR_SHIFT ; 
 int SDHC_CLK_IPGEN ; 
 int SDHC_CLK_PRESCALE_MASK ; 
 int SDHC_CLK_PRESCALE_SHIFT ; 
 int SDHC_CLK_SDCLKEN ; 
 int /*<<< orphan*/  WR4 (struct fsl_sdhci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,int,int,int) ; 
 int ffs (int) ; 

__attribute__((used)) static void 
fsl_sdhc_set_clock(struct fsl_sdhci_softc *sc, uint16_t val)
{
	uint32_t divisor, freq, prescale, val32;

	val32 = RD4(sc, SDHCI_CLOCK_CONTROL);

	/*
	 * Save the frequency-setting bits in SDHCI format so that we can play
	 * them back in get_clock without complex decoding of hardware regs,
	 * then deal with the freqency part of the value based on hardware type.
	 */
	sc->sdclockreg_freq_bits = val & SDHCI_DIVIDERS_MASK;
	if (sc->hwtype == HWTYPE_ESDHC) {
		/*
		 * The i.MX5 ESDHC hardware requires the driver to manually
		 * start and stop the sd bus clock.  If the enable bit is not
		 * set, turn off the clock in hardware and we're done, otherwise
		 * decode the requested frequency.  ESDHC hardware is sdhci 2.0;
		 * the sdhci driver will use the original 8-bit divisor field
		 * and the "base / 2^N" divisor scheme.
		 */
		if ((val & SDHCI_CLOCK_CARD_EN) == 0) {
#ifdef __arm__
			/* On QorIQ, this is a reserved bit. */
			WR4(sc, SDHCI_CLOCK_CONTROL, val32 & ~SDHC_CLK_SDCLKEN);
#endif
			return;

		}
		divisor = (val >> SDHCI_DIVIDER_SHIFT) & SDHCI_DIVIDER_MASK;
		freq = sc->baseclk_hz >> ffs(divisor);
	} else {
		/*
		 * The USDHC hardware provides only "force always on" control
		 * over the sd bus clock, but no way to turn it off.  (If a cmd
		 * or data transfer is in progress the clock is on, otherwise it
		 * is off.)  If the clock is being disabled, we can just return
		 * now, otherwise we decode the requested frequency.  USDHC
		 * hardware is sdhci 3.0; the sdhci driver will use a 10-bit
		 * divisor using the "base / 2*N" divisor scheme.
		 */
		if ((val & SDHCI_CLOCK_CARD_EN) == 0)
			return;
		divisor = ((val >> SDHCI_DIVIDER_SHIFT) & SDHCI_DIVIDER_MASK) |
		    ((val >> SDHCI_DIVIDER_HI_SHIFT) & SDHCI_DIVIDER_HI_MASK) <<
		    SDHCI_DIVIDER_MASK_LEN;
		if (divisor == 0)
			freq = sc->baseclk_hz;
		else
			freq = sc->baseclk_hz / (2 * divisor);
	}

	/*
	 * Get a prescaler and final divisor to achieve the desired frequency.
	 */
	for (prescale = 2; freq < sc->baseclk_hz / (prescale * 16);)
		prescale <<= 1;

	for (divisor = 1; freq < sc->baseclk_hz / (prescale * divisor);)
		++divisor;

#ifdef DEBUG	
	device_printf(sc->dev,
	    "desired SD freq: %d, actual: %d; base %d prescale %d divisor %d\n",
	    freq, sc->baseclk_hz / (prescale * divisor), sc->baseclk_hz, 
	    prescale, divisor);
#endif	

	/*
	 * Adjust to zero-based values, and store them to the hardware.
	 */
	prescale >>= 1;
	divisor -= 1;

	val32 &= ~(SDHC_CLK_DIVISOR_MASK | SDHC_CLK_PRESCALE_MASK);
	val32 |= divisor << SDHC_CLK_DIVISOR_SHIFT;
	val32 |= prescale << SDHC_CLK_PRESCALE_SHIFT;
	val32 |= SDHC_CLK_IPGEN;
	WR4(sc, SDHCI_CLOCK_CONTROL, val32);
}