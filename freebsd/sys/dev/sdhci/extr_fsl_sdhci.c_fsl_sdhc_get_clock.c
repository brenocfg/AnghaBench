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
typedef  int /*<<< orphan*/  uint16_t ;
struct fsl_sdhci_softc {scalar_t__ hwtype; int /*<<< orphan*/  sdclockreg_freq_bits; } ;

/* Variables and functions */
 scalar_t__ HWTYPE_ESDHC ; 
 int RD4 (struct fsl_sdhci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDHCI_CLOCK_CARD_EN ; 
 int /*<<< orphan*/  SDHCI_CLOCK_INT_EN ; 
 int /*<<< orphan*/  SDHCI_CLOCK_INT_STABLE ; 
 int SDHC_CLK_SDCLKEN ; 
 int SDHC_PRES_SDSTB ; 
 int /*<<< orphan*/  SDHC_PRES_STATE ; 
 int /*<<< orphan*/  SDHC_SYS_CTRL ; 

__attribute__((used)) static uint16_t
fsl_sdhc_get_clock(struct fsl_sdhci_softc *sc)
{
	uint16_t val;

	/*
	 * Whenever the sdhci driver writes the clock register we save a
	 * snapshot of just the frequency bits, so that we can play them back
	 * here on a register read without recalculating the frequency from the
	 * prescalar and divisor bits in the real register.  We'll start with
	 * those bits, and mix in the clock status and enable bits that come
	 * from different places depending on which hardware we've got.
	 */
	val = sc->sdclockreg_freq_bits;

	/*
	 * The internal clock is always enabled (actually, the hardware manages
	 * it).  Whether the internal clock is stable yet after a frequency
	 * change comes from the present-state register on both hardware types.
	 */
	val |= SDHCI_CLOCK_INT_EN;
	if (RD4(sc, SDHC_PRES_STATE) & SDHC_PRES_SDSTB)
	    val |= SDHCI_CLOCK_INT_STABLE;

	/*
	 * On i.MX ESDHC hardware the card bus clock enable is in the usual
	 * sdhci register but it's a different bit, so transcribe it (note the
	 * difference between standard SDHCI_ and Freescale SDHC_ prefixes
	 * here). On USDHC and QorIQ ESDHC hardware there is a force-on bit, but
	 * no force-off for the card bus clock (the hardware runs the clock when
	 * transfers are active no matter what), so we always say the clock is
	 * on.
	 * XXX Maybe we should say it's in whatever state the sdhci driver last
	 * set it to.
	 */
	if (sc->hwtype == HWTYPE_ESDHC) {
#ifdef __arm__
		if (RD4(sc, SDHC_SYS_CTRL) & SDHC_CLK_SDCLKEN)
#endif
			val |= SDHCI_CLOCK_CARD_EN;
	} else {
		val |= SDHCI_CLOCK_CARD_EN;
	}

	return (val);
}