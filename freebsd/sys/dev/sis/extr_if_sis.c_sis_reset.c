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
struct sis_softc {scalar_t__ sis_type; int /*<<< orphan*/  sis_dev; } ;

/* Variables and functions */
 int CSR_READ_4 (struct sis_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct sis_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  NS_CLKRUN ; 
 int /*<<< orphan*/  NS_CLKRUN_PMESTS ; 
 int /*<<< orphan*/  SIS_CSR ; 
 int SIS_CSR_RESET ; 
 int /*<<< orphan*/  SIS_PWRMAN_CTL ; 
 int /*<<< orphan*/  SIS_SETBIT (struct sis_softc*,int /*<<< orphan*/ ,int) ; 
 int SIS_TIMEOUT ; 
 scalar_t__ SIS_TYPE_83815 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
sis_reset(struct sis_softc *sc)
{
	int		i;

	SIS_SETBIT(sc, SIS_CSR, SIS_CSR_RESET);

	for (i = 0; i < SIS_TIMEOUT; i++) {
		if (!(CSR_READ_4(sc, SIS_CSR) & SIS_CSR_RESET))
			break;
	}

	if (i == SIS_TIMEOUT)
		device_printf(sc->sis_dev, "reset never completed\n");

	/* Wait a little while for the chip to get its brains in order. */
	DELAY(1000);

	/*
	 * If this is a NetSemi chip, make sure to clear
	 * PME mode.
	 */
	if (sc->sis_type == SIS_TYPE_83815) {
		CSR_WRITE_4(sc, NS_CLKRUN, NS_CLKRUN_PMESTS);
		CSR_WRITE_4(sc, NS_CLKRUN, 0);
	} else {
		/* Disable WOL functions. */
		CSR_WRITE_4(sc, SIS_PWRMAN_CTL, 0);
	}
}