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
typedef  int u_int ;
struct run_softc {int* txpow1; int* txpow2; int ntxchains; int* txpow3; int bbp25; int bbp26; int rf24_20mhz; } ;
typedef  int int8_t ;
struct TYPE_4__ {int chan; } ;
struct TYPE_3__ {int n; int k; int r; } ;

/* Variables and functions */
 int RT3070_PLL_PD ; 
 int RT3070_RF_BLOCK ; 
 int RT3070_RX0_PD ; 
 int RT3070_RX1_PD ; 
 int RT3070_RX2_PD ; 
 int RT3070_TX0_PD ; 
 int RT3070_TX1_PD ; 
 int RT3070_TX2_PD ; 
 int RT5390_VCOCAL ; 
 TYPE_2__* rt2860_rf2850 ; 
 TYPE_1__* rt3070_freqs ; 
 int /*<<< orphan*/  run_adjust_freq_offset (struct run_softc*) ; 
 int /*<<< orphan*/  run_bbp_write (struct run_softc*,int,int) ; 
 int /*<<< orphan*/  run_rt3070_rf_read (struct run_softc*,int,int*) ; 
 int /*<<< orphan*/  run_rt3070_rf_write (struct run_softc*,int,int) ; 

__attribute__((used)) static void
run_rt3593_set_chan(struct run_softc *sc, u_int chan)
{
	int8_t txpow1, txpow2, txpow3;
	uint8_t h20mhz, rf;
	int i;

	/* find the settings for this channel (we know it exists) */
	for (i = 0; rt2860_rf2850[i].chan != chan; i++);

	/* use Tx power values from EEPROM */
	txpow1 = sc->txpow1[i];
	txpow2 = sc->txpow2[i];
	txpow3 = (sc->ntxchains == 3) ? sc->txpow3[i] : 0;

	if (chan <= 14) {
		run_bbp_write(sc, 25, sc->bbp25);
		run_bbp_write(sc, 26, sc->bbp26);
	} else {
		/* Enable IQ phase correction. */
		run_bbp_write(sc, 25, 0x09);
		run_bbp_write(sc, 26, 0xff);
	}

	run_rt3070_rf_write(sc, 8, rt3070_freqs[i].n);
	run_rt3070_rf_write(sc, 9, rt3070_freqs[i].k & 0x0f);
	run_rt3070_rf_read(sc, 11, &rf);
	rf = (rf & ~0x03) | (rt3070_freqs[i].r & 0x03);
	run_rt3070_rf_write(sc, 11, rf);

	/* Set pll_idoh. */
	run_rt3070_rf_read(sc, 11, &rf);
	rf &= ~0x4c;
	rf |= (chan <= 14) ? 0x44 : 0x48;
	run_rt3070_rf_write(sc, 11, rf);

	if (chan <= 14)
		rf = txpow1 & 0x1f;
	else
		rf = 0x40 | ((txpow1 & 0x18) << 1) | (txpow1 & 0x07);
	run_rt3070_rf_write(sc, 53, rf);

	if (chan <= 14)
		rf = txpow2 & 0x1f;
	else
		rf = 0x40 | ((txpow2 & 0x18) << 1) | (txpow2 & 0x07);
	run_rt3070_rf_write(sc, 55, rf);

	if (chan <= 14)
		rf = txpow3 & 0x1f;
	else
		rf = 0x40 | ((txpow3 & 0x18) << 1) | (txpow3 & 0x07);
	run_rt3070_rf_write(sc, 54, rf);

	rf = RT3070_RF_BLOCK | RT3070_PLL_PD;
	if (sc->ntxchains == 3)
		rf |= RT3070_TX0_PD | RT3070_TX1_PD | RT3070_TX2_PD;
	else
		rf |= RT3070_TX0_PD | RT3070_TX1_PD;
	rf |= RT3070_RX0_PD | RT3070_RX1_PD | RT3070_RX2_PD;
	run_rt3070_rf_write(sc, 1, rf);

	run_adjust_freq_offset(sc);

	run_rt3070_rf_write(sc, 31, (chan <= 14) ? 0xa0 : 0x80);

	h20mhz = (sc->rf24_20mhz & 0x20) >> 5; 
	run_rt3070_rf_read(sc, 30, &rf);
	rf = (rf & ~0x06) | (h20mhz << 1) | (h20mhz << 2);
	run_rt3070_rf_write(sc, 30, rf);

	run_rt3070_rf_read(sc, 36, &rf);
	if (chan <= 14)
		rf |= 0x80;
	else
		rf &= ~0x80;
	run_rt3070_rf_write(sc, 36, rf);

	/* Set vcolo_bs. */
	run_rt3070_rf_write(sc, 34, (chan <= 14) ? 0x3c : 0x20);
	/* Set pfd_delay. */
	run_rt3070_rf_write(sc, 12, (chan <= 14) ? 0x1a : 0x12);

	/* Set vco bias current control. */
	run_rt3070_rf_read(sc, 6, &rf);
	rf &= ~0xc0;
	if (chan <= 14)
		rf |= 0x40;
	else if (chan <= 128)
		rf |= 0x80;
	else
		rf |= 0x40;
	run_rt3070_rf_write(sc, 6, rf);
		
	run_rt3070_rf_read(sc, 30, &rf);
	rf = (rf & ~0x18) | 0x10;
	run_rt3070_rf_write(sc, 30, rf);

	run_rt3070_rf_write(sc, 10, (chan <= 14) ? 0xd3 : 0xd8);
	run_rt3070_rf_write(sc, 13, (chan <= 14) ? 0x12 : 0x23);

	run_rt3070_rf_read(sc, 51, &rf);
	rf = (rf & ~0x03) | 0x01;
	run_rt3070_rf_write(sc, 51, rf);
	/* Set tx_mx1_cc. */
	run_rt3070_rf_read(sc, 51, &rf);
	rf &= ~0x1c;
	rf |= (chan <= 14) ? 0x14 : 0x10;
	run_rt3070_rf_write(sc, 51, rf);
	/* Set tx_mx1_ic. */
	run_rt3070_rf_read(sc, 51, &rf);
	rf &= ~0xe0;
	rf |= (chan <= 14) ? 0x60 : 0x40;
	run_rt3070_rf_write(sc, 51, rf);
	/* Set tx_lo1_ic. */
	run_rt3070_rf_read(sc, 49, &rf);
	rf &= ~0x1c;
	rf |= (chan <= 14) ? 0x0c : 0x08;
	run_rt3070_rf_write(sc, 49, rf);
	/* Set tx_lo1_en. */
	run_rt3070_rf_read(sc, 50, &rf);
	run_rt3070_rf_write(sc, 50, rf & ~0x20);
	/* Set drv_cc. */
	run_rt3070_rf_read(sc, 57, &rf);
	rf &= ~0xfc;
	rf |= (chan <= 14) ?  0x6c : 0x3c;
	run_rt3070_rf_write(sc, 57, rf);
	/* Set rx_mix1_ic, rxa_lnactr, lna_vc, lna_inbias_en and lna_en. */
	run_rt3070_rf_write(sc, 44, (chan <= 14) ? 0x93 : 0x9b);
	/* Set drv_gnd_a, tx_vga_cc_a and tx_mx2_gain. */
	run_rt3070_rf_write(sc, 52, (chan <= 14) ? 0x45 : 0x05);
	/* Enable VCO calibration. */
	run_rt3070_rf_read(sc, 3, &rf);
	rf &= ~RT5390_VCOCAL;
	rf |= (chan <= 14) ? RT5390_VCOCAL : 0xbe;
	run_rt3070_rf_write(sc, 3, rf);

	if (chan <= 14)
		rf = 0x23;
	else if (chan <= 64)
		rf = 0x36;
	else if (chan <= 128)
		rf = 0x32;
	else
		rf = 0x30;
	run_rt3070_rf_write(sc, 39, rf);
	if (chan <= 14)
		rf = 0xbb;
	else if (chan <= 64)
		rf = 0xeb;
	else if (chan <= 128)
		rf = 0xb3;
	else
		rf = 0x9b;
	run_rt3070_rf_write(sc, 45, rf);

	/* Set FEQ/AEQ control. */
	run_bbp_write(sc, 105, 0x34);
}