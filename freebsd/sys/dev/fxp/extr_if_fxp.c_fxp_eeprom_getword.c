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
struct fxp_softc {int eeprom_size; } ;

/* Variables and functions */
 int CSR_READ_2 (struct fxp_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct fxp_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  FXP_CSR_EEPROMCONTROL ; 
 int FXP_EEPROM_EECS ; 
 int FXP_EEPROM_EEDI ; 
 int FXP_EEPROM_EEDO ; 
 int FXP_EEPROM_EESK ; 
 int /*<<< orphan*/  FXP_EEPROM_OPC_READ ; 
 int /*<<< orphan*/  fxp_eeprom_shiftin (struct fxp_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint16_t
fxp_eeprom_getword(struct fxp_softc *sc, int offset, int autosize)
{
	uint16_t reg, data;
	int x;

	CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, FXP_EEPROM_EECS);
	/*
	 * Shift in read opcode.
	 */
	fxp_eeprom_shiftin(sc, FXP_EEPROM_OPC_READ, 3);
	/*
	 * Shift in address.
	 */
	data = 0;
	for (x = 1 << (sc->eeprom_size - 1); x; x >>= 1) {
		if (offset & x)
			reg = FXP_EEPROM_EECS | FXP_EEPROM_EEDI;
		else
			reg = FXP_EEPROM_EECS;
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, reg);
		DELAY(1);
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, reg | FXP_EEPROM_EESK);
		DELAY(1);
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, reg);
		DELAY(1);
		reg = CSR_READ_2(sc, FXP_CSR_EEPROMCONTROL) & FXP_EEPROM_EEDO;
		data++;
		if (autosize && reg == 0) {
			sc->eeprom_size = data;
			break;
		}
	}
	/*
	 * Shift out data.
	 */
	data = 0;
	reg = FXP_EEPROM_EECS;
	for (x = 1 << 15; x; x >>= 1) {
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, reg | FXP_EEPROM_EESK);
		DELAY(1);
		if (CSR_READ_2(sc, FXP_CSR_EEPROMCONTROL) & FXP_EEPROM_EEDO)
			data |= x;
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, reg);
		DELAY(1);
	}
	CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, 0);
	DELAY(1);

	return (data);
}