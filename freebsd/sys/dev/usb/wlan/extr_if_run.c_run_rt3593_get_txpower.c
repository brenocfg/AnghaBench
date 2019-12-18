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
struct run_softc {int ntxchains; int* txpow1; int* txpow2; int* txpow3; } ;
typedef  void* int8_t ;

/* Variables and functions */
 int RT2860_EEPROM_PWR2GHZ_BASE1 ; 
 int RT2860_EEPROM_PWR2GHZ_BASE2 ; 
 int RT3593_EEPROM_PWR2GHZ_BASE1 ; 
 int RT3593_EEPROM_PWR2GHZ_BASE2 ; 
 int RT3593_EEPROM_PWR2GHZ_BASE3 ; 
 int RT3593_EEPROM_PWR5GHZ_BASE1 ; 
 int RT3593_EEPROM_PWR5GHZ_BASE2 ; 
 int RT3593_EEPROM_PWR5GHZ_BASE3 ; 
 int /*<<< orphan*/  run_srom_read (struct run_softc*,int,int*) ; 

__attribute__((used)) static void
run_rt3593_get_txpower(struct run_softc *sc)
{
	uint16_t addr, val;
	int i;

	/* Read power settings for 2GHz channels. */
	for (i = 0; i < 14; i += 2) {
		addr = (sc->ntxchains == 3) ? RT3593_EEPROM_PWR2GHZ_BASE1 :
		    RT2860_EEPROM_PWR2GHZ_BASE1;
		run_srom_read(sc, addr + i / 2, &val);
		sc->txpow1[i + 0] = (int8_t)(val & 0xff);
		sc->txpow1[i + 1] = (int8_t)(val >> 8);

		addr = (sc->ntxchains == 3) ? RT3593_EEPROM_PWR2GHZ_BASE2 :
		    RT2860_EEPROM_PWR2GHZ_BASE2;
		run_srom_read(sc, addr + i / 2, &val);
		sc->txpow2[i + 0] = (int8_t)(val & 0xff);
		sc->txpow2[i + 1] = (int8_t)(val >> 8);

		if (sc->ntxchains == 3) {
			run_srom_read(sc, RT3593_EEPROM_PWR2GHZ_BASE3 + i / 2,
			    &val);
			sc->txpow3[i + 0] = (int8_t)(val & 0xff);
			sc->txpow3[i + 1] = (int8_t)(val >> 8);
		}
	}
	/* Fix broken Tx power entries. */
	for (i = 0; i < 14; i++) {
		if (sc->txpow1[i] > 31)
			sc->txpow1[i] = 5;
		if (sc->txpow2[i] > 31)
			sc->txpow2[i] = 5;
		if (sc->ntxchains == 3) {
			if (sc->txpow3[i] > 31)
				sc->txpow3[i] = 5;
		}
	}
	/* Read power settings for 5GHz channels. */
	for (i = 0; i < 40; i += 2) {
		run_srom_read(sc, RT3593_EEPROM_PWR5GHZ_BASE1 + i / 2, &val);
		sc->txpow1[i + 14] = (int8_t)(val & 0xff);
		sc->txpow1[i + 15] = (int8_t)(val >> 8);

		run_srom_read(sc, RT3593_EEPROM_PWR5GHZ_BASE2 + i / 2, &val);
		sc->txpow2[i + 14] = (int8_t)(val & 0xff);
		sc->txpow2[i + 15] = (int8_t)(val >> 8);

		if (sc->ntxchains == 3) {
			run_srom_read(sc, RT3593_EEPROM_PWR5GHZ_BASE3 + i / 2,
			    &val);
			sc->txpow3[i + 14] = (int8_t)(val & 0xff);
			sc->txpow3[i + 15] = (int8_t)(val >> 8);
		}
	}
}