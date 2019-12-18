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
struct rt2560_softc {int rf_rev; int hw_radio; int led_mode; int rx_ant; int tx_ant; int nb_ant; int* txpow; int rssi_corr; TYPE_1__* bbp_prom; } ;
struct TYPE_2__ {int reg; int val; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct rt2560_softc*,char*,int,int) ; 
 int RT2560_DEFAULT_RSSI_CORR ; 
 scalar_t__ RT2560_EEPROM_BBP_BASE ; 
 scalar_t__ RT2560_EEPROM_CALIBRATE ; 
 scalar_t__ RT2560_EEPROM_CONFIG0 ; 
 scalar_t__ RT2560_EEPROM_TXPOWER ; 
 int rt2560_eeprom_read (struct rt2560_softc*,scalar_t__) ; 

__attribute__((used)) static void
rt2560_read_config(struct rt2560_softc *sc)
{
	uint16_t val;
	int i;

	val = rt2560_eeprom_read(sc, RT2560_EEPROM_CONFIG0);
	sc->rf_rev =   (val >> 11) & 0x7;
	sc->hw_radio = (val >> 10) & 0x1;
	sc->led_mode = (val >> 6)  & 0x7;
	sc->rx_ant =   (val >> 4)  & 0x3;
	sc->tx_ant =   (val >> 2)  & 0x3;
	sc->nb_ant =   val & 0x3;

	/* read default values for BBP registers */
	for (i = 0; i < 16; i++) {
		val = rt2560_eeprom_read(sc, RT2560_EEPROM_BBP_BASE + i);
		if (val == 0 || val == 0xffff)
			continue;

		sc->bbp_prom[i].reg = val >> 8;
		sc->bbp_prom[i].val = val & 0xff;
	}

	/* read Tx power for all b/g channels */
	for (i = 0; i < 14 / 2; i++) {
		val = rt2560_eeprom_read(sc, RT2560_EEPROM_TXPOWER + i);
		sc->txpow[i * 2] = val & 0xff;
		sc->txpow[i * 2 + 1] = val >> 8;
	}
	for (i = 0; i < 14; ++i) {
		if (sc->txpow[i] > 31)
			sc->txpow[i] = 24;
	}

	val = rt2560_eeprom_read(sc, RT2560_EEPROM_CALIBRATE);
	if ((val & 0xff) == 0xff)
		sc->rssi_corr = RT2560_DEFAULT_RSSI_CORR;
	else
		sc->rssi_corr = val & 0xff;
	DPRINTF(sc, "rssi correction %d, calibrate 0x%02x\n",
		 sc->rssi_corr, val);
}