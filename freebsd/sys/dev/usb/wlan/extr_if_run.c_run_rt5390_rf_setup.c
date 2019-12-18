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
struct run_softc {int mac_rev; int mac_ver; int ntxchains; int nrxchains; scalar_t__ patch_dac; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT2860_TX_SW_CFG1 ; 
 int /*<<< orphan*/  RT2860_TX_SW_CFG2 ; 
 int RT5390_MAC_IF_CTRL ; 
 int RT5390_RX_LO1 ; 
 int RT5390_RX_LO2 ; 
 int /*<<< orphan*/  run_bbp_read (struct run_softc*,int,int*) ; 
 int /*<<< orphan*/  run_bbp_write (struct run_softc*,int,int) ; 
 int /*<<< orphan*/  run_rt3070_rf_read (struct run_softc*,int,int*) ; 
 int /*<<< orphan*/  run_rt3070_rf_write (struct run_softc*,int,int) ; 
 int /*<<< orphan*/  run_write (struct run_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
run_rt5390_rf_setup(struct run_softc *sc)
{
	uint8_t bbp, rf;

	if (sc->mac_rev >= 0x0211) {
		/* Enable DC filter. */
		run_bbp_write(sc, 103, 0xc0);

		if (sc->mac_ver != 0x5592) {
			/* Improve power consumption. */
			run_bbp_read(sc, 31, &bbp);
			run_bbp_write(sc, 31, bbp & ~0x03);
		}
	}

	run_bbp_read(sc, 138, &bbp);
	if (sc->ntxchains == 1)
		bbp |= 0x20;	/* turn off DAC1 */
	if (sc->nrxchains == 1)
		bbp &= ~0x02;	/* turn off ADC1 */
	run_bbp_write(sc, 138, bbp);

	run_rt3070_rf_read(sc, 38, &rf);
	run_rt3070_rf_write(sc, 38, rf & ~RT5390_RX_LO1);

	run_rt3070_rf_read(sc, 39, &rf);
	run_rt3070_rf_write(sc, 39, rf & ~RT5390_RX_LO2);

	/* Avoid data lost and CRC error. */
	run_bbp_read(sc, 4, &bbp);
	run_bbp_write(sc, 4, bbp | RT5390_MAC_IF_CTRL);

	run_rt3070_rf_read(sc, 30, &rf);
	rf = (rf & ~0x18) | 0x10;
	run_rt3070_rf_write(sc, 30, rf);

	if (sc->mac_ver != 0x5592) {
		run_write(sc, RT2860_TX_SW_CFG1, 0);
		if (sc->mac_rev < 0x0211) {
			run_write(sc, RT2860_TX_SW_CFG2,
			    sc->patch_dac ? 0x2c : 0x0f);
		} else
			run_write(sc, RT2860_TX_SW_CFG2, 0);
	}
}