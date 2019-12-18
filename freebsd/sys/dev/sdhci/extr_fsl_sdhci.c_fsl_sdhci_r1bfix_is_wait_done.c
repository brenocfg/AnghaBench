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
struct TYPE_2__ {int /*<<< orphan*/  mtx; } ;
struct fsl_sdhci_softc {scalar_t__ r1bfix_timeout_at; scalar_t__ r1bfix_type; int /*<<< orphan*/  r1bfix_intmask; int /*<<< orphan*/  r1bfix_callout; TYPE_1__ slot; } ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ R1BFIX_NODATA ; 
 scalar_t__ R1BFIX_NONE ; 
 int RD4 (struct fsl_sdhci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBT_1MS ; 
 int /*<<< orphan*/  SDHCI_INT_DATA_END ; 
 int /*<<< orphan*/  SDHCI_INT_DATA_TIMEOUT ; 
 int /*<<< orphan*/  SDHCI_INT_RESPONSE ; 
 int SDHC_PRES_CDIHB ; 
 int SDHC_PRES_DLA ; 
 int /*<<< orphan*/  SDHC_PRES_STATE ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fsl_sdhci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_sdhci_r1bfix_func ; 
 scalar_t__ getsbinuptime () ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
fsl_sdhci_r1bfix_is_wait_done(struct fsl_sdhci_softc *sc)
{
	uint32_t inhibit;

	mtx_assert(&sc->slot.mtx, MA_OWNED);

	/*
	 * Check the DAT0 line status using both the DLA (data line active) and
	 * CDIHB (data inhibit) bits in the present state register.  In theory
	 * just DLA should do the trick,  but in practice it takes both.  If the
	 * DAT0 line is still being held and we're not yet beyond the timeout
	 * point, just schedule another callout to check again later.
	 */
	inhibit = RD4(sc, SDHC_PRES_STATE) & (SDHC_PRES_DLA | SDHC_PRES_CDIHB);

	if (inhibit && getsbinuptime() < sc->r1bfix_timeout_at) {
		callout_reset_sbt(&sc->r1bfix_callout, SBT_1MS, 0, 
		    fsl_sdhci_r1bfix_func, sc, 0);
		return (false);
	}

	/*
	 * If we reach this point with the inhibit bits still set, we've got a
	 * timeout, synthesize a DATA_TIMEOUT interrupt.  Otherwise the DAT0
	 * line has been released, and we synthesize a DATA_END, and if the type
	 * of fix needed was on a command-without-data we also now add in the
	 * original INT_RESPONSE that we suppressed earlier.
	 */
	if (inhibit)
		sc->r1bfix_intmask |= SDHCI_INT_DATA_TIMEOUT;
	else {
		sc->r1bfix_intmask |= SDHCI_INT_DATA_END;
		if (sc->r1bfix_type == R1BFIX_NODATA)
			sc->r1bfix_intmask |= SDHCI_INT_RESPONSE;
	}

	sc->r1bfix_type = R1BFIX_NONE;
	return (true);
}