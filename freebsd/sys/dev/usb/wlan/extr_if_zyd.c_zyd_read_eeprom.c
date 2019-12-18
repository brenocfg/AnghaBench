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
struct zyd_softc {int* sc_pwrcal; int* sc_pwrint; int* sc_ofdm36_cal; int* sc_ofdm48_cal; int* sc_ofdm54_cal; } ;

/* Variables and functions */
 scalar_t__ ZYD_EEPROM_36M_CAL ; 
 scalar_t__ ZYD_EEPROM_48M_CAL ; 
 scalar_t__ ZYD_EEPROM_54M_CAL ; 
 scalar_t__ ZYD_EEPROM_PWR_CAL ; 
 scalar_t__ ZYD_EEPROM_PWR_INT ; 
 int /*<<< orphan*/  zyd_read16_m (struct zyd_softc*,scalar_t__,int*) ; 

__attribute__((used)) static int
zyd_read_eeprom(struct zyd_softc *sc)
{
	uint16_t val;
	int error, i;

	/* read Tx power calibration tables */
	for (i = 0; i < 7; i++) {
		zyd_read16_m(sc, ZYD_EEPROM_PWR_CAL + i, &val);
		sc->sc_pwrcal[i * 2] = val >> 8;
		sc->sc_pwrcal[i * 2 + 1] = val & 0xff;
		zyd_read16_m(sc, ZYD_EEPROM_PWR_INT + i, &val);
		sc->sc_pwrint[i * 2] = val >> 8;
		sc->sc_pwrint[i * 2 + 1] = val & 0xff;
		zyd_read16_m(sc, ZYD_EEPROM_36M_CAL + i, &val);
		sc->sc_ofdm36_cal[i * 2] = val >> 8;
		sc->sc_ofdm36_cal[i * 2 + 1] = val & 0xff;
		zyd_read16_m(sc, ZYD_EEPROM_48M_CAL + i, &val);
		sc->sc_ofdm48_cal[i * 2] = val >> 8;
		sc->sc_ofdm48_cal[i * 2 + 1] = val & 0xff;
		zyd_read16_m(sc, ZYD_EEPROM_54M_CAL + i, &val);
		sc->sc_ofdm54_cal[i * 2] = val >> 8;
		sc->sc_ofdm54_cal[i * 2 + 1] = val & 0xff;
	}
fail:
	return (error);
}