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
typedef  int uint16_t ;
struct run_softc {int* txpow1; int mac_ver; int* txpow2; } ;
typedef  void* int8_t ;
struct TYPE_2__ {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 scalar_t__ RT2860_EEPROM_PWR2GHZ_BASE1 ; 
 scalar_t__ RT2860_EEPROM_PWR2GHZ_BASE2 ; 
 scalar_t__ RT2860_EEPROM_PWR5GHZ_BASE1 ; 
 scalar_t__ RT2860_EEPROM_PWR5GHZ_BASE2 ; 
 int /*<<< orphan*/  RUN_DEBUG_TXPWR ; 
 int /*<<< orphan*/  RUN_DPRINTF (struct run_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* rt2860_rf2850 ; 
 int /*<<< orphan*/  run_srom_read (struct run_softc*,scalar_t__,int*) ; 

__attribute__((used)) static void
run_get_txpower(struct run_softc *sc)
{
	uint16_t val;
	int i;

	/* Read power settings for 2GHz channels. */
	for (i = 0; i < 14; i += 2) {
		run_srom_read(sc, RT2860_EEPROM_PWR2GHZ_BASE1 + i / 2, &val);
		sc->txpow1[i + 0] = (int8_t)(val & 0xff);
		sc->txpow1[i + 1] = (int8_t)(val >> 8);

		if (sc->mac_ver != 0x5390) {
			run_srom_read(sc,
			    RT2860_EEPROM_PWR2GHZ_BASE2 + i / 2, &val);
			sc->txpow2[i + 0] = (int8_t)(val & 0xff);
			sc->txpow2[i + 1] = (int8_t)(val >> 8);
		}
	}
	/* Fix broken Tx power entries. */
	for (i = 0; i < 14; i++) {
		if (sc->mac_ver >= 0x5390) {
			if (sc->txpow1[i] < 0 || sc->txpow1[i] > 39)
				sc->txpow1[i] = 5;
		} else {
			if (sc->txpow1[i] < 0 || sc->txpow1[i] > 31)
				sc->txpow1[i] = 5;
		}
		if (sc->mac_ver > 0x5390) {
			if (sc->txpow2[i] < 0 || sc->txpow2[i] > 39)
				sc->txpow2[i] = 5;
		} else if (sc->mac_ver < 0x5390) {
			if (sc->txpow2[i] < 0 || sc->txpow2[i] > 31)
				sc->txpow2[i] = 5;
		}
		RUN_DPRINTF(sc, RUN_DEBUG_TXPWR,
		    "chan %d: power1=%d, power2=%d\n",
		    rt2860_rf2850[i].chan, sc->txpow1[i], sc->txpow2[i]);
	}
	/* Read power settings for 5GHz channels. */
	for (i = 0; i < 40; i += 2) {
		run_srom_read(sc, RT2860_EEPROM_PWR5GHZ_BASE1 + i / 2, &val);
		sc->txpow1[i + 14] = (int8_t)(val & 0xff);
		sc->txpow1[i + 15] = (int8_t)(val >> 8);

		run_srom_read(sc, RT2860_EEPROM_PWR5GHZ_BASE2 + i / 2, &val);
		sc->txpow2[i + 14] = (int8_t)(val & 0xff);
		sc->txpow2[i + 15] = (int8_t)(val >> 8);
	}
	/* Fix broken Tx power entries. */
	for (i = 0; i < 40; i++ ) {
		if (sc->mac_ver != 0x5592) {
			if (sc->txpow1[14 + i] < -7 || sc->txpow1[14 + i] > 15)
				sc->txpow1[14 + i] = 5;
			if (sc->txpow2[14 + i] < -7 || sc->txpow2[14 + i] > 15)
				sc->txpow2[14 + i] = 5;
		}
		RUN_DPRINTF(sc, RUN_DEBUG_TXPWR,
		    "chan %d: power1=%d, power2=%d\n",
		    rt2860_rf2850[14 + i].chan, sc->txpow1[14 + i],
		    sc->txpow2[14 + i]);
	}
}