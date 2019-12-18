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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct rtwn_softc {int ntxchains; } ;

/* Variables and functions */
 int MS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R92C_IQK_AGC_CONT ; 
 int /*<<< orphan*/  R92C_IQK_AGC_PTS ; 
 int /*<<< orphan*/  R92C_IQK_AGC_RSP ; 
 int /*<<< orphan*/  R92C_POWER_IQK_RESULT ; 
 int /*<<< orphan*/  R92C_RX_IQK_PI (int) ; 
 int /*<<< orphan*/  R92C_RX_IQK_TONE (int) ; 
 int /*<<< orphan*/  R92C_RX_POWER_IQK_AFTER (int) ; 
 int /*<<< orphan*/  R92C_RX_POWER_IQK_BEFORE (int) ; 
 int /*<<< orphan*/  R92C_TX_IQK_PI (int) ; 
 int /*<<< orphan*/  R92C_TX_IQK_TONE (int) ; 
 int /*<<< orphan*/  R92C_TX_POWER_IQK_AFTER (int) ; 
 int /*<<< orphan*/  R92C_TX_POWER_IQK_BEFORE (int) ; 
 int rtwn_bb_read (struct rtwn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_bb_write (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtwn_delay (struct rtwn_softc*,int) ; 

__attribute__((used)) static int
r92ce_iq_calib_chain(struct rtwn_softc *sc, int chain, uint16_t tx[2],
    uint16_t rx[2])
{
	uint32_t status;

	if (chain == 0) {	/* IQ calibration for chain 0. */
		/* IQ calibration settings for chain 0. */
		rtwn_bb_write(sc, R92C_TX_IQK_TONE(0), 0x10008c1f);
		rtwn_bb_write(sc, R92C_RX_IQK_TONE(0), 0x10008c1f);
		rtwn_bb_write(sc, R92C_TX_IQK_PI(0), 0x82140102);

		if (sc->ntxchains > 1) {
			rtwn_bb_write(sc, R92C_RX_IQK_PI(0), 0x28160202);
			/* IQ calibration settings for chain 1. */
			rtwn_bb_write(sc, R92C_TX_IQK_TONE(1), 0x10008c22);
			rtwn_bb_write(sc, R92C_RX_IQK_TONE(1), 0x10008c22);
			rtwn_bb_write(sc, R92C_TX_IQK_PI(1), 0x82140102);
			rtwn_bb_write(sc, R92C_RX_IQK_PI(1), 0x28160202);
		} else
			rtwn_bb_write(sc, R92C_RX_IQK_PI(0), 0x28160502);

		/* LO calibration settings. */
		rtwn_bb_write(sc, R92C_IQK_AGC_RSP, 0x001028d1);
		/* We're doing LO and IQ calibration in one shot. */
		rtwn_bb_write(sc, R92C_IQK_AGC_PTS, 0xf9000000);
		rtwn_bb_write(sc, R92C_IQK_AGC_PTS, 0xf8000000);

	} else {		/* IQ calibration for chain 1. */
		/* We're doing LO and IQ calibration in one shot. */
		rtwn_bb_write(sc, R92C_IQK_AGC_CONT, 2);
		rtwn_bb_write(sc, R92C_IQK_AGC_CONT, 0);
	}

	/* Give LO and IQ calibrations the time to complete. */
	rtwn_delay(sc, 1000);

	/* Read IQ calibration status. */
	status = rtwn_bb_read(sc, R92C_RX_POWER_IQK_AFTER(0));

	if (status & (1 << (28 + chain * 3)))
		return (0);	/* Tx failed. */
	/* Read Tx IQ calibration results. */
	tx[0] = MS(rtwn_bb_read(sc, R92C_TX_POWER_IQK_BEFORE(chain)),
	    R92C_POWER_IQK_RESULT);
	tx[1] = MS(rtwn_bb_read(sc, R92C_TX_POWER_IQK_AFTER(chain)),
	    R92C_POWER_IQK_RESULT);
	if (tx[0] == 0x142 || tx[1] == 0x042)
		return (0);	/* Tx failed. */

	if (status & (1 << (27 + chain * 3)))
		return (1);	/* Rx failed. */
	/* Read Rx IQ calibration results. */
	rx[0] = MS(rtwn_bb_read(sc, R92C_RX_POWER_IQK_BEFORE(chain)),
	    R92C_POWER_IQK_RESULT);
	rx[1] = MS(rtwn_bb_read(sc, R92C_RX_POWER_IQK_AFTER(chain)),
	    R92C_POWER_IQK_RESULT);
	if (rx[0] == 0x132 || rx[1] == 0x036)
		return (1);	/* Rx failed. */

	return (3);	/* Both Tx and Rx succeeded. */
}