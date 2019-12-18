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
struct dc_softc {int dummy; } ;

/* Variables and functions */
 int CSR_READ_4 (struct dc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct dc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_CLRBIT (struct dc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_SETBIT (struct dc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_SIO ; 
 int /*<<< orphan*/  DC_SIO_EESEL ; 
 int /*<<< orphan*/  DC_SIO_EE_CLK ; 
 int /*<<< orphan*/  DC_SIO_EE_CS ; 
 int DC_SIO_EE_DATAOUT ; 
 int /*<<< orphan*/  DC_SIO_ROMCTL_READ ; 
 int /*<<< orphan*/  SIO_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIO_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_delay (struct dc_softc*) ; 
 int /*<<< orphan*/  dc_eeprom_idle (struct dc_softc*) ; 
 int /*<<< orphan*/  dc_eeprom_putbyte (struct dc_softc*,int) ; 

__attribute__((used)) static void
dc_eeprom_getword(struct dc_softc *sc, int addr, uint16_t *dest)
{
	int i;
	uint16_t word = 0;

	/* Force EEPROM to idle state. */
	dc_eeprom_idle(sc);

	/* Enter EEPROM access mode. */
	CSR_WRITE_4(sc, DC_SIO, DC_SIO_EESEL);
	dc_delay(sc);
	DC_SETBIT(sc, DC_SIO,  DC_SIO_ROMCTL_READ);
	dc_delay(sc);
	DC_CLRBIT(sc, DC_SIO, DC_SIO_EE_CLK);
	dc_delay(sc);
	DC_SETBIT(sc, DC_SIO, DC_SIO_EE_CS);
	dc_delay(sc);

	/*
	 * Send address of word we want to read.
	 */
	dc_eeprom_putbyte(sc, addr);

	/*
	 * Start reading bits from EEPROM.
	 */
	for (i = 0x8000; i; i >>= 1) {
		SIO_SET(DC_SIO_EE_CLK);
		dc_delay(sc);
		if (CSR_READ_4(sc, DC_SIO) & DC_SIO_EE_DATAOUT)
			word |= i;
		dc_delay(sc);
		SIO_CLR(DC_SIO_EE_CLK);
		dc_delay(sc);
	}

	/* Turn off EEPROM access mode. */
	dc_eeprom_idle(sc);

	*dest = word;
}