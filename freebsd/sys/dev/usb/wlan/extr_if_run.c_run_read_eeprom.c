#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct ieee80211com {int* ic_macaddr; } ;
struct run_softc {int mac_ver; int freq; int leds; int* led; int rf_rev; int ntxchains; int nrxchains; int patch_dac; int ext_5ghz_lna; int ext_2ghz_lna; int calib_2ghz; int calib_5ghz; int rfswitch; int* txpow20mhz; int* rssi_2ghz; int txmixgain_2ghz; int* lna; int* rssi_5ghz; int txmixgain_5ghz; void** txpow40mhz_5ghz; void** txpow40mhz_2ghz; int /*<<< orphan*/  sc_dev; TYPE_2__* rf; TYPE_1__* bbp; int /*<<< orphan*/  sc_srom_read; struct ieee80211com sc_ic; } ;
typedef  int int8_t ;
struct TYPE_4__ {int val; int reg; } ;
struct TYPE_3__ {int val; int reg; } ;

/* Variables and functions */
 int RT2860_EEPROM_ANTENNA ; 
 int RT2860_EEPROM_BBP_BASE ; 
 int RT2860_EEPROM_CONFIG ; 
 int RT2860_EEPROM_DELTAPWR ; 
 int RT2860_EEPROM_FREQ_LEDS ; 
 int RT2860_EEPROM_LED1 ; 
 int RT2860_EEPROM_LED2 ; 
 int RT2860_EEPROM_LED3 ; 
 int RT2860_EEPROM_LNA ; 
 int RT2860_EEPROM_MAC01 ; 
 int RT2860_EEPROM_MAC23 ; 
 int RT2860_EEPROM_MAC45 ; 
 int RT2860_EEPROM_RPWR ; 
 int RT2860_EEPROM_RSSI1_2GHZ ; 
 int RT2860_EEPROM_RSSI1_5GHZ ; 
 int RT2860_EEPROM_RSSI2_2GHZ ; 
 int RT2860_EEPROM_RSSI2_5GHZ ; 
 int RT2860_EEPROM_VERSION ; 
 int RT2860_RF_2820 ; 
 int /*<<< orphan*/  RT3070_EFUSE_CTRL ; 
 int RT3070_RF_3020 ; 
 int RT3070_RF_3052 ; 
 int RT3070_SEL_EFUSE ; 
 int RT3071_EEPROM_RF_BASE ; 
 int RT3593_EEPROM_FREQ ; 
 int RT3593_EEPROM_FREQ_LEDS ; 
 int RT3593_EEPROM_LED1 ; 
 int RT3593_EEPROM_LED2 ; 
 int RT3593_EEPROM_LED3 ; 
 int RT3593_EEPROM_LNA ; 
 int RT3593_EEPROM_LNA_5GHZ ; 
 int RT3593_EEPROM_RSSI1_2GHZ ; 
 int RT3593_EEPROM_RSSI1_5GHZ ; 
 int RT3593_EEPROM_RSSI2_2GHZ ; 
 int RT3593_EEPROM_RSSI2_5GHZ ; 
 int RUN_DEBUG_ROM ; 
 int RUN_DEBUG_RSSI ; 
 int RUN_DEBUG_TXPWR ; 
 int /*<<< orphan*/  RUN_DPRINTF (struct run_softc*,int,char*,int,...) ; 
 void* b4inc (int,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  run_eeprom_read_2 ; 
 int /*<<< orphan*/  run_efuse_read_2 ; 
 int /*<<< orphan*/  run_get_txpower (struct run_softc*) ; 
 int /*<<< orphan*/  run_read (struct run_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  run_rt3593_get_txpower (struct run_softc*) ; 
 int /*<<< orphan*/  run_srom_read (struct run_softc*,int,int*) ; 

__attribute__((used)) static int
run_read_eeprom(struct run_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	int8_t delta_2ghz, delta_5ghz;
	uint32_t tmp;
	uint16_t val;
	int ridx, ant, i;

	/* check whether the ROM is eFUSE ROM or EEPROM */
	sc->sc_srom_read = run_eeprom_read_2;
	if (sc->mac_ver >= 0x3070) {
		run_read(sc, RT3070_EFUSE_CTRL, &tmp);
		RUN_DPRINTF(sc, RUN_DEBUG_ROM, "EFUSE_CTRL=0x%08x\n", tmp);
		if ((tmp & RT3070_SEL_EFUSE) || sc->mac_ver == 0x3593)
			sc->sc_srom_read = run_efuse_read_2;
	}

	/* read ROM version */
	run_srom_read(sc, RT2860_EEPROM_VERSION, &val);
	RUN_DPRINTF(sc, RUN_DEBUG_ROM,
	    "EEPROM rev=%d, FAE=%d\n", val >> 8, val & 0xff);

	/* read MAC address */
	run_srom_read(sc, RT2860_EEPROM_MAC01, &val);
	ic->ic_macaddr[0] = val & 0xff;
	ic->ic_macaddr[1] = val >> 8;
	run_srom_read(sc, RT2860_EEPROM_MAC23, &val);
	ic->ic_macaddr[2] = val & 0xff;
	ic->ic_macaddr[3] = val >> 8;
	run_srom_read(sc, RT2860_EEPROM_MAC45, &val);
	ic->ic_macaddr[4] = val & 0xff;
	ic->ic_macaddr[5] = val >> 8;

	if (sc->mac_ver < 0x3593) {
		/* read vender BBP settings */
		for (i = 0; i < 10; i++) {
			run_srom_read(sc, RT2860_EEPROM_BBP_BASE + i, &val);
			sc->bbp[i].val = val & 0xff;
			sc->bbp[i].reg = val >> 8;
			RUN_DPRINTF(sc, RUN_DEBUG_ROM,
			    "BBP%d=0x%02x\n", sc->bbp[i].reg, sc->bbp[i].val);
		}
		if (sc->mac_ver >= 0x3071) {
			/* read vendor RF settings */
			for (i = 0; i < 10; i++) {
				run_srom_read(sc, RT3071_EEPROM_RF_BASE + i,
				   &val);
				sc->rf[i].val = val & 0xff;
				sc->rf[i].reg = val >> 8;
				RUN_DPRINTF(sc, RUN_DEBUG_ROM, "RF%d=0x%02x\n",
				    sc->rf[i].reg, sc->rf[i].val);
			}
		}
	}

	/* read RF frequency offset from EEPROM */
	run_srom_read(sc, (sc->mac_ver != 0x3593) ? RT2860_EEPROM_FREQ_LEDS :
	    RT3593_EEPROM_FREQ, &val);
	sc->freq = ((val & 0xff) != 0xff) ? val & 0xff : 0;
	RUN_DPRINTF(sc, RUN_DEBUG_ROM, "EEPROM freq offset %d\n",
	    sc->freq & 0xff);

	run_srom_read(sc, (sc->mac_ver != 0x3593) ? RT2860_EEPROM_FREQ_LEDS :
	    RT3593_EEPROM_FREQ_LEDS, &val);
	if (val >> 8 != 0xff) {
		/* read LEDs operating mode */
		sc->leds = val >> 8;
		run_srom_read(sc, (sc->mac_ver != 0x3593) ? RT2860_EEPROM_LED1 :
		    RT3593_EEPROM_LED1, &sc->led[0]);
		run_srom_read(sc, (sc->mac_ver != 0x3593) ? RT2860_EEPROM_LED2 :
		    RT3593_EEPROM_LED2, &sc->led[1]);
		run_srom_read(sc, (sc->mac_ver != 0x3593) ? RT2860_EEPROM_LED3 :
		    RT3593_EEPROM_LED3, &sc->led[2]);
	} else {
		/* broken EEPROM, use default settings */
		sc->leds = 0x01;
		sc->led[0] = 0x5555;
		sc->led[1] = 0x2221;
		sc->led[2] = 0x5627;	/* differs from RT2860 */
	}
	RUN_DPRINTF(sc, RUN_DEBUG_ROM,
	    "EEPROM LED mode=0x%02x, LEDs=0x%04x/0x%04x/0x%04x\n",
	    sc->leds, sc->led[0], sc->led[1], sc->led[2]);

	/* read RF information */
	if (sc->mac_ver == 0x5390 || sc->mac_ver ==0x5392)
		run_srom_read(sc, 0x00, &val);
	else
		run_srom_read(sc, RT2860_EEPROM_ANTENNA, &val);

	if (val == 0xffff) {
		device_printf(sc->sc_dev,
		    "invalid EEPROM antenna info, using default\n");
		if (sc->mac_ver == 0x3572) {
			/* default to RF3052 2T2R */
			sc->rf_rev = RT3070_RF_3052;
			sc->ntxchains = 2;
			sc->nrxchains = 2;
		} else if (sc->mac_ver >= 0x3070) {
			/* default to RF3020 1T1R */
			sc->rf_rev = RT3070_RF_3020;
			sc->ntxchains = 1;
			sc->nrxchains = 1;
		} else {
			/* default to RF2820 1T2R */
			sc->rf_rev = RT2860_RF_2820;
			sc->ntxchains = 1;
			sc->nrxchains = 2;
		}
	} else {
		if (sc->mac_ver == 0x5390 || sc->mac_ver ==0x5392) {
			sc->rf_rev = val;
			run_srom_read(sc, RT2860_EEPROM_ANTENNA, &val);
		} else
			sc->rf_rev = (val >> 8) & 0xf;
		sc->ntxchains = (val >> 4) & 0xf;
		sc->nrxchains = val & 0xf;
	}
	RUN_DPRINTF(sc, RUN_DEBUG_ROM, "EEPROM RF rev=0x%04x chains=%dT%dR\n",
	    sc->rf_rev, sc->ntxchains, sc->nrxchains);

	/* check if RF supports automatic Tx access gain control */
	run_srom_read(sc, RT2860_EEPROM_CONFIG, &val);
	RUN_DPRINTF(sc, RUN_DEBUG_ROM, "EEPROM CFG 0x%04x\n", val);
	/* check if driver should patch the DAC issue */
	if ((val >> 8) != 0xff)
		sc->patch_dac = (val >> 15) & 1;
	if ((val & 0xff) != 0xff) {
		sc->ext_5ghz_lna = (val >> 3) & 1;
		sc->ext_2ghz_lna = (val >> 2) & 1;
		/* check if RF supports automatic Tx access gain control */
		sc->calib_2ghz = sc->calib_5ghz = (val >> 1) & 1;
		/* check if we have a hardware radio switch */
		sc->rfswitch = val & 1;
	}

	/* Read Tx power settings. */
	if (sc->mac_ver == 0x3593)
		run_rt3593_get_txpower(sc);
	else
		run_get_txpower(sc);

	/* read Tx power compensation for each Tx rate */
	run_srom_read(sc, RT2860_EEPROM_DELTAPWR, &val);
	delta_2ghz = delta_5ghz = 0;
	if ((val & 0xff) != 0xff && (val & 0x80)) {
		delta_2ghz = val & 0xf;
		if (!(val & 0x40))	/* negative number */
			delta_2ghz = -delta_2ghz;
	}
	val >>= 8;
	if ((val & 0xff) != 0xff && (val & 0x80)) {
		delta_5ghz = val & 0xf;
		if (!(val & 0x40))	/* negative number */
			delta_5ghz = -delta_5ghz;
	}
	RUN_DPRINTF(sc, RUN_DEBUG_ROM | RUN_DEBUG_TXPWR,
	    "power compensation=%d (2GHz), %d (5GHz)\n", delta_2ghz, delta_5ghz);

	for (ridx = 0; ridx < 5; ridx++) {
		uint32_t reg;

		run_srom_read(sc, RT2860_EEPROM_RPWR + ridx * 2, &val);
		reg = val;
		run_srom_read(sc, RT2860_EEPROM_RPWR + ridx * 2 + 1, &val);
		reg |= (uint32_t)val << 16;

		sc->txpow20mhz[ridx] = reg;
		sc->txpow40mhz_2ghz[ridx] = b4inc(reg, delta_2ghz);
		sc->txpow40mhz_5ghz[ridx] = b4inc(reg, delta_5ghz);

		RUN_DPRINTF(sc, RUN_DEBUG_ROM | RUN_DEBUG_TXPWR,
		    "ridx %d: power 20MHz=0x%08x, 40MHz/2GHz=0x%08x, "
		    "40MHz/5GHz=0x%08x\n", ridx, sc->txpow20mhz[ridx],
		    sc->txpow40mhz_2ghz[ridx], sc->txpow40mhz_5ghz[ridx]);
	}

	/* Read RSSI offsets and LNA gains from EEPROM. */
	run_srom_read(sc, (sc->mac_ver != 0x3593) ? RT2860_EEPROM_RSSI1_2GHZ :
	    RT3593_EEPROM_RSSI1_2GHZ, &val);
	sc->rssi_2ghz[0] = val & 0xff;	/* Ant A */
	sc->rssi_2ghz[1] = val >> 8;	/* Ant B */
	run_srom_read(sc, (sc->mac_ver != 0x3593) ? RT2860_EEPROM_RSSI2_2GHZ :
	    RT3593_EEPROM_RSSI2_2GHZ, &val);
	if (sc->mac_ver >= 0x3070) {
		if (sc->mac_ver == 0x3593) {
			sc->txmixgain_2ghz = 0;
			sc->rssi_2ghz[2] = val & 0xff;	/* Ant C */
		} else {
			/*
			 * On RT3070 chips (limited to 2 Rx chains), this ROM
			 * field contains the Tx mixer gain for the 2GHz band.
			 */
			if ((val & 0xff) != 0xff)
				sc->txmixgain_2ghz = val & 0x7;
		}
		RUN_DPRINTF(sc, RUN_DEBUG_ROM, "tx mixer gain=%u (2GHz)\n",
		    sc->txmixgain_2ghz);
	} else
		sc->rssi_2ghz[2] = val & 0xff;	/* Ant C */
	if (sc->mac_ver == 0x3593)
		run_srom_read(sc, RT3593_EEPROM_LNA_5GHZ, &val);
	sc->lna[2] = val >> 8;		/* channel group 2 */

	run_srom_read(sc, (sc->mac_ver != 0x3593) ? RT2860_EEPROM_RSSI1_5GHZ :
	    RT3593_EEPROM_RSSI1_5GHZ, &val);
	sc->rssi_5ghz[0] = val & 0xff;	/* Ant A */
	sc->rssi_5ghz[1] = val >> 8;	/* Ant B */
	run_srom_read(sc, (sc->mac_ver != 0x3593) ? RT2860_EEPROM_RSSI2_5GHZ :
	    RT3593_EEPROM_RSSI2_5GHZ, &val);
	if (sc->mac_ver == 0x3572) {
		/*
		 * On RT3572 chips (limited to 2 Rx chains), this ROM
		 * field contains the Tx mixer gain for the 5GHz band.
		 */
		if ((val & 0xff) != 0xff)
			sc->txmixgain_5ghz = val & 0x7;
		RUN_DPRINTF(sc, RUN_DEBUG_ROM, "tx mixer gain=%u (5GHz)\n",
		    sc->txmixgain_5ghz);
	} else
		sc->rssi_5ghz[2] = val & 0xff;	/* Ant C */
	if (sc->mac_ver == 0x3593) {
		sc->txmixgain_5ghz = 0;
		run_srom_read(sc, RT3593_EEPROM_LNA_5GHZ, &val);
	}
	sc->lna[3] = val >> 8;		/* channel group 3 */

	run_srom_read(sc, (sc->mac_ver != 0x3593) ? RT2860_EEPROM_LNA :
	    RT3593_EEPROM_LNA, &val);
	sc->lna[0] = val & 0xff;	/* channel group 0 */
	sc->lna[1] = val >> 8;		/* channel group 1 */

	/* fix broken 5GHz LNA entries */
	if (sc->lna[2] == 0 || sc->lna[2] == 0xff) {
		RUN_DPRINTF(sc, RUN_DEBUG_ROM,
		    "invalid LNA for channel group %d\n", 2);
		sc->lna[2] = sc->lna[1];
	}
	if (sc->lna[3] == 0 || sc->lna[3] == 0xff) {
		RUN_DPRINTF(sc, RUN_DEBUG_ROM,
		    "invalid LNA for channel group %d\n", 3);
		sc->lna[3] = sc->lna[1];
	}

	/* fix broken RSSI offset entries */
	for (ant = 0; ant < 3; ant++) {
		if (sc->rssi_2ghz[ant] < -10 || sc->rssi_2ghz[ant] > 10) {
			RUN_DPRINTF(sc, RUN_DEBUG_ROM | RUN_DEBUG_RSSI,
			    "invalid RSSI%d offset: %d (2GHz)\n",
			    ant + 1, sc->rssi_2ghz[ant]);
			sc->rssi_2ghz[ant] = 0;
		}
		if (sc->rssi_5ghz[ant] < -10 || sc->rssi_5ghz[ant] > 10) {
			RUN_DPRINTF(sc, RUN_DEBUG_ROM | RUN_DEBUG_RSSI,
			    "invalid RSSI%d offset: %d (5GHz)\n",
			    ant + 1, sc->rssi_5ghz[ant]);
			sc->rssi_5ghz[ant] = 0;
		}
	}
	return (0);
}