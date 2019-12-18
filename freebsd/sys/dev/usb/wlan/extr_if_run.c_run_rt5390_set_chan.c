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
typedef  int uint8_t ;
typedef  scalar_t__ u_int ;
struct run_softc {int* txpow1; int* txpow2; int mac_ver; int mac_rev; } ;
typedef  int int8_t ;
struct TYPE_4__ {scalar_t__ chan; } ;
struct TYPE_3__ {int n; int k; int r; } ;

/* Variables and functions */
 int RT3070_PLL_PD ; 
 int RT3070_RF_BLOCK ; 
 int RT3070_RX0_PD ; 
 int RT3070_RX1_PD ; 
 int RT3070_TX0_PD ; 
 int RT3070_TX1_PD ; 
 int RT5390_VCOCAL ; 
 TYPE_2__* rt2860_rf2850 ; 
 TYPE_1__* rt3070_freqs ; 
 int /*<<< orphan*/  run_adjust_freq_offset (struct run_softc*) ; 
 int /*<<< orphan*/  run_delay (struct run_softc*,int) ; 
 int /*<<< orphan*/  run_rt3070_rf_read (struct run_softc*,int,int*) ; 
 int /*<<< orphan*/  run_rt3070_rf_write (struct run_softc*,int,int) ; 

__attribute__((used)) static void
run_rt5390_set_chan(struct run_softc *sc, u_int chan)
{
	int8_t txpow1, txpow2;
	uint8_t rf;
	int i;

	/* find the settings for this channel (we know it exists) */
	for (i = 0; rt2860_rf2850[i].chan != chan; i++);

	/* use Tx power values from EEPROM */
	txpow1 = sc->txpow1[i];
	txpow2 = sc->txpow2[i];

	run_rt3070_rf_write(sc, 8, rt3070_freqs[i].n);
	run_rt3070_rf_write(sc, 9, rt3070_freqs[i].k & 0x0f);
	run_rt3070_rf_read(sc, 11, &rf);
	rf = (rf & ~0x03) | (rt3070_freqs[i].r & 0x03);
	run_rt3070_rf_write(sc, 11, rf);

	run_rt3070_rf_read(sc, 49, &rf);
	rf = (rf & ~0x3f) | (txpow1 & 0x3f);
	/* The valid range of the RF R49 is 0x00 to 0x27. */
	if ((rf & 0x3f) > 0x27)
		rf = (rf & ~0x3f) | 0x27;
	run_rt3070_rf_write(sc, 49, rf);

	if (sc->mac_ver == 0x5392) {
		run_rt3070_rf_read(sc, 50, &rf);
		rf = (rf & ~0x3f) | (txpow2 & 0x3f);
		/* The valid range of the RF R50 is 0x00 to 0x27. */
		if ((rf & 0x3f) > 0x27)
			rf = (rf & ~0x3f) | 0x27;
		run_rt3070_rf_write(sc, 50, rf);
	}

	run_rt3070_rf_read(sc, 1, &rf);
	rf |= RT3070_RF_BLOCK | RT3070_PLL_PD | RT3070_RX0_PD | RT3070_TX0_PD;
	if (sc->mac_ver == 0x5392)
		rf |= RT3070_RX1_PD | RT3070_TX1_PD;
	run_rt3070_rf_write(sc, 1, rf);

	if (sc->mac_ver != 0x5392) {
		run_rt3070_rf_read(sc, 2, &rf);
		rf |= 0x80;
		run_rt3070_rf_write(sc, 2, rf);
		run_delay(sc, 10);
		rf &= 0x7f;
		run_rt3070_rf_write(sc, 2, rf);
	}

	run_adjust_freq_offset(sc);

	if (sc->mac_ver == 0x5392) {
		/* Fix for RT5392C. */
		if (sc->mac_rev >= 0x0223) {
			if (chan <= 4)
				rf = 0x0f;
			else if (chan >= 5 && chan <= 7)
				rf = 0x0e;
			else
				rf = 0x0d;
			run_rt3070_rf_write(sc, 23, rf);

			if (chan <= 4)
				rf = 0x0c;
			else if (chan == 5)
				rf = 0x0b;
			else if (chan >= 6 && chan <= 7)
				rf = 0x0a;
			else if (chan >= 8 && chan <= 10)
				rf = 0x09;
			else
				rf = 0x08;
			run_rt3070_rf_write(sc, 59, rf);
		} else {
			if (chan <= 11)
				rf = 0x0f;
			else
				rf = 0x0b;
			run_rt3070_rf_write(sc, 59, rf);
		}
	} else {
		/* Fix for RT5390F. */
		if (sc->mac_rev >= 0x0502) {
			if (chan <= 11)
				rf = 0x43;
			else
				rf = 0x23;
			run_rt3070_rf_write(sc, 55, rf);

			if (chan <= 11)
				rf = 0x0f;
			else if (chan == 12)
				rf = 0x0d;
			else
				rf = 0x0b;
			run_rt3070_rf_write(sc, 59, rf);
		} else {
			run_rt3070_rf_write(sc, 55, 0x44);
			run_rt3070_rf_write(sc, 59, 0x8f);
		}
	}

	/* Enable VCO calibration. */
	run_rt3070_rf_read(sc, 3, &rf);
	rf |= RT5390_VCOCAL;
	run_rt3070_rf_write(sc, 3, rf);
}