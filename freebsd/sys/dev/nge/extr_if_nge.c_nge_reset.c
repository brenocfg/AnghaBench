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
struct nge_softc {int /*<<< orphan*/  nge_dev; } ;

/* Variables and functions */
 int CSR_READ_4 (struct nge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct nge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  NGE_CFG ; 
 int NGE_CFG_64BIT_ADDR_ENB ; 
 int NGE_CFG_64BIT_DATA_ENB ; 
 int /*<<< orphan*/  NGE_CLKRUN ; 
 int NGE_CLKRUN_PMESTS ; 
 int /*<<< orphan*/  NGE_CSR ; 
 int NGE_CSR_RESET ; 
 int /*<<< orphan*/  NGE_SETBIT (struct nge_softc*,int /*<<< orphan*/ ,int) ; 
 int NGE_TIMEOUT ; 
 int /*<<< orphan*/  NGE_WOLCSR ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
nge_reset(struct nge_softc *sc)
{
	uint32_t v;
	int i;

	NGE_SETBIT(sc, NGE_CSR, NGE_CSR_RESET);

	for (i = 0; i < NGE_TIMEOUT; i++) {
		if (!(CSR_READ_4(sc, NGE_CSR) & NGE_CSR_RESET))
			break;
		DELAY(1);
	}

	if (i == NGE_TIMEOUT)
		device_printf(sc->nge_dev, "reset never completed\n");

	/* Wait a little while for the chip to get its brains in order. */
	DELAY(1000);

	/*
	 * If this is a NetSemi chip, make sure to clear
	 * PME mode.
	 */
	CSR_WRITE_4(sc, NGE_CLKRUN, NGE_CLKRUN_PMESTS);
	CSR_WRITE_4(sc, NGE_CLKRUN, 0);

	/* Clear WOL events which may interfere normal Rx filter opertaion. */
	CSR_WRITE_4(sc, NGE_WOLCSR, 0);

	/*
	 * Only DP83820 supports 64bits addressing/data transfers and
	 * 64bit addressing requires different descriptor structures.
	 * To make it simple, disable 64bit addressing/data transfers.
	 */
	v = CSR_READ_4(sc, NGE_CFG);
	v &= ~(NGE_CFG_64BIT_ADDR_ENB | NGE_CFG_64BIT_DATA_ENB);
	CSR_WRITE_4(sc, NGE_CFG, v);
}