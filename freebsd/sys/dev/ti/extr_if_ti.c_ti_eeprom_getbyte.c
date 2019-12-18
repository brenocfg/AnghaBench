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
typedef  int uint8_t ;
struct ti_softc {int /*<<< orphan*/  ti_dev; } ;

/* Variables and functions */
 int CSR_READ_4 (struct ti_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EEPROM_CTL_READ ; 
 int EEPROM_CTL_WRITE ; 
 int /*<<< orphan*/  EEPROM_START ; 
 int /*<<< orphan*/  EEPROM_STOP ; 
 int /*<<< orphan*/  TI_CLRBIT (struct ti_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_MISC_LOCAL_CTL ; 
 int /*<<< orphan*/  TI_MLC_EE_CLK ; 
 int TI_MLC_EE_DIN ; 
 int /*<<< orphan*/  TI_MLC_EE_TXEN ; 
 int /*<<< orphan*/  TI_SETBIT (struct ti_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ti_eeprom_putbyte (struct ti_softc*,int) ; 

__attribute__((used)) static uint8_t
ti_eeprom_getbyte(struct ti_softc *sc, int addr, uint8_t *dest)
{
	int i;
	uint8_t byte = 0;

	EEPROM_START;

	/*
	 * Send write control code to EEPROM.
	 */
	if (ti_eeprom_putbyte(sc, EEPROM_CTL_WRITE)) {
		device_printf(sc->ti_dev,
		    "failed to send write command, status: %x\n",
		    CSR_READ_4(sc, TI_MISC_LOCAL_CTL));
		return (1);
	}

	/*
	 * Send first byte of address of byte we want to read.
	 */
	if (ti_eeprom_putbyte(sc, (addr >> 8) & 0xFF)) {
		device_printf(sc->ti_dev, "failed to send address, status: %x\n",
		    CSR_READ_4(sc, TI_MISC_LOCAL_CTL));
		return (1);
	}
	/*
	 * Send second byte address of byte we want to read.
	 */
	if (ti_eeprom_putbyte(sc, addr & 0xFF)) {
		device_printf(sc->ti_dev, "failed to send address, status: %x\n",
		    CSR_READ_4(sc, TI_MISC_LOCAL_CTL));
		return (1);
	}

	EEPROM_STOP;
	EEPROM_START;
	/*
	 * Send read control code to EEPROM.
	 */
	if (ti_eeprom_putbyte(sc, EEPROM_CTL_READ)) {
		device_printf(sc->ti_dev,
		    "failed to send read command, status: %x\n",
		    CSR_READ_4(sc, TI_MISC_LOCAL_CTL));
		return (1);
	}

	/*
	 * Start reading bits from EEPROM.
	 */
	TI_CLRBIT(sc, TI_MISC_LOCAL_CTL, TI_MLC_EE_TXEN);
	for (i = 0x80; i; i >>= 1) {
		TI_SETBIT(sc, TI_MISC_LOCAL_CTL, TI_MLC_EE_CLK);
		DELAY(1);
		if (CSR_READ_4(sc, TI_MISC_LOCAL_CTL) & TI_MLC_EE_DIN)
			byte |= i;
		TI_CLRBIT(sc, TI_MISC_LOCAL_CTL, TI_MLC_EE_CLK);
		DELAY(1);
	}

	EEPROM_STOP;

	/*
	 * No ACK generated for read, so just return byte.
	 */

	*dest = byte;

	return (0);
}