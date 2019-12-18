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
typedef  int /*<<< orphan*/  uint32_t ;
struct rtwn_softc {int nrxchains; } ;

/* Variables and functions */
 scalar_t__ R92C_OFDM1_LSTF ; 
 int /*<<< orphan*/  R92C_RF_AC ; 
 int /*<<< orphan*/  R92C_RF_AC_MODE ; 
 int /*<<< orphan*/  R92C_RF_AC_MODE_STANDBY ; 
 int /*<<< orphan*/  R92C_RF_CHNLBW ; 
 int /*<<< orphan*/  R92C_RF_CHNLBW_LCSTART ; 
 scalar_t__ R92C_TXPAUSE ; 
 int R92C_TX_QUEUE_ALL ; 
 int /*<<< orphan*/  RW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_delay (struct rtwn_softc*,int) ; 
 int rtwn_read_1 (struct rtwn_softc*,scalar_t__) ; 
 int /*<<< orphan*/  rtwn_rf_read (struct rtwn_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_rf_setbits (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_rf_write (struct rtwn_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_write_1 (struct rtwn_softc*,scalar_t__,int) ; 

void
r92c_lc_calib(struct rtwn_softc *sc)
{
	uint32_t rf_ac[2];
	uint8_t txmode;
	int i;

	txmode = rtwn_read_1(sc, R92C_OFDM1_LSTF + 3);
	if ((txmode & 0x70) != 0) {
		/* Disable all continuous Tx. */
		rtwn_write_1(sc, R92C_OFDM1_LSTF + 3, txmode & ~0x70);

		/* Set RF mode to standby mode. */
		for (i = 0; i < sc->nrxchains; i++) {
			rf_ac[i] = rtwn_rf_read(sc, i, R92C_RF_AC);
			rtwn_rf_write(sc, i, R92C_RF_AC,
			    RW(rf_ac[i], R92C_RF_AC_MODE,
				R92C_RF_AC_MODE_STANDBY));
		}
	} else {
		/* Block all Tx queues. */
		rtwn_write_1(sc, R92C_TXPAUSE, R92C_TX_QUEUE_ALL);
	}
	/* Start calibration. */
	rtwn_rf_setbits(sc, 0, R92C_RF_CHNLBW, 0, R92C_RF_CHNLBW_LCSTART);

	/* Give calibration the time to complete. */
	rtwn_delay(sc, 100000);	/* 100ms */

	/* Restore configuration. */
	if ((txmode & 0x70) != 0) {
		/* Restore Tx mode. */
		rtwn_write_1(sc, R92C_OFDM1_LSTF + 3, txmode);
		/* Restore RF mode. */
		for (i = 0; i < sc->nrxchains; i++)
			rtwn_rf_write(sc, i, R92C_RF_AC, rf_ac[i]);
	} else {
		/* Unblock all Tx queues. */
		rtwn_write_1(sc, R92C_TXPAUSE, 0x00);
	}
}