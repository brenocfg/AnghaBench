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
struct dc_softc {int /*<<< orphan*/  dc_dev; } ;

/* Variables and functions */
 int CSR_READ_4 (struct dc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct dc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DC_10BTCTRL ; 
 int /*<<< orphan*/  DC_BUSCTL ; 
 int DC_BUSCTL_RESET ; 
 int /*<<< orphan*/  DC_CLRBIT (struct dc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DC_IMR ; 
 scalar_t__ DC_IS_ADMTEK (struct dc_softc*) ; 
 scalar_t__ DC_IS_ASIX (struct dc_softc*) ; 
 scalar_t__ DC_IS_CONEXANT (struct dc_softc*) ; 
 scalar_t__ DC_IS_INTEL (struct dc_softc*) ; 
 scalar_t__ DC_IS_ULI (struct dc_softc*) ; 
 scalar_t__ DC_IS_XIRCOM (struct dc_softc*) ; 
 int /*<<< orphan*/  DC_NETCFG ; 
 int /*<<< orphan*/  DC_SETBIT (struct dc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DC_SIARESET ; 
 int DC_SIA_RESET ; 
 int DC_TIMEOUT ; 
 int /*<<< orphan*/  DC_WATCHDOG ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
dc_reset(struct dc_softc *sc)
{
	int i;

	DC_SETBIT(sc, DC_BUSCTL, DC_BUSCTL_RESET);

	for (i = 0; i < DC_TIMEOUT; i++) {
		DELAY(10);
		if (!(CSR_READ_4(sc, DC_BUSCTL) & DC_BUSCTL_RESET))
			break;
	}

	if (DC_IS_ASIX(sc) || DC_IS_ADMTEK(sc) || DC_IS_CONEXANT(sc) ||
	    DC_IS_XIRCOM(sc) || DC_IS_INTEL(sc) || DC_IS_ULI(sc)) {
		DELAY(10000);
		DC_CLRBIT(sc, DC_BUSCTL, DC_BUSCTL_RESET);
		i = 0;
	}

	if (i == DC_TIMEOUT)
		device_printf(sc->dc_dev, "reset never completed!\n");

	/* Wait a little while for the chip to get its brains in order. */
	DELAY(1000);

	CSR_WRITE_4(sc, DC_IMR, 0x00000000);
	CSR_WRITE_4(sc, DC_BUSCTL, 0x00000000);
	CSR_WRITE_4(sc, DC_NETCFG, 0x00000000);

	/*
	 * Bring the SIA out of reset. In some cases, it looks
	 * like failing to unreset the SIA soon enough gets it
	 * into a state where it will never come out of reset
	 * until we reset the whole chip again.
	 */
	if (DC_IS_INTEL(sc)) {
		DC_SETBIT(sc, DC_SIARESET, DC_SIA_RESET);
		CSR_WRITE_4(sc, DC_10BTCTRL, 0xFFFFFFFF);
		CSR_WRITE_4(sc, DC_WATCHDOG, 0);
	}
}