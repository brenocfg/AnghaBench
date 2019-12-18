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
struct run_softc {int mac_rev; int txmixgain_2ghz; int nrxchains; scalar_t__ patch_dac; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT2860_TX_SW_CFG1 ; 
 int /*<<< orphan*/  RT2860_TX_SW_CFG2 ; 
 int RT3070_PLL_PD ; 
 int RT3070_RF_BLOCK ; 
 int RT3593_TX_LO1 ; 
 int RT3593_TX_LO2 ; 
 int RT5390_MAC_IF_CTRL ; 
 int RT5390_MLD ; 
 int RT5390_RX_LO1 ; 
 int RT5390_RX_LO2 ; 
 int /*<<< orphan*/  run_bbp_read (struct run_softc*,int,int*) ; 
 int /*<<< orphan*/  run_bbp_write (struct run_softc*,int,int) ; 
 int /*<<< orphan*/  run_rt3070_rf_read (struct run_softc*,int,int*) ; 
 int /*<<< orphan*/  run_rt3070_rf_write (struct run_softc*,int,int) ; 
 int /*<<< orphan*/  run_write (struct run_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
run_rt3593_rf_setup(struct run_softc *sc)
{
	uint8_t bbp, rf;

	if (sc->mac_rev >= 0x0211) {
		/* Enable DC filter. */
		run_bbp_write(sc, 103, 0xc0);
	}
	run_write(sc, RT2860_TX_SW_CFG1, 0);
	if (sc->mac_rev < 0x0211) {
		run_write(sc, RT2860_TX_SW_CFG2,
		    sc->patch_dac ? 0x2c : 0x0f);
	} else
		run_write(sc, RT2860_TX_SW_CFG2, 0);

	run_rt3070_rf_read(sc, 50, &rf);
	run_rt3070_rf_write(sc, 50, rf & ~RT3593_TX_LO2);

	run_rt3070_rf_read(sc, 51, &rf);
	rf = (rf & ~(RT3593_TX_LO1 | 0x0c)) |
	    ((sc->txmixgain_2ghz & 0x07) << 2);
	run_rt3070_rf_write(sc, 51, rf);

	run_rt3070_rf_read(sc, 38, &rf);
	run_rt3070_rf_write(sc, 38, rf & ~RT5390_RX_LO1);

	run_rt3070_rf_read(sc, 39, &rf);
	run_rt3070_rf_write(sc, 39, rf & ~RT5390_RX_LO2);

	run_rt3070_rf_read(sc, 1, &rf);
	run_rt3070_rf_write(sc, 1, rf & ~(RT3070_RF_BLOCK | RT3070_PLL_PD));

	run_rt3070_rf_read(sc, 30, &rf);
	rf = (rf & ~0x18) | 0x10;
	run_rt3070_rf_write(sc, 30, rf);

	/* Apply maximum likelihood detection for 2 stream case. */
	run_bbp_read(sc, 105, &bbp);
	if (sc->nrxchains > 1)
		run_bbp_write(sc, 105, bbp | RT5390_MLD);

	/* Avoid data lost and CRC error. */
	run_bbp_read(sc, 4, &bbp);
	run_bbp_write(sc, 4, bbp | RT5390_MAC_IF_CTRL);

	run_bbp_write(sc, 92, 0x02);
	run_bbp_write(sc, 82, 0x82);
	run_bbp_write(sc, 106, 0x05);
	run_bbp_write(sc, 104, 0x92);
	run_bbp_write(sc, 88, 0x90);
	run_bbp_write(sc, 148, 0xc8);
	run_bbp_write(sc, 47, 0x48);
	run_bbp_write(sc, 120, 0x50);

	run_bbp_write(sc, 163, 0x9d);

	/* SNR mapping. */
	run_bbp_write(sc, 142, 0x06);
	run_bbp_write(sc, 143, 0xa0);
	run_bbp_write(sc, 142, 0x07);
	run_bbp_write(sc, 143, 0xa1);
	run_bbp_write(sc, 142, 0x08);
	run_bbp_write(sc, 143, 0xa2);

	run_bbp_write(sc, 31, 0x08);
	run_bbp_write(sc, 68, 0x0b);
	run_bbp_write(sc, 105, 0x04);
}