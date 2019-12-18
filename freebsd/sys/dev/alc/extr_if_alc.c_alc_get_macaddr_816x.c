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
struct alc_softc {int /*<<< orphan*/  alc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALC_EEPROM_LD ; 
 int /*<<< orphan*/  ALC_SLD ; 
 int CSR_READ_4 (struct alc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct alc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EEPROM_LD_EEPROM_EXIST ; 
 int EEPROM_LD_FLASH_EXIST ; 
 int EEPROM_LD_PROGRESS ; 
 int EEPROM_LD_START ; 
 int SLD_PROGRESS ; 
 int SLD_START ; 
 int /*<<< orphan*/  alc_get_macaddr_par (struct alc_softc*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
alc_get_macaddr_816x(struct alc_softc *sc)
{
	uint32_t reg;
	int i, reloaded;

	reloaded = 0;
	/* Try to reload station address via TWSI. */
	for (i = 100; i > 0; i--) {
		reg = CSR_READ_4(sc, ALC_SLD);
		if ((reg & (SLD_PROGRESS | SLD_START)) == 0)
			break;
		DELAY(1000);
	}
	if (i != 0) {
		CSR_WRITE_4(sc, ALC_SLD, reg | SLD_START);
		for (i = 100; i > 0; i--) {
			DELAY(1000);
			reg = CSR_READ_4(sc, ALC_SLD);
			if ((reg & SLD_START) == 0)
				break;
		}
		if (i != 0)
			reloaded++;
		else if (bootverbose)
			device_printf(sc->alc_dev,
			    "reloading station address via TWSI timed out!\n");
	}

	/* Try to reload station address from EEPROM or FLASH. */
	if (reloaded == 0) {
		reg = CSR_READ_4(sc, ALC_EEPROM_LD);
		if ((reg & (EEPROM_LD_EEPROM_EXIST |
		    EEPROM_LD_FLASH_EXIST)) != 0) {
			for (i = 100; i > 0; i--) {
				reg = CSR_READ_4(sc, ALC_EEPROM_LD);
				if ((reg & (EEPROM_LD_PROGRESS |
				    EEPROM_LD_START)) == 0)
					break;
				DELAY(1000);
			}
			if (i != 0) {
				CSR_WRITE_4(sc, ALC_EEPROM_LD, reg |
				    EEPROM_LD_START);
				for (i = 100; i > 0; i--) {
					DELAY(1000);
					reg = CSR_READ_4(sc, ALC_EEPROM_LD);
					if ((reg & EEPROM_LD_START) == 0)
						break;
				}
			} else if (bootverbose)
				device_printf(sc->alc_dev,
				    "reloading EEPROM/FLASH timed out!\n");
		}
	}

	alc_get_macaddr_par(sc);
}